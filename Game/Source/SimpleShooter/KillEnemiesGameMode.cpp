// Fill out your copyright notice in the Description page of Project Settings.

#include "KillEnemiesGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterPlayerController.h"
#include "AIShooterController.h"
#include "EngineUtils.h"

void AKillEnemiesGameMode::PawnKilled(APawn *KilledPawn)
{
    Super::PawnKilled(KilledPawn);

    APlayerController *PlayerController = Cast<APlayerController>(KilledPawn->GetController());
    if (PlayerController)
    {
        EndGame(false);
    }
    else
    {
        for (AAIShooterController *ShooterController : TActorRange<AAIShooterController>(GetWorld()))
        {
            if (!ShooterController->IsDead())
            {
                return;
            }
        }
        EndGame(true);
    }
}

void AKillEnemiesGameMode::EndGame(bool bIsPlayerWin)
{
    for (AController *Controller : TActorRange<AController>(GetWorld()))
    {
        bool tempIsPlayerWinner = Controller->IsPlayerController() == bIsPlayerWin;
        Controller->GameHasEnded(Controller->GetPawn(), tempIsPlayerWinner);
    }
}
