// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicCharacter.h"
#include "MilitaryCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API AMilitaryCharacter : public ABasicCharacter
{
	GENERATED_BODY()

public:

   AMilitaryCharacter( const FObjectInitializer& ObjectInitializer );

   virtual void ToggleProne() override;

   void StartReload();

   void EndReload();

   //custom function for movement
   virtual void MoveForward( float amount ) override;

   //custom function for movement
   virtual void MoveRight( float amount ) override;

   virtual void Crouch( bool bClientSimulation = false ) override;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Equipment )
      WeaponCategories equippedWeapon;
};
