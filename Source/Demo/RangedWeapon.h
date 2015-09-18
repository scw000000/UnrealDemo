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

   virtual void BeginPlay() override;

   void Fire();
	
   void Reload(  int32 reloadAmmoNum  );

   void SetisTriggerOn( const bool& isSwitchedOn );

   /** return true if this weapon have empty room for reload, and has specified projectile class */
   bool CanReload();
   
   int32 ammo;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = RangedWeapon )
      FireModes fireMode; 

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = RangedWeapon )
      int32 maxAmmo; 

   //unit = RPM
   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = RangedWeapon )
      float fireRate; 

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = RangedWeapon )
      TSubclassOf<class AProjectile> bpProjectile;

   
private:

   void OnTriggerPressed();

   void OnTriggerReleased();

   void TryFire( bool onTriggerPressed );

   void TryAutoFire();

   void TrySemiAutoFire( bool onTriggerPressed );

   void TrySingleFire();

   void ResetisCoolDownOver();

   void StartCoolDownTimer();

   void SetisCoolDownOver( bool isOver );

   bool canFire;

   bool isTriggerOn;

   bool isCoolDownOver;

   
   //unit = seconds / shot = 1 / fireRate * 60.f
   float coolDownTime;

   FTimerHandle autoFireTimerHandle;

   FTimerHandle coolDownTimerHandle;
};
