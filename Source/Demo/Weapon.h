// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Item.h"
#include "DemoEnums.h"
#include "Weapon.generated.h"

class ABasicCharacter;
/**
 * 
 */
UCLASS()
class DEMO_API AWeapon : public AItem
{
	GENERATED_BODY()
public:
   AWeapon( const FObjectInitializer& ObjectInitializer );

   void Initialize( ABasicCharacter *const character, const FName &socketName );
	//virtual void Attack( int attackType = 0 );

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Weapon )
      WeaponCategories weaponCategory; 

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Weapon )
      float minCrossHairSize;

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Weapon )
      float maxCrossHairSize;

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Weapon )
      float crossHairSize;

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Weapon )
      float crossHairSizeDecrSpeed;

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Weapon )
      float crossHairSizeIncrSpeed;
};
