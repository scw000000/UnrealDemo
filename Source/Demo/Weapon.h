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
   void Initialize( ABasicCharacter *character, FName socketName );
	//virtual void Attack( int attackType = 0 );

   UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Weapon )
      WeaponCategories weaponCategory; 
};
