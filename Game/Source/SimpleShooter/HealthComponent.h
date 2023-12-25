
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMPLESHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const { return Health; }

private:
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 50.f;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UFUNCTION()
	void DamageTaken(AActor *DamagedActor, float BaseDamage, AController* Controller, 
										FVector HitLocation, UPrimitiveComponent* PrimitiveComp, FName BoneName, 
										FVector ShotFromDirection, const class UDamageType* DamageType, 
										AActor* DamageCauser);
};
