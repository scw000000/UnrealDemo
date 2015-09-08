// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ABasicCharacter;
/**
 * 
 */

class DEMO_API InventoryManager
{
public:
   static InventoryManager* GetInstance();
   void InventoryManager::EquipWeapon( UClass* bpWeapon );
   
private:
   InventoryManager();
	~InventoryManager();
   ABasicCharacter* controllingCharacter;
   static InventoryManager* instance;
  // virtual bool SetControllingCharacter( APawn* InPawn );
};

InventoryManager* InventoryManager::GetInstance()
{
   if( !instance )
      {
      instance = new InventoryManager;
      }
   return instance;
}
