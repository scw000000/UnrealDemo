// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipment.h"
#include "DemoEnums.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AWeapon : public AEquipment
{
	GENERATED_BODY()
public:
	void Attack( int AttackType = 0 );
	void Reload();
   void Aim();

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = WeaponProperties )
      WeaponCategories m_Category; 
};
