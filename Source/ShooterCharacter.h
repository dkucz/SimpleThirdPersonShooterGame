// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
class AController;
struct FDamageEvent;


UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, const FDamageEvent &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;
	
	void Shoot();

	void Reload();

	/*Resets the players ability to fire when reloading is complete*/
	void ResetFire();

	UFUNCTION(BlueprintPure)
	int GetAmmoCount() const;

	UFUNCTION(BlueprintPure)
	bool GetIsReloading() const;

	UFUNCTION(BlueprintPure)
	FTimerHandle GetReloadTimerHandle() const;

	UFUNCTION(BlueprintPure)
	int GetAmmoReserve() const;

	UFUNCTION(BlueprintPure)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintPure)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float HealthToSet);

	void AddAmmoToReserve(int AmmoToAdd);

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	
	UPROPERTY(EditAnywhere)
	float RotationRate = 10;
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	struct FTimerHandle ReloadTimerHandle;

	bool bIsReloading;
};
