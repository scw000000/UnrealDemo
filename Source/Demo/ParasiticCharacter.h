// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BasicCharacter.h"
#include "ParasiticCharacter.generated.h"

/**
 * 
 */

UCLASS()
class DEMO_API AParasiticCharacter : public ABasicCharacter
{
	GENERATED_BODY()

public:
   AParasiticCharacter( const FObjectInitializer& ObjectInitializer );

   virtual void Tick( float DeltaSeconds ) override;

   virtual void OnHit_Implementation( AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

   UFUNCTION( BlueprintNativeEvent, Category = Collision )
         void OnHit( AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

private:
   void Parasitize( ABasicCharacter* target );
	
	bool parasitizingHuman;
};
