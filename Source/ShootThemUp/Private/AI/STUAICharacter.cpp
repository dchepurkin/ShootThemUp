// Shoot Them Up Game. All Right Reserved

#include "AI/STUAICharacter.h"
#include "BrainComponent.h"
#include "STUAIWeaponComponent.h"
#include "STUHealthBarWidget.h"
#include "STUHealthComponent.h"
#include "AI/STUAIController.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASTUAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBarWidgetComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASTUAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthBarWidgetComponent);
}

void ASTUAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateHealthWidgetVisibility();
}

void ASTUAICharacter::OnDeath()
{
	Super::OnDeath();

	const auto STUController = Cast<AAIController>(Controller);
	if(STUController && STUController->BrainComponent)
	{
		STUController->BrainComponent->Cleanup();
	}
}

void ASTUAICharacter::OnHealthChanged(float Health, float HealthDelta) const
{
	Super::OnHealthChanged(Health, HealthDelta);

	const auto HealthBarWidget = Cast<USTUHealthBarWidget>(HealthBarWidgetComponent->GetUserWidgetObject());
	if(!HealthBarWidget || !HealthComponent) return;
	
	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void ASTUAICharacter::UpdateHealthWidgetVisibility()
{
	if(!HealthBarWidgetComponent || !GetWorld() || !GetWorld()->GetFirstPlayerController()) return;

	const auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator();
	if(!PlayerPawn) return;

	const auto Distance = GetDistanceTo(PlayerPawn);

	HealthBarWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}
