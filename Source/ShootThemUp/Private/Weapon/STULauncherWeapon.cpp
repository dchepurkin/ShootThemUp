// Shoot Them Up Game. All Right Reserved

#include "Weapon/STULauncherWeapon.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "STUProjectile.h"
#include "Sound/SoundCue.h"

void ASTULauncherWeapon::StartFire()
{
	Super::StartFire();
	MakeShot();
}

void ASTULauncherWeapon::MakeShot()
{
	if(!GetWorld()) return;

	if(IsAmmoEmpty())
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
		return;
	}

	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : HitResult.TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
	if(!Projectile) return;

	Projectile->SetShotDirection(Direction);
	Projectile->SetOwner(GetOwner());
	Projectile->FinishSpawning(SpawnTransform);

	DecreaseAmmo();
	SpawnMuzzleFX();

	UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}
