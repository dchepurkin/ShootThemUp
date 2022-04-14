// Shoot Them Up Game. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
    GENERATED_BODY()

  public:
    virtual void StartFire() override;
    virtual void StopFire() override;

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BulletSpread = 1.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0"))
    float WeaponDamage = 10.0f; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.1"))
    float FireRate = 0.1f;

    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const override;

    void MakeDamage(FHitResult &HitResult) const;    

  private:
    FTimerHandle FireTimer;
};
