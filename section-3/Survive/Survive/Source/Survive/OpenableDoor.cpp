// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "OpenableDoor.h"

UOpenableDoor::UOpenableDoor()
	: LastOpenedTime(0.f)
	, bIsOpen(false)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenableDoor::BeginPlay()
{
	Super::BeginPlay();
}

void UOpenableDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (WantsToClose())
	{
		Close();
	}
}

void UOpenableDoor::Open()
{
	LastOpenedTime = GetWorld()->GetTimeSeconds();
	if (!bIsOpen)
	{
		bIsOpen = true;
		OnOpen.Broadcast();
	}
}

bool UOpenableDoor::WantsToClose() const
{
	return bIsOpen && GetWorld()->GetTimeSeconds() - LastOpenedTime >= CloseDelay;
}

void UOpenableDoor::Close()
{
	bIsOpen = false;
	OnClose.Broadcast();
}