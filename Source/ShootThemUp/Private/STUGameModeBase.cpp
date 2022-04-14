// Shoot Them Up Game. All Right Reserved

#include "STUGameModeBase.h"
#include "Player/STUBaseCharacter.h"
#include "UI/STUGameHUD.h"
#include "Player/STUPlayerController.h"


ASTUGameModeBase::ASTUGameModeBase()
{
    DefaultPawnClass = ASTUBaseCharacter::StaticClass();
    PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
}