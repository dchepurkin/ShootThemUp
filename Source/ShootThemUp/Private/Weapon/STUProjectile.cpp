// Shoot Them Up Game. All Right Reserved

#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "STUWeaponFXComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->InitSphereRadius(5.0f);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SphereComponent->bReturnMaterialOnMove = true;
	SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);
	SetRootComponent(SphereComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed = 2000;
	MovementComponent->ProjectileGravityScale = 0.0f;

	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFxComponent");
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();
	MovementComponent->Velocity = ShootDirection * MovementComponent->InitialSpeed;

	SphereComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectileHit);

	SetLifeSpan(LifeSeconds);

	check(WeaponFXComponent);
}

void ASTUProjectile::SetShotDirection(const FVector& Direction)
{
	ShootDirection = Direction;
}

void ASTUProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(!GetWorld()) return;

	MovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), DamageRadiust,
	                                    UDamageType::StaticClass(), {GetOwner()}, this, GetController(), DoFoolDamage);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadiust, 24, FColor::Red, false, 5.0f, 0.0f, 2.0f);
	WeaponFXComponent->PlayImpactFX(Hit);

	Destroy();
}

AController* ASTUProjectile::GetController()
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
