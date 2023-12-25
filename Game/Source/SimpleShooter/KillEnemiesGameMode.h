// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEnemiesGameMode.generated.h"

/**
 *
 */
UCLASS()
class SIMPLESHOOTER_API AKillEnemiesGameMode : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn *KilledPawn) override;

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool IsGameOver);

private:

	void EndGame(bool HasPlayerWon);
};
