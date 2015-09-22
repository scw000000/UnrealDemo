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
   healthIcon = UCanvas::MakeIcon(HUDAssets02Texture, 78, 262, 28, 28);
   controllingCharacter = NULL;
}

void ADemoHUD::DrawHUD()
{
   Super::DrawHUD();
   if( !Canvas )
      {
      return;
      }
   uiScale = Canvas->ClipY / 1080.0f;
   ADemoPlayerController* PCOwner = Cast<ADemoPlayerController>( PlayerOwner );
   controllingCharacter =  Cast<AMilitaryCharacter>( PCOwner->GetPawn() );
  // GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "drawing" );
      DrawCrossHair();
      DrawHealth();
		return;
}

void ADemoHUD::DrawHealth()
{
   if( controllingCharacter )
      {
      Canvas->SetDrawColor(FColor::White);
   	const float healthPosX = 20.f * uiScale;
	   const float healthPosY = Canvas->ClipY - ( 20.f + healthBarBg.VL ) * uiScale;
	   Canvas->DrawIcon( healthBarBg, healthPosX, healthPosY, uiScale );
	   const float healthPercent =  FMath::Min( 1.0f, controllingCharacter->health / controllingCharacter->maxHealth );

	   FCanvasTileItem tileItem( FVector2D( healthPosX, healthPosY ), healthBar.Texture->Resource, 
							 FVector2D( healthBar.UL * healthPercent * uiScale, healthBar.VL * uiScale ), FLinearColor::Green );

      const float iconWidth = healthBar.Texture->GetSurfaceWidth();
		const float iconHeight = healthBar.Texture->GetSurfaceHeight();
		tileItem.UV0 = FVector2D( healthBar.U / iconWidth, healthBar.V / iconHeight );
		tileItem.UV1 = tileItem.UV0  + FVector2D( healthBar.UL * healthPercent / iconWidth, healthBar.VL / iconHeight );

	   tileItem.BlendMode = SE_BLEND_Translucent;
	   Canvas->DrawItem( tileItem );
      Canvas->DrawIcon( healthIcon, healthPosX + 20.f * uiScale, healthPosY + ( healthBar.VL - healthIcon.VL ) / 2.0f * uiScale, uiScale);
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
	      	CenterX - (Crosshair[ CrosshairDirections::CrosshairDirections_Center ]).UL * uiScale / 2.0f, 
	      	CenterY - (Crosshair[ CrosshairDirections::CrosshairDirections_Center ]).VL * uiScale / 2.0f, uiScale );

	      Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Left ],
	        CenterX - 1 - (Crosshair[ CrosshairDirections::CrosshairDirections_Left ]).UL * uiScale - characterWeapon->crossHairSize * uiScale, 
	      	CenterY - (Crosshair[ CrosshairDirections::CrosshairDirections_Left ]).VL * uiScale / 2.0f, uiScale );

      	Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Right ], 
	      	CenterX + characterWeapon->crossHairSize * uiScale, 
	        	CenterY - (Crosshair[ CrosshairDirections::CrosshairDirections_Right ]).VL * uiScale / 2.0f, uiScale );

	      Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Top ], 
         	CenterX - (Crosshair[ CrosshairDirections::CrosshairDirections_Top ]).UL * uiScale / 2.0f,
	      	CenterY - 1 - (Crosshair[ CrosshairDirections::CrosshairDirections_Top ]).VL * uiScale - characterWeapon->crossHairSize * uiScale, uiScale );

	      Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Bottom ],
		      CenterX - (Crosshair[ CrosshairDirections::CrosshairDirections_Bottom ]).UL * uiScale / 2.0f,
		      CenterY + characterWeapon->crossHairSize * uiScale, uiScale );
         }
      }
}


