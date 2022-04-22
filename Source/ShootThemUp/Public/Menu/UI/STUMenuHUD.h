// Shoot Them Up Game. All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUMenuHUD.generated.h"

class UUserWidget;

UCLASS()
class SHOOTTHEMUP_API ASTUMenuHUD : public AHUD
{
	GENERATED_BODY()	

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> MenuWidgetClass;
	
};
