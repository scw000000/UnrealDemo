// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicCharacter.h"
#include "InventoryManager.h"
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

   virtual void PostInitializeComponents() override;

   virtual void BeginPlay() override;

   virtual void ToggleProne() override;

   UFUNCTION( BlueprintCallable, Category = Equipment )
      void Fire();

   void StartReload();

   void EndReload();

   virtual void Tick( float DeltaSeconds ) override;

   //custom function for movement
   virtual void MoveForward( float amount ) override;

   //custom function for movement
   virtual void MoveRight( float amount ) override;

   virtual void Crouch( bool bClientSimulation = false ) override;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Equipment )
      WeaponCategories equippedWeapon;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Equipment )
      UClass* bpWeapon;

   UFUNCTION( BlueprintCallable, Category = Equipment )
      void EquipWeapon( UClass* weapon );

   

private:
   InventoryManager inventoryManager;
   bool fuck;
};
