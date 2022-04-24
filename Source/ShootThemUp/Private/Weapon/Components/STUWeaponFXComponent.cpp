// Shoot Them Up Game. All Right Reserved

#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Sound/SoundCue.h"

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& HitResult)
{
	auto ImpactData = DefaultImpactData;

	if(HitResult.PhysMaterial.IsValid())
	{
		const auto PhysMat = HitResult.PhysMaterial.Get();
		if(ImpactDataMap.Contains(PhysMat)) { ImpactData = ImpactDataMap[PhysMat]; }
	}

	//niagara
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
	                                               ImpactData.NiagaraEffect,
	                                               HitResult.ImpactPoint,
	                                               HitResult.ImpactNormal.Rotation());

	//decal
	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
	                                                             ImpactData.DecalData.Material,
	                                                             ImpactData.DecalData.Size,
	                                                             HitResult.ImpactPoint,
	                                                             HitResult.ImpactNormal.Rotation());
	if(DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}

	//sound
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactData.ImpactSound, HitResult.ImpactPoint);
}
