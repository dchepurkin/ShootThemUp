// Shoot Them Up Game. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCoreTypes.h"
#include "STUGameInstance.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	const FLevelData& GetStartupLevel() const { return StartupLevel; }
	void SetStartupLevel(const FLevelData& Data) { StartupLevel = Data; }

	const TArray<FLevelData>& GetLevelsData() const { return LevelsData; }

	const FName& GetMainMenuLevelName() const { return MainMenuLevelName; }

protected:
	UPROPERTY(EditDefaultsOnly, Category="Game", meta=(ToolTip = "Level names must be unique"))
	TArray<FLevelData> LevelsData;

	UPROPERTY(EditDefaultsOnly, Category="Game")
	FName MainMenuLevelName = NAME_None;

private:
	FLevelData StartupLevel;
};
