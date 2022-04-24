// Shoot Them Up Game. All Right Reserved

#include "UI/STUBaseWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void USTUBaseWidget::Show()
{
	PlayAnimation(ShowAnimation);
	if(!GetWorld()) return;

	UGameplayStatics::PlaySound2D(GetWorld(), OpenSound);
}
