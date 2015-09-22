// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "DemoHUD.h"
#include "DemoEnums.h"
#include "DemoPlayerController.h"
#include "MilitaryCharacter.h"
#include "Weapon.h"

ADemoHUD::ADemoHUD( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{
   ConstructorHelpers::FObjectFinder<UTexture2D> HUDMainTextureOb(TEXT("/Game/UI/HUD/HUDMain"));
   ConstructorHelpers::FObjectFinder<UTexture2D> HUDAssets02TextureOb(TEXT("/Game/UI/HUD/HUDAssets02"));

   HUDMainTexture = HUDMainTextureOb.Object;
   HUDAssets02Texture = HUDAssets02TextureOb.Object;

   Crosshair[ CrosshairDirections::CrosshairDirections_Left ] = UCanvas::MakeIcon(HUDMainTexture, 43, 402, 25, 9); // left
	Crosshair[ CrosshairDirections::CrosshairDirections_Right ] = UCanvas::MakeIcon(HUDMainTexture, 88, 402, 25, 9); // right
	Crosshair[ CrosshairDirections::CrosshairDirections_Top ] = UCanvas::MakeIcon(HUDMainTexture, 74, 371, 9, 25); // top
	Crosshair[ CrosshairDirections::CrosshairDirections_Bottom ] = UCanvas::MakeIcon(HUDMainTexture, 74, 415, 9, 25); // bottom
	Crosshair[ CrosshairDirections::CrosshairDirections_Center ] = UCanvas::MakeIcon(HUDMainTexture, 75, 403, 7, 7); // center

   healthBar = UCanvas::MakeIcon( HUDAssets02Texture, 67, 212, 372, 50 );
	healthBarBg = UCanvas::MakeIcon( HUDAssets02Texture, 67, 162, 372, 50 );

   controllingCharacter = NULL;
}

void ADemoHUD::DrawHUD()
{
   Super::DrawHUD();
   ADemoPlayerController* PCOwner = Cast<ADemoPlayerController>( PlayerOwner );
   controllingCharacter =  Cast<AMilitaryCharacter>( PCOwner->GetPawn() );
  // GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "drawing" );
   if( Canvas )
	{
      DrawCrossHair();
      DrawHealth();
		return;
	}
}

void ADemoHUD::DrawHealth()
{

   if( controllingCharacter )
      {
      Canvas->SetDrawColor(FColor::White);
   	const float healthPosX = 20.f;
	   const float healthPosY = Canvas->ClipY - 20.f - healthBarBg.VL ;
	   Canvas->DrawIcon( healthBarBg, healthPosX, healthPosY );
	   const float healthPercent =  FMath::Min( 1.0f, controllingCharacter->health / controllingCharacter->maxHealth );

	   FCanvasTileItem tileItem( FVector2D( healthPosX, healthPosY ), healthBar.Texture->Resource, 
							 FVector2D( healthBar.UL * healthPercent, healthBar.VL ), FLinearColor::White );

     // MakeUV( FCanvasIcon& Icon, FVector2D& UV0, FVector2D& UV1, uint16 U, uint16 V, uint16 UL, uint16 VL )
      const float iconWidth = healthBar.Texture->GetSurfaceWidth();
		const float iconHeight = healthBar.Texture->GetSurfaceHeight();
		tileItem.UV0 = FVector2D( healthBar.U / iconWidth, healthBar.V / iconHeight );
		tileItem.UV1 = tileItem.UV0  + FVector2D( healthBar.UL * healthPercent / iconWidth, healthBar.VL / iconHeight );

	   tileItem.BlendMode = SE_BLEND_Translucent;
	   Canvas->DrawItem( tileItem );

	//   Canvas->DrawIcon( HealthIcon, HealthPosX + Offset * ScaleUI, HealthPosY + (HealthBar.VL - HealthIcon.VL) / 2.0f * ScaleUI, ScaleUI );
      }

	
}

void ADemoHUD::DrawCrossHair()
{
   float CenterX = Canvas->ClipX / 2;
   float CenterY = Canvas->ClipY / 2;

   Canvas->SetDrawColor(255,255,255,192);
   if( controllingCharacter )
      {
      AWeapon* characterWeapon = controllingCharacter->GetEquippedWeapon();
      if( characterWeapon )
         {
        Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Center ], 
	      	CenterX - (Crosshair[ CrosshairDirections::CrosshairDirections_Center ]).UL / 2.0f, 
	      	CenterY - (Crosshair[ CrosshairDirections::CrosshairDirections_Center ]).VL / 2.0f );

	      Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Left ],
	        CenterX - 1 - (Crosshair[ CrosshairDirections::CrosshairDirections_Left ]).UL - characterWeapon->crossHairSize, 
	      	CenterY - (Crosshair[ CrosshairDirections::CrosshairDirections_Left ]).VL / 2.0f );

      	Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Right ], 
	      	CenterX + characterWeapon->crossHairSize, 
	        	CenterY - (Crosshair[ CrosshairDirections::CrosshairDirections_Right ]).VL / 2.0f );

	      Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Top ], 
         	CenterX - (Crosshair[ CrosshairDirections::CrosshairDirections_Top ]).UL / 2.0f,
	      	CenterY - 1 - (Crosshair[ CrosshairDirections::CrosshairDirections_Top ]).VL - characterWeapon->crossHairSize );

	      Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Bottom ],
		      CenterX - (Crosshair[ CrosshairDirections::CrosshairDirections_Bottom ]).UL / 2.0f,
		      CenterY + characterWeapon->crossHairSize );
         }
      }
}


