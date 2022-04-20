// Shoot Them Up Game. All Right Reserved

#include "UI/STUSpectatorWidget.h"
#include "STURespawnComponent.h"
#include "STUUtils.h"

bool USTUSpectatorWidget::GetRespawnTime(int32& RespawnTime) const
{
	const auto RespawnComponent = STUUtils::GetSTUPlayerComponent<USTURespawnComponent>(GetOwningPlayer());
	if(!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

	RespawnTime = RespawnComponent->GetRespawnCountDown();
	return true;
}
