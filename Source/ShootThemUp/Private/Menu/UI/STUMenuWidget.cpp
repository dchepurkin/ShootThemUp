// Shoot Them Up Game. All Right Reserved

#include "Menu/UI/STUMenuWidget.h"
#include "Components/Button.h"
#include "STUGameInstance.h"
#include "STULevelItemWidget.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUMenuWidget, All, All)

void USTUMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
	}

	if(QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
	}

	InitLevelItems();
}

void USTUMenuWidget::OnStartGame()
{
	PlayAnimation(HideAnimation);
}

void USTUMenuWidget::OnQuitGame()
{
	if(!GetWorld() || !GetOwningPlayer()) return;
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTUMenuWidget::InitLevelItems()
{
	if(!GetWorld()) return;

	const auto GameInstance = GetGameInstance<USTUGameInstance>();
	if(!GameInstance) return;

	checkf(GameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));
	if(!LevelItemsBox) return;

	LevelItemsBox->ClearChildren();
	for(const auto LevelData : GameInstance->GetLevelsData())
	{
		const auto LevelItemWidget = CreateWidget<USTULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
		if(!LevelItemWidget) continue;

		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelSelected);

		LevelItemsBox->AddChild(LevelItemWidget);

		LevelItemWidgets.Add(LevelItemWidget);
	}

	if(GameInstance->GetStartupLevel().LevelName.IsNone())
	{
		OnLevelSelected(GameInstance->GetLevelsData()[0]);
	}
	else
	{
		OnLevelSelected(GameInstance->GetStartupLevel());
	}
}

void USTUMenuWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto GameInstance = GetGameInstance<USTUGameInstance>();
	if(!GameInstance) return;

	GameInstance->SetStartupLevel(Data);

	for(const auto LevelItemWidget : LevelItemWidgets)
	{
		if(LevelItemWidget)
		{
			const auto IsSelected = LevelItemWidget->GetLevelData().LevelName == Data.LevelName;
			LevelItemWidget->SetSelected(IsSelected);
		}
	}
}

void USTUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if(Animation != HideAnimation) return;

	const auto STUGameInstance = GetGameInstance<USTUGameInstance>();
	if(!STUGameInstance) return;

	UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevel().LevelName);
}
