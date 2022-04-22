// Shoot Them Up Game. All Right Reserved

#include "UI/STUPlayerStatRowWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
	if(!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetKills(const FText& Text)
{
	if(!KillsTextBlock) return;
	KillsTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetDeaths(const FText& Text)
{
	if(!DeathsTextBlock) return;
	DeathsTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetTeamID(const FText& Text)
{
	if(!TeamIDBlock) return;
	TeamIDBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visibile)
{
	if(!PlayerIndicator) return;
	PlayerIndicator->SetVisibility(Visibile ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
