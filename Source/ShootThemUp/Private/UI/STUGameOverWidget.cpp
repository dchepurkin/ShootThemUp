// Shoot Them Up Game. All Right Reserved

#include "UI/STUGameOverWidget.h"
#include "STUGameModeBase.h"
#include "STUUtils.h"
#include "Components/Button.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameOverWidget, All, All)

void USTUGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(GetWorld())
	{
		const auto GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
		if(GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);
		}
	}

	if(ResetLevelButton)
	{
		ResetLevelButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnResetLevel);
	}
}

void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState State)
{
	if(State == ESTUMatchState::GameOver)
	{
		UpdatePlayerStat();
	}
}

void USTUGameOverWidget::UpdatePlayerStat()
{
	if(!GetWorld() || !PlayerStatBox) return;

	PlayerStatBox->ClearChildren();

	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if(!Controller)continue;

		const auto PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
		if(!PlayerState) continue;

		const auto PlayerStatRowWidget = CreateWidget<USTUPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
		if(!PlayerStatRowWidget) continue;

		PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
		PlayerStatRowWidget->SetKills(STUUtils::TextFromInt(PlayerState->GetKillsNum()));
		PlayerStatRowWidget->SetDeaths(STUUtils::TextFromInt(PlayerState->GetDeathsNum()));
		PlayerStatRowWidget->SetTeamID(STUUtils::TextFromInt(PlayerState->GetTeamID()));
		PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
		PlayerStatRowWidget->SetTeamColor(PlayerState->GetTeamColor());

		PlayerStatBox->AddChild(PlayerStatRowWidget);
	}
}

void USTUGameOverWidget::OnResetLevel()
{
	if(!GetWorld()) return;

	const auto CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(CurrentLevelName));
}
