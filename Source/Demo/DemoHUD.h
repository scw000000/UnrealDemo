// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "DemoHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoHUD : public AHUD
{
	GENERATED_BODY()
	
   ADemoHUD( const FObjectInitializer& ObjectInitializer );

   virtual void DrawHUD() override;

   void DrawCrossHair();

   UPROPERTY()
	UTexture2D* HUDMainTexture;

	UPROPERTY()
	FCanvasIcon Crosshair[5];
	
	
};
