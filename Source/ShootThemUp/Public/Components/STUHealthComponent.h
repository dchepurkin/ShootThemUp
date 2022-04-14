// Shoot Them Up Game. All Right Reserved

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUHealthComponent();

	float GetHealth() const;

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
		meta = (ClampMin = "0.1", ClampMax = "10.0", EditCondition = "AutoHealEnabled"))
	float HealUpdateTime = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Auto Heal",
		meta = (ClampMin = "0.1", ClampMax = "10.0", EditCondition = "AutoHealEnabled"))
	float HealDelay = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Auto Heal",
		meta = (ClampMin = "0.001", ClampMax = "1000.0", EditCondition = "AutoHealEnabled"))
	float HealModifier = 2.0f;

private:
	float Health = 0.0f;

	FTimerHandle AutoHealTimer;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	                     class AController* InstigatedBy, AActor* DamageCauser);

	void Heal(float HealModifier);
	void AutoHeal();
	void SetHealth(float NewHealth);
};
