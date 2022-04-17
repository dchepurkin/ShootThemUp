// Shoot Them Up Game. All Right Reserved

#include "AI/Services/STUChangeWeaponService.h"
#include "AIController.h"
#include "STUAIWeaponComponent.h"
#include "STUUtils.h"
#include "Kismet/KismetMathLibrary.h"

USTUChangeWeaponService::USTUChangeWeaponService()
{
	NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if(Controller)
	{
		const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUAIWeaponComponent>(Controller->GetPawn());
		if(WeaponComponent && UKismetMathLibrary::RandomBoolWithWeight(Probability))
		{
			WeaponComponent->NextWeapon();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
