// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_LastPlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_LastPlayerLocation::UBTService_LastPlayerLocation()
{
    NodeName = TEXT("LastPlayerLocation");

    CharacterPawn = UGameplayStatics::GetPlayerPawn(this, 0);
}

void UBTService_LastPlayerLocation::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if (!CharacterPawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("Character Pawn is null"));
        return;
    }
    OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), CharacterPawn);
}
