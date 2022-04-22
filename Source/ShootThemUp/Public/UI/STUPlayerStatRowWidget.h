// Shoot Them Up Game. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SHOOTTHEMUP_API USTUPlayerStatRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlayerName(const FText& Text);
	void SetKills(const FText& Text);
	void SetDeaths(const FText& Text);
	void SetTeamID(const FText& Text);
	void SetPlayerIndicatorVisibility(bool Visibile);

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PlayerNameTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* KillsTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* DeathsTextBlock;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* TeamIDBlock;

	UPROPERTY(meta=(BindWidget))
	UImage* PlayerIndicator;
};
