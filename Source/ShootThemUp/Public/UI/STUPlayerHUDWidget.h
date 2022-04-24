// Shoot Them Up Game. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

class UProgressBar;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public USTUBaseWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="UI")
	float GetHealthPercet() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetWeaponUIData(FWeaponUIData& UIData) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool GetWeaponAmmoData(FAmmoData& AmmoData) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsPlayerAlive() const;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool IsPlayerSpectating() const;

	UFUNCTION(BlueprintImplementableEvent, Category="UI")
	void OnTakeDamage();

	UFUNCTION(BlueprintCallable, Category="UI")
	void GetKillsNum(int32& Kills) const;

protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* DamageAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=UI)
	float PercentColorThreshold = 0.3f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=UI)
	FLinearColor GoodColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=UI)
	FLinearColor BadColor = FLinearColor::Red;

	virtual void NativeOnInitialized() override;

private:
	void OnHealthChanged(float Health, float HealthDelta);
	void OnNewPawn(APawn* Pawn);
	void UpdateHealthBar();
};
