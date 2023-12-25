// Fill out your copyright notice in the Description page of Project Settings.

#include "AIShooterController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

AAIShooterController::AAIShooterController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AAIShooterController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehaviour == nullptr)
    {
        return;
    }
    
    RunBehaviorTree(AIBehaviour);
    GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}

void AAIShooterController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

bool AAIShooterController::IsPlayerVisible() const
{
    return LineOfSightTo(PlayerPawn);
}

bool AAIShooterController::IsDead() const
{
    AShooterCharacter *ShooterPawn = Cast<AShooterCharacter>(GetPawn());
    if (ShooterPawn)
    {
        return ShooterPawn->IsDead();
    }
    return true;
}