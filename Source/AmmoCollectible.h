// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectible.h"
#include "AmmoCollectible.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AAmmoCollectible : public ACollectible
{
	GENERATED_BODY()
	
protected:
	/*Sets up interaction with player to add Ammo to Reserves*/
	virtual void InteractWithPlayer(AShooterCharacter *ShooterCharacter) override;

	UPROPERTY(EditDefaultsOnly)
	int AmmoAmount = 10;
};
