// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Item.h"
#include "BackpackItem.h"
class ABasicCharacter;
class AItem;
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
   void EquipWeapon();

   void DestroyEquippedWeapon();

   void ReloadWeapon();

   void ShowBackpack();

   void SetAttack( bool isAttackOn );

   void SetControllingCharacter( ABasicCharacter *const character );

   void SetEquippingWeapon( TSubclassOf<class AWeapon> weapon );
   
   UFUNCTION( BlueprintCallable, Category = Equipment )
      void AddBackpackItemByInstance( AItem *const inItemInstance );

   UFUNCTION( BlueprintCallable, Category = Equipment )
      void AddBackpackItemByClass( TSubclassOf<class AItem> inItemClass, int32 itemNum = 1 );

   UFUNCTION( BlueprintCallable, Category = Equipment )
      void RemoveBackpackItemByClass( TSubclassOf<class AItem> inItemClass, int32 itemNum = 1 );

   bool CanReload();

   AWeapon* GetEquippedWeapon();

   bool CanEquipWeapon( TSubclassOf<class AWeapon> weapon );

   BackpackItem * FindItem( TSubclassOf<class AItem> searchItem );

private:
   void SpawnAndAttachWeapon();
   
   ABasicCharacter* controllingCharacter;
   
   AWeapon* equippedWeapon;

   TSubclassOf<class AWeapon> bpEquippedWeapon;
   TSubclassOf<class AWeapon> bpEquippingWeapon;

   TMap< TSubclassOf<class AItem>, BackpackItem > backpack;
};