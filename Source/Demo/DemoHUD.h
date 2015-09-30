// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "DemoHUD.generated.h"

class AMilitaryCharacter;
/**
 * 
 */

struct FHitData
{
	/** Last hit time. */
	float hitTime;
	
	/** strength of hit icon */
	float hitPercentage;

	/** Initialise defaults. */
	FHitData()
	{
		hitTime = 0.0f;
		hitPercentage = 0.0f;
	}
};

UCLASS()
class DEMO_API ADemoHUD : public AHUD
{
	GENERATED_BODY()
	
   ADemoHUD( const FObjectInitializer& ObjectInitializer );

   virtual void DrawHUD() override;

   void DrawHealth();

   void DrawCrossHair();

   void DrawHitIndicator();

   void NotifyWeaponHit( float damageTaken, struct FDamageEvent const& damageEvent, class APawn* pawnInstigator );

  // bool SetControllingCharacter( APawn* InPawn );

   UPROPERTY()
	   UTexture2D* HUDMainTexture;

   UPROPERTY()
      UTexture2D* HUDAssets02Texture;

   UPROPERTY()
      UTexture2D* HitNotifyTexture;

	UPROPERTY()
	   FCanvasIcon Crosshair[5];

   UPROPERTY()
	   FCanvasIcon HitNotifyIcon[8];

   UPROPERTY()
	   FCanvasIcon healthBar;

   UPROPERTY()
	   FCanvasIcon healthBarBg;

   UPROPERTY()
	   FCanvasIcon healthIcon;

   UPROPERTY()
	   FVector2D Offsets[8];
	
protected:
	AMilitaryCharacter* controllingCharacter;

   float uiScale;

   /** Most recent hit time, used to check if we need to draw hit indicator at all. */
	float lastHitTime;

	/** How long till hit notify fades out completely. */
	float hitNotifyDisplayTime;

	/** When we last time hit the enemy. */
	float lastEnemyHitTime;

	/** How long till enemy hit notify fades out completely. */
	float lastEnemyHitDisplayTime;

   /** Runtime data for hit indicator. */
	FHitData hitNotifyData[8];
};
