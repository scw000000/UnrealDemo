// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "PatrolPathManager.h"
#include "BasicCharacter.h"
#include "Bots/PatrolPoint.h"

PatrolPathManager::PatrolPathManager()
{
 //partolPath.
   currentPoint = NULL;
}

PatrolPathManager::~PatrolPathManager()
{
}

void PatrolPathManager::SetToNextDestination()
{
   if( currentPoint )
      {
      currentPoint = currentPoint->nextPoint;
      }
}

bool PatrolPathManager::SetStartPoint( ABasicCharacter* pathOwner )
{
   //pathOwner->GetWorld()->GetPawn
  // TActorIterator< APatrolPoint > ActorItr = TActorIterator< APatrolPoint >( pathOwner->GetWorld() );
   for( TActorIterator< APatrolPoint > ActorItr = TActorIterator< APatrolPoint >( pathOwner->GetWorld() ); ActorItr; ++ActorItr )
      {
      if( (*ActorItr)->pointOwner == pathOwner && (*ActorItr)->isHead )
         {
         currentPoint = (*ActorItr);
         return true;
         GEngine->AddOnScreenDebugMessage( -1, 5.0f, FColor::Red, pathOwner->GetName() + TEXT(" : ") + (*ActorItr)->GetName() );
         }
      }
   return false;
}

FVector PatrolPathManager::GetCurrentDestination()
{
   if( currentPoint )
      {
      return currentPoint->GetActorLocation();
      }
   else
      {
      return FVector::ZeroVector;
      }
}
