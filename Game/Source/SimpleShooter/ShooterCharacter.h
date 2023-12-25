// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AShooterCharacter();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	void Fire();
	void OnDeathActions();
	// virtual float TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY(VisibleAnywhere) 
	float MaxHealth;

	UPROPERTY(VisibleAnywhere) 
	float Health;

	float RotateRate = 20.f;
	class APlayerController *PC;
	class UHealthComponent* HealthComp;
	AGun *Gun;

	void MoveVertical(float Value);
	void MoveHorizontal(float Value);

	void MoveJoystickVertical(float Value);
	void MoveJoystickHorizontal(float Value);
};
