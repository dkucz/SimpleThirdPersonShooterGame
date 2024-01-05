// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	bIsReloading = false;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Reload);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController *EventInstigator, AActor *DamageCauser) 
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if (IsDead())
	{
		ASimpleShooterGameModeBase *GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

void AShooterCharacter::MoveForward(const float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(const float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(const float AxisValue) 
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(const float AxisValue) 
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot() 
{
	if (!bIsReloading)
	{
		Gun->PullTrigger();
	}
}

void AShooterCharacter::Reload()
{
	if (!bIsReloading && (GetAmmoReserve() > 0) && (GetAmmoCount < 30))
	{
		bIsReloading = true;
		const float ReloadTime = Gun->GetReloadTime();
		GetWorld()->GetTimerManager().SetTimer(
			ReloadTimerHandle, 
			this,
			&AShooterCharacter::ResetFire,
			ReloadTime,
			false);
	}
}

void AShooterCharacter::ResetFire()
{
	bIsReloading = false;
	GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
	Gun->ReloadGun();
}

int AShooterCharacter::GetAmmoCount() const
{
	return Gun->GetAmmoCount();
}

bool AShooterCharacter::GetIsReloading() const
{
	return bIsReloading;
}

FTimerHandle AShooterCharacter::GetReloadTimerHandle() const
{
	return ReloadTimerHandle;
}

int AShooterCharacter::GetAmmoReserve() const {
	return Gun->GetAmmoReserve();
}

float AShooterCharacter::GetMaxHealth() const {
	return MaxHealth;
}

float AShooterCharacter::GetHealth() const {
	return Health;
}

void AShooterCharacter::SetHealth(const float HealthToSet)
{
	Health = HealthToSet;
}

void AShooterCharacter::AddAmmoToReserve(const int AmmoToAdd)
{
	Gun->AddAmmoToReserve(AmmoToAdd);
}
