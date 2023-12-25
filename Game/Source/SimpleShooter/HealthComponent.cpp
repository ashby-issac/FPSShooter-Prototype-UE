
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "ShooterCharacter.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;

	GetOwner()->OnTakePointDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor *DamagedActor, float BaseDamage, AController *Controller,
								   FVector HitLocation, UPrimitiveComponent *PrimitiveComp, FName BoneName,
								   FVector ShotFromDirection, const class UDamageType *DamageType,
								   AActor *DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("DamageTaken"));
	Health = Health < 1 ? 0 : Health -= BaseDamage;
	if (Health < 1)
	{
		auto CastedDamagedActor = Cast<AShooterCharacter>(DamagedActor);
		if (!CastedDamagedActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("DamagedActor Cast Failed"));
			return;
		}
		CastedDamagedActor->OnDeathActions();
		return;
	}
}
