// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "DemoHUD.h"
#include "DemoEnums.h"
#include "DemoPlayerController.h"
#include "MilitaryCharacter.h"
#include "Weapon.h"

ADemoHUD::ADemoHUD( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{
   static ConstructorHelpers::FObjectFinder<UTexture2D> HUDMainTextureOb(TEXT("/Game/UI/HUD/HUDMain"));
   HUDMainTexture = HUDMainTextureOb.Object;
   Crosshair[ CrosshairDirections::CrosshairDirections_Left ] = UCanvas::MakeIcon(HUDMainTexture, 43, 402, 25, 9); // left
	Crosshair[ CrosshairDirections::CrosshairDirections_Right ] = UCanvas::MakeIcon(HUDMainTexture, 88, 402, 25, 9); // right
	Crosshair[ CrosshairDirections::CrosshairDirections_Top ] = UCanvas::MakeIcon(HUDMainTexture, 74, 371, 9, 25); // top
	Crosshair[ CrosshairDirections::CrosshairDirections_Bottom ] = UCanvas::MakeIcon(HUDMainTexture, 74, 415, 9, 25); // bottom
	Crosshair[ CrosshairDirections::CrosshairDirections_Center ] = UCanvas::MakeIcon(HUDMainTexture, 75, 403, 7, 7); // center
}

void ADemoHUD::DrawHUD()
{
   Super::DrawHUD();
  // GEngine->AddOnScreenDebugMessage( -1, 15.0f, FColor::Red, "drawing" );
   if( Canvas )
	{
      DrawCrossHair();
		return;
	}
}

void ADemoHUD::DrawCrossHair()
{
   float CenterX = Canvas->ClipX / 2;
   float CenterY = Canvas->ClipY / 2;

   Canvas->SetDrawColor(255,255,255,192);

   ADemoPlayerController* PCOwner = Cast<ADemoPlayerController>( PlayerOwner );

   AMilitaryCharacter* character =  Cast<AMilitaryCharacter>( PCOwner->GetPawn() );
   if( character )
      {
      AWeapon* weapon = character->GetEquippedWeapon();
      if( weapon )
         {
        Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Center ], 
	      	CenterX - (Crosshair[ CrosshairDirections::CrosshairDirections_Center ]).UL / 2.0f, 
	      	CenterY - (Crosshair[ CrosshairDirections::CrosshairDirections_Center ]).VL / 2.0f );

	      Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Left ],
	        CenterX - 1 - (Crosshair[ CrosshairDirections::CrosshairDirections_Left ]).UL - weapon->crossHairSize, 
	      	CenterY - (Crosshair[ CrosshairDirections::CrosshairDirections_Left ]).VL / 2.0f );

      	Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Right ], 
	      	CenterX + weapon->crossHairSize, 
	        	CenterY - (Crosshair[ CrosshairDirections::CrosshairDirections_Right ]).VL / 2.0f );

	      Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Top ], 
         	CenterX - (Crosshair[ CrosshairDirections::CrosshairDirections_Top ]).UL / 2.0f,
	      	CenterY - 1 - (Crosshair[ CrosshairDirections::CrosshairDirections_Top ]).VL - weapon->crossHairSize );

	      Canvas->DrawIcon(Crosshair[ CrosshairDirections::CrosshairDirections_Bottom ],
		      CenterX - (Crosshair[ CrosshairDirections::CrosshairDirections_Bottom ]).UL / 2.0f,
		      CenterY + weapon->crossHairSize );
         }
      }
}


