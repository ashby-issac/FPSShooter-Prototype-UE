// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIShooterController.generated.h"

/**
 *
 */
class UBehaviorTree;

UCLASS()
class SIMPLESHOOTER_API AAIShooterController : public AAIController
{
	GENERATED_BODY()

public:
	AAIShooterController();

	virtual void Tick(float DeltaTime) override;

	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UBehaviorTree *AIBehaviour;

	APawn *PlayerPawn;
	APawn* AIShooterPawn;

	bool IsPlayerVisible() const;
};
