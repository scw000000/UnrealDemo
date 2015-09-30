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
   ConstructorHelpers::FObjectFinder<UTexture2D> HitTextureOb(TEXT("/Game/UI/HUD/HitIndicator"));
   
   HUDMainTexture = HUDMainTextureOb.Object;
   HUDAssets02Texture = HUDAssets02TextureOb.Object;
   HitNotifyTexture = HitTextureOb.Object;

   Crosshair[ CrosshairDirections::CrosshairDirections_Left ] = UCanvas::MakeIcon(HUDMainTexture, 43, 402, 25, 9); // left
	Crosshair[ CrosshairDirections::CrosshairDirections_Right ] = UCanvas::MakeIcon(HUDMainTexture, 88, 402, 25, 9); // right
	Crosshair[ CrosshairDirections::CrosshairDirections_Top ] = UCanvas::MakeIcon(HUDMainTexture, 74, 371, 9, 25); // top
	Crosshair[ CrosshairDirections::CrosshairDirections_Bottom ] = UCanvas::MakeIcon(HUDMainTexture, 74, 415, 9, 25); // bottom
	Crosshair[ CrosshairDirections::CrosshairDirections_Center ] = UCanvas::MakeIcon(HUDMainTexture, 75, 403, 7, 7); // center

   HitNotifyIcon[ ShooterHudPositions::ShooterHudPositions_Left ] = UCanvas::MakeIcon(HitNotifyTexture,  158, 831, 585, 392);	
	HitNotifyIcon[ ShooterHudPositions::ShooterHudPositions_FrontLeft ] = UCanvas::MakeIcon(HitNotifyTexture, 369, 434, 460, 378);	
	HitNotifyIcon[ ShooterHudPositions::ShooterHudPositions_Front ] = UCanvas::MakeIcon(HitNotifyTexture,  848, 284, 361, 395);	
	HitNotifyIcon[ ShooterHudPositions::ShooterHudPositions_FrontRight ] = UCanvas::MakeIcon(HitNotifyTexture,  1212, 397, 427, 394);	
	HitNotifyIcon[ ShooterHudPositions::ShooterHudPositions_Right ] = UCanvas::MakeIcon(HitNotifyTexture, 1350, 844, 547, 321);	
	HitNotifyIcon[ ShooterHudPositions::ShooterHudPositions_BackRight ] = UCanvas::MakeIcon(HitNotifyTexture, 1232, 1241, 458, 341);	
	HitNotifyIcon[ ShooterHudPositions::ShooterHudPositions_Back ] = UCanvas::MakeIcon(HitNotifyTexture,  862, 1384, 353, 408);	
	HitNotifyIcon[ ShooterHudPositions::ShooterHudPositions_BackLeft ] = UCanvas::MakeIcon(HitNotifyTexture, 454, 1251, 371, 410);	

   Offsets[ ShooterHudPositions::ShooterHudPositions_Left ] = FVector2D(173,0);	
	Offsets[ ShooterHudPositions::ShooterHudPositions_FrontLeft ] = FVector2D(120,125);	
	Offsets[ ShooterHudPositions::ShooterHudPositions_Front ] = FVector2D(0,173);	
	Offsets[ ShooterHudPositions::ShooterHudPositions_FrontRight ] = FVector2D(-120,125);
	Offsets[ ShooterHudPositions::ShooterHudPositions_Right ] = FVector2D(-173,0);	
	Offsets[ ShooterHudPositions::ShooterHudPositions_BackRight ] = FVector2D(-120,-125);
	Offsets[ ShooterHudPositions::ShooterHudPositions_Back ] = FVector2D(0,-173);
	Offsets[ ShooterHudPositions::ShooterHudPositions_BackLeft ] = FVector2D(120,-125);
   
   healthBar = UCanvas::MakeIcon( HUDAssets02Texture, 67, 212, 372, 50 );
	healthBarBg = UCanvas::MakeIcon( HUDAssets02Texture, 67, 162, 372, 50 );
   healthIcon = UCanvas::MakeIcon(HUDAssets02Texture, 78, 262, 28, 28);
   controllingCharacter = NULL;

   lastHitTime = 0.f;
 //  noAmmoFadeOutTime =  1.0f;
	hitNotifyDisplayTime = 0.75f;
	//KillFadeOutTime = 2.0f;
	lastEnemyHitDisplayTime = 0.2f;
	//NoAmmoNotifyTime = -NoAmmoFadeOutTime;
	//LastKillTime = - KillFadeOutTime;
	lastEnemyHitTime = -lastEnemyHitDisplayTime;
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
      DrawHitIndicator();;
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

void ADemoHUD::DrawHitIndicator()
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - lastHitTime <= hitNotifyDisplayTime)
	   {
		const float StartX = Canvas->ClipX / 2.0f;
		const float StartY = Canvas->ClipY / 2.0f;

		for ( uint8 i = 0; i < 8; i++ )
		   {
			const float TimeModifier = FMath::Max( 0.0f, 1 - (CurrentTime - hitNotifyData[i].hitTime ) / hitNotifyDisplayTime );
			const float Alpha = TimeModifier * hitNotifyData[i].hitPercentage;
			Canvas->SetDrawColor(255, 255, 255, FMath::Clamp(FMath::TruncToInt(Alpha * 255 * 1.5f), 0, 255));
			Canvas->DrawIcon(HitNotifyIcon[i], 
				StartX + ( HitNotifyIcon[i].U - HitNotifyTexture->GetSizeX() / 2 + Offsets[i].X) * uiScale,
				StartY + ( HitNotifyIcon[i].V - HitNotifyTexture->GetSizeY() / 2 + Offsets[i].Y) * uiScale,
				uiScale );
		   }
	   }
}

void ADemoHUD::NotifyWeaponHit( float damageTaken, struct FDamageEvent const& damageEvent, class APawn* pawnInstigator )
{
	const float currentTime = GetWorld()->GetTimeSeconds();
	if ( controllingCharacter )
	   {
		if ( currentTime - lastHitTime > hitNotifyDisplayTime ) 
		   {
			for ( uint8 i = 0; i < 8; i++ )
			   {
				hitNotifyData[i].hitPercentage = 0;
			   }
		   }

		FVector impulseDir;    
		FHitResult hitResult; 
		damageEvent.GetBestHitInfo( this, pawnInstigator, hitResult, impulseDir );

		//check hit vector against pre-defined direction vectors - left, front, right, back
		FVector HitVector = FRotationMatrix( controllingCharacter->playerCamera->GetComponentRotation() ).InverseTransformVector( -impulseDir );

		FVector Dirs2[8] = { 
			FVector(0,-1,0) /*left*/, 
			FVector(1,-1,0) /*front left*/, 
			FVector(1,0,0) /*front*/, 
			FVector(1,1,0) /*front right*/, 
			FVector(0,1,0) /*right*/, 
			FVector(-1,1,0) /*back right*/, 
			FVector(-1,0,0), /*back*/
			FVector(-1,-1,0) /*back left*/ 
		   };
		int32 DirIndex = -1;
		float HighestModifier = 0;
      //test 8 direction individually to find the best match direction by minimal dot product value
		for ( uint8 i = 0; i < 8; i++ )
		   {
			//Normalize our direction vectors
			Dirs2[i].Normalize();
			const float DirModifier = FMath::Max(0.0f, FVector::DotProduct(Dirs2[i], HitVector));
			if (DirModifier > HighestModifier)
			   {
				DirIndex = i;
				HighestModifier = DirModifier;
			   }
		   }
		if (DirIndex > -1)
		   {
			const float DamageTakenPercentage = ( damageTaken / controllingCharacter->health );
			hitNotifyData[DirIndex].hitPercentage += DamageTakenPercentage * 2;
			hitNotifyData[DirIndex].hitPercentage = FMath::Clamp( hitNotifyData[DirIndex].hitPercentage, 0.0f, 1.0f );
			hitNotifyData[DirIndex].hitTime = currentTime;
		   }

	   }
	
	lastHitTime = currentTime;
}


