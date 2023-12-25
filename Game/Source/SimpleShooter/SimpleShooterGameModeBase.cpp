// Copyright Epic Games, Inc. All Rights Reserved.


#include "SimpleShooterGameModeBase.h"

void ASimpleShooterGameModeBase::PawnKilled(APawn* KilledPawn)
{
    UE_LOG(LogTemp, Warning, TEXT("SimpleShooterGameModeBase PawnKilled() %s"), *KilledPawn->GetName());
}
