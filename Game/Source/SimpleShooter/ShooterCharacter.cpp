
#include "ShooterCharacter.h"
#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Health = MaxHealth;
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	PC = UGameplayStatics::GetPlayerController(this, 0);
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weapon_rSocket"));
	Gun->SetOwner(this);
	HealthComp = Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()));

}

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveVertical", this, &AShooterCharacter::MoveVertical);
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &AShooterCharacter::MoveHorizontal);

	PlayerInputComponent->BindAxis("MouseX", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("MouseY", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("JoystickMouseX", this, &AShooterCharacter::MoveJoystickVertical);
	PlayerInputComponent->BindAxis("JoystickMouseY", this, &AShooterCharacter::MoveJoystickHorizontal);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AShooterCharacter::Fire);
}

void AShooterCharacter::Fire()
{
	Gun->PullTrigger();
}

void AShooterCharacter::MoveVertical(float Value)
{
	if (PC->IsInputKeyDown(EKeys::LeftShift)) {
		Value /= 4;
	}
	AddMovementInput(GetActorForwardVector() * Value);
}

void AShooterCharacter::MoveHorizontal(float Value)
{
	if (PC->IsInputKeyDown(EKeys::LeftShift)) {
		Value /= 4;
	}
	AddMovementInput(GetActorRightVector() * -Value);
}

void AShooterCharacter::MoveJoystickVertical(float Value)
{
	AddControllerPitchInput(Value * RotateRate * UGameplayStatics::GetWorldDeltaSeconds(this));
}

void AShooterCharacter::MoveJoystickHorizontal(float Value)
{
	AddControllerYawInput(Value * RotateRate * UGameplayStatics::GetWorldDeltaSeconds(this));
}

bool AShooterCharacter::IsDead() const
{
	if (HealthComp == nullptr) return false;
	UE_LOG(LogTemp, Warning, TEXT("ShooterCharacter %s : %f"), *this->GetName(), HealthComp->GetCurrentHealth());
	return HealthComp->GetCurrentHealth() < 1;
}

void AShooterCharacter::OnDeathActions()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ASimpleShooterGameModeBase* SSGameModeBase = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();

	if (SSGameModeBase)
	{
		SSGameModeBase->PawnKilled(this);
		DetachFromControllerPendingDestroy();
	}
}

// float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
// {
// 	UE_LOG(LogTemp, Warning, TEXT("Overridden TakeDamage"));
// 	float AppliedDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
// 	Health = Health < 1 ? 0 : Health -= AppliedDamage;
// 	return AppliedDamage;
// }

