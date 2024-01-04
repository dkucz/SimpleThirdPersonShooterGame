// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectible.h"
#include "HealthCollectible.generated.h"


/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AHealthCollectible : public ACollectible
{
	GENERATED_BODY()

protected:
	/*Sets up interaction with player when collision occurs*/
	virtual void InteractWithPlayer(AShooterCharacter* ShooterCharacter) override;

	UPROPERTY(EditDefaultsOnly)
	float HealthAmount = 25.0f;

};
