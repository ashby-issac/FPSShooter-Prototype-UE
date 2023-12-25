
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();

	void PullTrigger();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* SkeletalMesh;

	class APlayerController* PC;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* FireFX;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* HitFX;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* FireSFX;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* HitSFX;

	UPROPERTY(EditDefaultsOnly)
	float DamageAmt = 7.f;

	float MaxRange = 1000.f;
	UWorld *MyWorld;
	AController *PawnController;

	bool IsLineTraceHit(FHitResult& HitInfo, FVector& Location, FRotator& Rotation);
};
