// Shoot Them Up Game. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGameInfoWidget.generated.h"

class ASTUGameModeBase;
class ASTUPlayerState;

UCLASS()
class SHOOTTHEMUP_API USTUGameInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="UI")
	void GetRoundInfo(int32& TotalRoundsNum, int32& CurrentRoundNum) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	void GetTimeInfo(int32& RoundCountDown) const;

	UFUNCTION(BlueprintCallable, Category="UI")
	void GetKillsInfo(int32& Kills) const;

private:
	ASTUGameModeBase* GetGameMode() const;
	ASTUPlayerState* GetPlayerState() const;
};
