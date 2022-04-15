// Shoot Them Up Game. All Right Reserved

#include "Pickups/STUBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All)

ASTUBasePickup::ASTUBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->SetSphereRadius(CollisionRadius);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetGenerateOverlapEvents(true);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	SetRootComponent(CollisionComponent);
}

void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent);

	GenerationRotationYaw();
}

void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}

bool ASTUBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	const auto Pawn = Cast<APawn>(OtherActor);
	if(GivePickupTo(Pawn)) { PickupWasTaken(); };
}

void ASTUBasePickup::PickupWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	if(GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);
}

void ASTUBasePickup::Respawn()
{
	GenerationRotationYaw();
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	if(GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
}

void ASTUBasePickup::GenerationRotationYaw()
{
	const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
	RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}
