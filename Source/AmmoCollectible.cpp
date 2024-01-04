// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCollectible.h"
#include "ShooterCharacter.h"

void AAmmoCollectible::InteractWithPlayer(AShooterCharacter *ShooterCharacter)
{
    Super::InteractWithPlayer(ShooterCharacter);
    ShooterCharacter->AddAmmoToReserve(AmmoAmount);
    Destroy();
}
