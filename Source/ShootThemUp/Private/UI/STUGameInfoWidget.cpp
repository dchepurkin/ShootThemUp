// Shoot Them Up Game. All Right Reserved

#include "UI/STUGameInfoWidget.h"
#include "STUGameModeBase.h"
#include "STUPlayerState.h"

ASTUGameModeBase* USTUGameInfoWidget::GetGameMode() const
{
	return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTUPlayerState* USTUGameInfoWidget::GetPlayerState() const
{
	return GetOwningPlayer() ? GetOwningPlayer()->GetPlayerState<ASTUPlayerState>() : nullptr;
}

void USTUGameInfoWidget::GetRoundInfo(int32& TotalRoundsNum, int32& CurrentRoundNum) const
{
	const auto GameMod = GetGameMode();
	if(!GameMod) return;

	GameMod->GetRoundInfo(TotalRoundsNum, CurrentRoundNum);
}

void USTUGameInfoWidget::GetTimeInfo(int32& RoundCountDown) const
{
	const auto GameMod = GetGameMode();
	if(!GameMod) return;

	GameMod->GetTimeInfo(RoundCountDown);
}
