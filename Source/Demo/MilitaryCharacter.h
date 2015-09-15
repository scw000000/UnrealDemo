// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicCharacter.h"
#include "InventoryManager.h"
#include "MilitaryCharacter.generated.h"

class AWeapon;
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
      virtual void StartAttack() override;

   UFUNCTION( BlueprintCallable, Category = Equipment )
      virtual void StopAttack() override;
   
   UFUNCTION( BlueprintCallable, Category = Equipment )
      void EndEquipWeapon();

   UFUNCTION( BlueprintCallable, Category = Equipment )
      void InstantiateEquipWeapon( );

   void StartReload();

   void EndReload();

   virtual void Tick( float DeltaSeconds ) override;

   //custom function for movement
   virtual void MoveForward( float amount ) override;

   //custom function for movement
   virtual void MoveRight( float amount ) override;

   virtual void Crouch( bool bClientSimulation = false ) override; 
   
   UFUNCTION( BlueprintCallable, Category = Equipment )
      void StartEquipWeapon( TSubclassOf<class AWeapon> weapon );

  // UFUNCTION( BlueprintCallable, Category = Equipment )
  //    void AddItem( TSubclassOf<class AItem> inItem );

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Equipment )
      WeaponCategories equippedWeapon;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Equipment )
      TSubclassOf<class AWeapon> bpWeapon;

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Equipment )
      TSubclassOf<class AWeapon> bpWeapon2;

  

    //  void StartEquipWeapon( TSubclassOf<class AWeapon> weapon );
   //UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = Equipment )
      
private:
   InventoryManager inventoryManager;
};
