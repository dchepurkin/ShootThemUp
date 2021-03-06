// Shoot Them Up Game. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "STUBasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickup : public AActor
{
	GENERATED_BODY()

public:
	ASTUBasePickup();

protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	float CollisionRadius = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup")
	float RespawnTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Pickup")
	USoundCue* PickupTakenSound;

public:
	virtual void Tick(float DeltaTime) override;

	bool CouldBeTaken() const;

private:
	float RotationYaw = 0.0f;
	FTimerHandle RespawnTimerHandle;

	virtual bool GivePickupTo(APawn* PlayerPawn);

	void PickupWasTaken();
	void Respawn();
	void GenerationRotationYaw();
};
