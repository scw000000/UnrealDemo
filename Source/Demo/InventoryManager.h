// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BackpackItem.h"
class ABasicCharacter;
class AItem;
//class BackpackItem;
class AWeapon;

/**
 * 
 */
class DEMO_API InventoryManager
{
public:

  // static InventoryManager* GetInstance();
   InventoryManager();

	~InventoryManager();
   
   //virtual void PostInitializeComponents() override;
   void FinishEquipWeapon();

   void DestroyEquippedWeapon();

   void ShowBackpack();

   void SetAttack( bool isAttackOn );

   void SetControllingCharacter( ABasicCharacter *const character );
   
   bool InitializeEquipWeapon( TSubclassOf<class AWeapon> weapon );

   UFUNCTION( BlueprintCallable, Category = Equipment )
      void AddBackpackItemByInstance( AItem *const inItemInstance );

   UFUNCTION( BlueprintCallable, Category = Equipment )
      void AddBackpackItemByClass( TSubclassOf<class AItem> inItemClass );

   TSubclassOf<class AWeapon> GetEquippedWeapon();

   BackpackItem * FindItem( TSubclassOf<class AItem> searchItem );

private:
   void SpawnAndAttachWeapon();
   
   ABasicCharacter* controllingCharacter;
   
   AWeapon* equippedWeapon;

   TSubclassOf<class AWeapon> bpEquippedWeapon;
   TSubclassOf<class AWeapon> bpEquippingWeapon;

   TMap< TSubclassOf<class AItem>, BackpackItem > backpack;
};