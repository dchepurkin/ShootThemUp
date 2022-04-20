// Shoot Them Up Game. All Right Reserved

#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPlayerState, All, All)

void ASTUPlayerState::LogInfo() const
{
	UE_LOG(LogSTUPlayerState, Display, TEXT("Team ID: %i, Kills: %i, Death: %i"), TeamID, KillsNum, DeathsNum);
}
