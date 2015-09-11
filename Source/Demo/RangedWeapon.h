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
   ARangedWeapon();
   
   void OnTriggerPressed();
   void OnTriggerReleased();
   void Fire();
	void Reload();

   void SetcanFire( const bool& inCanFire );
   bool GetcanFire();

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = RangedWeapon )
      FiringModes firingMode; 

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = RangedWeapon )
      int32 maxAmmo; 

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = RangedWeapon )
      FVector nozzleOffset;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = RangedWeapon )
      UClass* bPAmmo;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = RangedWeapon )
      TSubclassOf<class AProjectile> projectileClass;

   
private:
   bool canFire;
};
