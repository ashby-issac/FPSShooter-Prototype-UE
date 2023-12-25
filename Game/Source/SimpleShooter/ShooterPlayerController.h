// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

class UUserWidget;

UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AShooterPlayerController();

	virtual void GameHasEnded(class AActor *EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PlayerWinWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> PlayerLoseWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UUserWidget* PlayerWidget;

	UPROPERTY(EditDefaultsOnly)
	float RestartDelay = 3.f;

	void AddWidgetToViewport(TSubclassOf<UUserWidget> PlayerWidgetClass);
};
