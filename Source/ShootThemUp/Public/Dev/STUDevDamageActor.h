// Shoot Them Up Game. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
    GENERATED_BODY()

  public:
    ASTUDevDamageActor();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    USceneComponent *SceneComponent;

    UPROPERTY(EditInstanceOnly)
    float Radius = 300.0f;

    UPROPERTY(EditInstanceOnly)
    bool DoFullDamage = true;

    UPROPERTY(EditInstanceOnly, meta = (ClampMin = "0.0", ClampMax = "10000.0"))
    float BaseDamage = 0.1f;

    UPROPERTY(EditInstanceOnly)
    FColor SphereColor = FColor::Red;

    UPROPERTY(EditInstanceOnly)
    TSubclassOf<UDamageType> DamageType;

        protected : virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;

  private:
};
