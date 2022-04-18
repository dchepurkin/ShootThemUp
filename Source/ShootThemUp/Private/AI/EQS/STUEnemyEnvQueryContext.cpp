// Shoot Them Up Game. All Right Reserved

#include "AI/EQS/STUEnemyEnvQueryContext.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void USTUEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

	const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if(!Blackboard) return;

	const auto ContextActor = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKeyName));
	if(!ContextActor) return;

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, ContextActor);
}
