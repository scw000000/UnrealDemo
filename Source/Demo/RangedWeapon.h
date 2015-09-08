// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "RangedWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ARangedWeapon : public AWeapon
{
	GENERATED_BODY()
public:

   void Fire();
	void Reload();
   void OnTriggerPressed();
   void OnTriggerReleased();

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = RangedWeapon )
      FiringModes firingMode; 

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = RangedWeapon )
      UClass* bPAmmo;

   UPROPERTY( VisibleAnywhere, BlueprintReadWrite, Category = RangedWeapon )
      int32 maxAmmo;
};
