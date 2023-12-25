
#include "Gun.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMesh->SetupAttachment(RootComponent);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();

	MyWorld = GetWorld();
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
	FVector Location;
	FRotator Rotation;

	if (FireFX && FireSFX)
	{
		UGameplayStatics::SpawnEmitterAttached(FireFX, SkeletalMesh, TEXT("MuzzleFlashSocket"));
		UGameplayStatics::SpawnSoundAttached(FireSFX, SkeletalMesh, TEXT("MuzzleFlashSocket"));
	}

	FHitResult HitInfo;
	if (IsLineTraceHit(HitInfo, Location, Rotation))
	{
		FVector ShotDirection = -Rotation.Vector();
		if (HitFX && HitSFX)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSFX, HitInfo.ImpactPoint, ShotDirection.Rotation());
			UGameplayStatics::SpawnEmitterAtLocation(MyWorld, HitFX, HitInfo.ImpactPoint, ShotDirection.Rotation());
		}
		AActor *HitActor = HitInfo.GetActor();
		if (HitActor != nullptr)
		{
			// FPointDamageEvent DamageEvent = FPointDamageEvent(DamageAmt, HitInfo, ShotDirection, nullptr);
			// HitActor->TakeDamage(DamageAmt, DamageEvent, Controller, this);
			UGameplayStatics::ApplyPointDamage(HitActor, DamageAmt, ShotDirection,
											   HitInfo, PawnController, this, UDamageType::StaticClass());
		}
	}
}

bool AGun::IsLineTraceHit(FHitResult &HitInfo, FVector &Location, FRotator &Rotation)
{
	APawn *PawnActor = Cast<APawn>(GetOwner());
	if (!PawnActor)
		return false;

	PawnController = PawnActor->GetController();
	if (!PawnController)
		return false;

	PawnController->GetPlayerViewPoint(Location, Rotation);

	FVector EndPoint = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return MyWorld->LineTraceSingleByChannel(HitInfo, Location, EndPoint,
											 ECollisionChannel::ECC_GameTraceChannel1,
											 Params);
}