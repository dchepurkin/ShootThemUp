// Shoot Them Up Game. All Right Reserved

#include "Player/STUPlayerController.h"

#include "STUGameInstance.h"
#include "STUGameModeBase.h"
#include "Components/STURespawnComponent.h"

ASTUPlayerController::ASTUPlayerController()
{
	STURespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}

void ASTUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(GetWorld() && GetWorld()->GetAuthGameMode<ASTUGameModeBase>())
	{
		GetWorld()->GetAuthGameMode<ASTUGameModeBase>()->OnMatchStateChanged.AddUObject(
			this, &ASTUPlayerController::OnMatchStateChanged);
	}
}

void ASTUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if(!InputComponent) return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
	InputComponent->BindAction("Mute", IE_Pressed, this, &ASTUPlayerController::OnMuteSound);
}

void ASTUPlayerController::OnPauseGame()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASTUPlayerController::OnMatchStateChanged(ESTUMatchState State)
{
	if(State == ESTUMatchState::InProgress)
	{
		SetShowMouseCursor(false);
		SetInputMode(FInputModeGameOnly());
	}
	else
	{
		SetShowMouseCursor(true);
		SetInputMode(FInputModeUIOnly());
	}
}

void ASTUPlayerController::OnMuteSound()
{
	if(!GetWorld()) return;
	
	const auto GameInstance = GetGameInstance<USTUGameInstance>();
	if(!GameInstance) return;

	GameInstance->ToggleVolume();
}
