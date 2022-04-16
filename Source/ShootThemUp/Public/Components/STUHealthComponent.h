// Shoot Them Up Game. All Right Reserved

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUHealthComponent();

	float GetHealth() const;
	bool TryToAddHealth(float HealAmount);
	bool IsHealthFull() const;

	UFUNCTION(BlueprintCallable, Category="Health")
	bool IsDead() const;

	UFUNCTION(BlueprintCallable, Category="Health")
	float GetHealthPercent() const;

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Auto Heal")
	bool AutoHealEnabled = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Auto Heal",
		meta = (ClampMin = "0.001", ClampMax = "10.0", EditCondition = "AutoHealEnabled"))
	float HealUpdateTime = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Auto Heal",
		meta = (ClampMin = "0.001", ClampMax = "10.0", EditCondition = "AutoHealEnabled"))
	float HealDelay = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Auto Heal",
		meta = (ClampMin = "0.001", ClampMax = "1000.0", EditCondition = "AutoHealEnabled"))
	float HealModifier = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;

private:
	float Health = 0.0f;

	FTimerHandle AutoHealTimer;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	                     class AController* InstigatedBy, AActor* DamageCauser);

	void AutoHeal();
	void SetHealth(float NewHealth);

	void PlayCameraShake() const;
};
