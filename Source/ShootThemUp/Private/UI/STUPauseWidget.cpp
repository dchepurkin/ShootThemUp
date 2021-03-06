// Shoot Them Up Game. All Right Reserved

#include "UI/STUPauseWidget.h"
#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPauseWidget, All, All)

void USTUPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	const auto InitStatus = Super::Initialize();

	if(ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);
	}
}

void USTUPauseWidget::OnClearPause()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
