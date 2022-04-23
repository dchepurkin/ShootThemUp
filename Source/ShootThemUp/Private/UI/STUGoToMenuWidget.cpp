// Shoot Them Up Game. All Right Reserved

#include "UI/STUGoToMenuWidget.h"
#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGoToMenuWidget, All, All)

void USTUGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::OnGoToMenu);
	}
}

void USTUGoToMenuWidget::OnGoToMenu()
{
	const auto GameInstance = GetGameInstance<USTUGameInstance>();
	if(!GameInstance) return;

	if(GameInstance->GetMainMenuLevelName().IsNone())
	{
		UE_LOG(LogSTUGoToMenuWidget, Error, TEXT("Main menu level name is NONE"));
		return;
	}

	if(!GetWorld()) return;

	UGameplayStatics::OpenLevel(GetWorld(), GameInstance->GetMainMenuLevelName());
}
