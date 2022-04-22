// Shoot Them Up Game. All Right Reserved

#include "Menu/STUMenuPlayerController.h"

void ASTUMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}
