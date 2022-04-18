// Shoot Them Up Game. All Right Reserved

#include "Components/STUHealthComponent.h"
#include "Gameframework/Actor.h"
#include "Gameframework/Pawn.h"
#include "Gameframework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float USTUHealthComponent::GetHealth() const
{
	return Health;
}

bool USTUHealthComponent::IsDead() const
{
	return FMath::IsNearlyZero(Health);
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxHealth > 0);

	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();

	if(ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                          AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0 || IsDead() || !GetWorld()) return;

	SetHealth(Health - Damage);
	GetWorld()->GetTimerManager().ClearTimer(AutoHealTimer);

	if(IsDead())
	{
		OnDeath.Broadcast();
	}
	else if(AutoHealEnabled)
	{
		GetWorld()->GetTimerManager().SetTimer(AutoHealTimer, this, &USTUHealthComponent::AutoHeal, HealUpdateTime,
		                                       true, HealDelay);
	}

	PlayCameraShake();
}

void USTUHealthComponent::AutoHeal()
{
	SetHealth(Health + HealModifier);

	if(IsHealthFull())
	{
		GetOwner()->GetWorldTimerManager().ClearTimer(AutoHealTimer);
	}
}

bool USTUHealthComponent::TryToAddHealth(const float HealAmount)
{
	if(IsDead() || IsHealthFull()) return false;
	SetHealth(Health + HealAmount);
	return true;
}

void USTUHealthComponent::SetHealth(const float NewHealth)
{
	const auto NextHealth = FMath::Clamp<float>(NewHealth, 0.0f, MaxHealth);
	const auto HealthDelta = NextHealth - Health;
	Health = NextHealth;	
	OnHealthChanged.Broadcast(Health, HealthDelta);
}

float USTUHealthComponent::GetHealthPercent() const { return Health / MaxHealth; }

bool USTUHealthComponent::IsHealthFull() const { return FMath::IsNearlyEqual(Health, MaxHealth); }

void USTUHealthComponent::PlayCameraShake() const
{
	if(IsDead()) return;

	const auto Player = Cast<APawn>(GetOwner());
	if(!Player) return;

	const auto Controller = Player->GetController<APlayerController>();
	if(!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}
