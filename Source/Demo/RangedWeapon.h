// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "RangedWeapon.generated.h"

USTRUCT()
struct FProjectileConfig
{
	GENERATED_USTRUCT_BODY()

   /** life time */
	UPROPERTY( EditDefaultsOnly, Category = Projectile )
	   float projectileVelocity;

	/** life time */
	UPROPERTY( EditDefaultsOnly, Category = Projectile )
	   float projectileLife;

	/** damage at impact point */
	UPROPERTY( EditDefaultsOnly, Category = WeaponStat )
	   int32 explosionDamage;

	/** radius of damage */
	UPROPERTY( EditDefaultsOnly, Category = WeaponStat) 
	   float explosionRadius;

	/** type of damage */
	UPROPERTY( EditDefaultsOnly, Category = WeaponStat )
	  TSubclassOf<UDamageType> damageType;

	/** defaults */
	FProjectileConfig()
	{
		projectileLife = 10.0f;
		explosionDamage = 30.f;
		explosionRadius = 90.0f;
		damageType = UDamageType::StaticClass();
	}
};
/**
 * 
 */
UCLASS()
class DEMO_API ARangedWeapon : public AWeapon
{
	GENERATED_BODY()
public:
   ARangedWeapon( const FObjectInitializer& ObjectInitializer );

   virtual void BeginPlay() override;

   /** return true if this weapon have empty room for reload, and has specified projectile class */
   bool CanReload();

   virtual void Tick( float DeltaSeconds ) override;

   void Fire( FVector hitPoint );
	
   void Reload(  int32 reloadAmmoNum  );

   void SetisTriggerOn( const bool& isSwitchedOn );

   void ApplyProjectileConfig( FProjectileConfig& Data );
   
   int32 ammo;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = RangedWeapon )
      FireModes fireMode; 

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = RangedWeapon )
      int32 maxAmmo; 

   //unit = RPM
   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = RangedWeapon )
      float fireRate;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Projectile )
	   FProjectileConfig projectileConfig;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Projectile )
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
