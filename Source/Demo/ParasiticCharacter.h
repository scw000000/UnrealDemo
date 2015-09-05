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

   UFUNCTION( BlueprintNativeEvent, Category = Item )
         void Prox( AActor * OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult );

   virtual void Prox_Implementation( AActor * OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult );

   UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Item )
      class USphereComponent* ProxSphere;
private:
  // void Parasitize( ABasicCharacter* target );
	
	
};
