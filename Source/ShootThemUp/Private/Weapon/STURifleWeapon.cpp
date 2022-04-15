// Shoot Them Up Game. All Right Reserved

#include "Weapon/STURifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "STUWeaponFXComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFxComponent");
}

void ASTURifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponFXComponent);
}

void ASTURifleWeapon::StartFire()
{
    Super::StartFire();
    GetWorldTimerManager().SetTimer(FireTimer, this, &ASTURifleWeapon::MakeShot, FireRate, true);
    MakeShot();
}

void ASTURifleWeapon::StopFire()
{
    Super::StopFire();
    GetWorldTimerManager().ClearTimer(FireTimer);
}

void ASTURifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit)
    {
        MakeDamage(HitResult);
        WeaponFXComponent->PlayImpactFX(HitResult);
        //DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
       // DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 24, FColor::Red, false, 3.0f);
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    }

    DecreaseAmmo();
}

bool ASTURifleWeapon::GetTraceData(FVector &TraceStart, FVector &TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;

    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return false;

    TraceStart = ViewLocation;
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void ASTURifleWeapon::MakeDamage(FHitResult &HitResult) const
{
    const auto Target = Cast<ACharacter>(HitResult.GetActor());
    if (!Target)
        return;
    Target->TakeDamage(WeaponDamage, FDamageEvent(), GetPlayerController(), GetOwner());
}
