// Shoot Them Up Game. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USTUWeaponFXComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
    GENERATED_BODY()

  public:
    ASTUProjectile();
    void SetShotDirection(const FVector &Direction);

  protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category="VFX")
    USTUWeaponFXComponent* WeaponFXComponent;

    UPROPERTY(VisibleAnywhere, Category = "Weaopn")
    USphereComponent *SphereComponent;

    UPROPERTY(VisibleAnywhere, Category = "Weaopn")
    UProjectileMovementComponent *MovementComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weaopn")
    float DamageRadiust = 200.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weaopn")
    float DamageAmount = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weaopn")
    bool DoFoolDamage = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weaopn")
    float LifeSeconds = 5.0f;

  private:
    FVector ShootDirection = FVector::ZeroVector;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
                         UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);

    AController *GetController();
};
