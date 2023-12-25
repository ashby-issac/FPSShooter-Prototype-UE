// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"

AShooterPlayerController::AShooterPlayerController()
{
}

void AShooterPlayerController::GameHasEnded(AActor *EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    auto PlayerWidgetClass = bIsWinner ? PlayerWinWidgetClass : PlayerLoseWidgetClass;
    AddWidgetToViewport(PlayerWidgetClass);

    // FTimerHandle TimerHandle;
    // GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerController::RestartLevel, RestartDelay);
}

void AShooterPlayerController::AddWidgetToViewport(TSubclassOf<UUserWidget> PlayerWidgetClass)
{
    if (PlayerWidget)
    {
        PlayerWidget->RemoveFromViewport();
    }
    PlayerWidget = CreateWidget(this, PlayerWidgetClass);
    PlayerWidget->AddToViewport();
}

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    AddWidgetToViewport(HUDWidgetClass);
}