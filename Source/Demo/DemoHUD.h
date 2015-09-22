// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "DemoHUD.generated.h"

class AMilitaryCharacter;
/**
 * 
 */
UCLASS()
class DEMO_API ADemoHUD : public AHUD
{
	GENERATED_BODY()
	
   ADemoHUD( const FObjectInitializer& ObjectInitializer );

   virtual void DrawHUD() override;

   void DrawHealth();

   void DrawCrossHair();

  // bool SetControllingCharacter( APawn* InPawn );

   UPROPERTY()
	UTexture2D* HUDMainTexture;

   UPROPERTY()
   UTexture2D* HUDAssets02Texture;

	UPROPERTY()
	FCanvasIcon Crosshair[5];

   UPROPERTY()
	FCanvasIcon healthBar;

   UPROPERTY()
	FCanvasIcon healthBarBg;
	
protected:
	AMilitaryCharacter* controllingCharacter;
};
