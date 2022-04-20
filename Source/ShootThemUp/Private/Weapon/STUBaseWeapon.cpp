// Shoot Them Up Game. All Right Reserved

#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All)

ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = DefaultAmmo;
}

void ASTUBaseWeapon::StartFire()
{
	FireInProgress = true;
}

void ASTUBaseWeapon::StopFire()
{
	FireInProgress = false;
}

bool ASTUBaseWeapon::IsFiring() const
{
	return FireInProgress;
}

void ASTUBaseWeapon::MakeShot() {}

bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto STUCharacter = Cast<ACharacter>(GetOwner());
	if(!STUCharacter) return false;

	if(STUCharacter->IsPlayerControlled())
	{
		const auto Controller = STUCharacter->GetController<APlayerController>();
		if(!Controller) return false;

		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}
	return true;
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTUBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;

	if(!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	FVector ShootDirection = ViewRotation.Vector();
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const
{
	if(!GetWorld()) return;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	CollisionParams.bReturnPhysicalMaterial = true;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,
	                                     CollisionParams);
}

void ASTUBaseWeapon::DecreaseAmmo()
{
	if(CurrentAmmo.Bullets == 0)
	{
		UE_LOG(LogWeapon, Warning, TEXT("Clip is empty"));
		return;
	}
	CurrentAmmo.Bullets--;

	if(IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFire();
		OnClipEmpty.Broadcast(this);
	}
}

bool ASTUBaseWeapon::IsAmmoEmpty() const
{
	return !CurrentAmmo.Infinite && !CurrentAmmo.Clips && IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty() const
{
	return !CurrentAmmo.Bullets;
}

void ASTUBaseWeapon::ChangeClip()
{
	if(!CurrentAmmo.Infinite)
	{
		if(CurrentAmmo.Clips == 0)
		{
			UE_LOG(LogWeapon, Warning, TEXT("NO MORE CLIPS"));
			return;
		}
		CurrentAmmo.Clips--;
	}
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	//UE_LOG(LogWeapon, Display, TEXT("-----------CHANGE CLIP-----------"));
}

void ASTUBaseWeapon::LogAmmo()
{
	FString AmmoInfo = "Ammo = " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
	AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
	UE_LOG(LogWeapon, Display, TEXT("%s"), *AmmoInfo);
}

bool ASTUBaseWeapon::CanReload() const
{
	return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool ASTUBaseWeapon::IsAmmoFull() const
{
	return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

bool ASTUBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
	if(CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;

	if(IsAmmoEmpty())
	{
		UE_LOG(LogWeapon, Display, TEXT("Ammo was empty"));
		CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
		OnClipEmpty.Broadcast(this);
	}
	else if(CurrentAmmo.Clips < DefaultAmmo.Clips)
	{
		const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
		if(DefaultAmmo.Clips - NextClipsAmount >= 0)
		{
			CurrentAmmo.Clips = NextClipsAmount;
			UE_LOG(LogWeapon, Display, TEXT("Clips were added"));
		}
		else
		{
			CurrentAmmo.Clips = DefaultAmmo.Clips;
			CurrentAmmo.Bullets = DefaultAmmo.Bullets;
			UE_LOG(LogWeapon, Display, TEXT("Ammo is full now"));
		}
	}
	else
	{
		UE_LOG(LogWeapon, Display, TEXT("Bullets were added"));
		CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	}

	return true;
}

UNiagaraComponent* ASTUBaseWeapon::SpawnMuzzleFX()
{
	return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX,
	                                                    WeaponMesh,
	                                                    MuzzleSocketName,
	                                                    FVector::ZeroVector,
	                                                    FRotator::ZeroRotator,
	                                                    EAttachLocation::SnapToTarget,
	                                                    true);
}
