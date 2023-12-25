// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_PlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
    NodeName = TEXT("Player");

    CharacterPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UBlackboardComponent *BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (/*!CharacterPawn || */!BlackboardComp)
    {
        UE_LOG(LogTemp, Warning, TEXT("Character Pawn is null"));
        return;
    }

    AAIController *AIShooterController = OwnerComp.GetAIOwner();
    if (!AIShooterController)
    {
        return;
    }

    if (AIShooterController->LineOfSightTo(CharacterPawn) && !IsCharacterDead())
    {
        BlackboardComp->SetValueAsObject(GetSelectedBlackboardKey(), CharacterPawn);
    }
    else
    {
        BlackboardComp->ClearValue(GetSelectedBlackboardKey());
    }
}

bool UBTService_PlayerLocation::IsCharacterDead() const
{
    AShooterCharacter *ShooterCharacter = Cast<AShooterCharacter>(CharacterPawn);
    if (!ShooterCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("ShooterCharacter is null"));
        return true;
    }
    return ShooterCharacter->IsDead();
}