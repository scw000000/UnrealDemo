// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "Item.h"
#include "BasicCharacter.h"


// Sets default values
AItem::AItem( const FObjectInitializer& ObjectInitializer ) : Super( ObjectInitializer )
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	RootComponent = mesh;
   quantity = 1;
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	//Mesh->SetSimulatePhysics(true);
	//Mesh->WakeRigidBody();
}

void AItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
   
}

bool AItem::Equals( AItem* otherItem )
{
   if( otherItem && ( name.Equals( otherItem->name ) ) )
      {
      return true;
      }   
   return false;
}

void AItem::PickedUp( ABasicCharacter *const character )
{
   if ( mesh && this->GetDistanceTo( character ) < pickUpDistance )
	   {
		Destroy();
	   }
}

void AItem::Dropped( const FVector& location, const FRotator& rotation )
{ 
   
}
/*
// Called every frame
void AItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}*/

