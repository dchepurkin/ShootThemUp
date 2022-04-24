// Shoot Them Up Game. All Right Reserved

#include "UI/STUPlayerHUDWidget.h"

#include "STUHealthComponent.h"
#include "STUWeaponComponent.h"
#include "STUUtils.h"
#include "Components/ProgressBar.h"

void USTUPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn()); //функция Initialize вызывается после OnPossess поэтому нужно в первый раз явно вызвать функцию OnNewPawn
	}
}

void USTUPlayerHUDWidget::OnNewPawn(APawn* Pawn)
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(Pawn);
	if(HealthComponent)
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
	}
	UpdateHealthBar();
}

void USTUPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if(HealthDelta < 0.0f)
	{
		OnTakeDamage();
		if(!IsAnimationPlaying(DamageAnimation))
		{
			PlayAnimation(DamageAnimation);
		}
	}
	UpdateHealthBar();
}

float USTUPlayerHUDWidget::GetHealthPercet() const
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if(!WeaponComponent) return false;

	return WeaponComponent->GetWeaponUIData(UIData);
}

bool USTUPlayerHUDWidget::GetWeaponAmmoData(FAmmoData& AmmoData) const
{
	const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
	if(!WeaponComponent) return false;

	return WeaponComponent->GetWeaponAmmoData(AmmoData);
}

bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
	const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
	return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
	const auto Controller = GetOwningPlayer();
	return Controller && Controller->GetStateName() == NAME_Spectating;
}

void USTUPlayerHUDWidget::UpdateHealthBar()
{
	if(HealthProgressBar)
	{
		HealthProgressBar->SetFillColorAndOpacity(GetHealthPercet() > PercentColorThreshold ? GoodColor : BadColor);
	}
}

void USTUPlayerHUDWidget::GetKillsNum(int32& Kills) const
{
	const auto Controller = GetOwningPlayer();
	if(!Controller) return;

	const auto PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
	if(!PlayerState) return;

	Kills = PlayerState->GetKillsNum();
}
