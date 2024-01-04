// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthCollectible.h"
#include "ShooterCharacter.h"

void AHealthCollectible::InteractWithPlayer(AShooterCharacter *ShooterCharacter)
{
    Super::InteractWithPlayer(ShooterCharacter);
    const float Health = ShooterCharacter->GetHealth();
    const float MaxHealth = ShooterCharacter->GetMaxHealth();
    const float HealthToAdd = Health + HealthAmount;
    if (HealthToAdd > MaxHealth) {
        ShooterCharacter->SetHealth(MaxHealth);
    } else {
        ShooterCharacter->SetHealth(HealthToAdd);
    }
    Destroy();
}
