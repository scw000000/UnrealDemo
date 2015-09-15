// Fill out your copyright notice in the Description page of Project Settings.

#include "Demo.h"
#include "BackpackItem.h"

BackpackItem::BackpackItem( UTexture2D * iIcon, const FString &  iName, int32 iQuantity ) : icon( iIcon ), name( iName ), quantity( iQuantity )
{
}

BackpackItem::~BackpackItem()
{
}

void BackpackItem::SetName( const FString & aName )
{
   name = aName;
}

void BackpackItem::SetQuantity( int32 aQuantity )
{
   quantity = aQuantity;
}

UTexture2D * const BackpackItem::GetIcon( )
{
   return icon;
}

FString BackpackItem::GetName( )
{
   return name;
}

int32 BackpackItem::GetQuantity( )
{
   return quantity;
}

