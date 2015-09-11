// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ABasicCharacter;
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

   void Fire();

   void SetControllingCharacter( ABasicCharacter *const character );
   
   void EquipWeapon( TSubclassOf<class AWeapon> weapon );

private:
   
   ABasicCharacter* controllingCharacter;
   AWeapon* equippedWeapon;
};