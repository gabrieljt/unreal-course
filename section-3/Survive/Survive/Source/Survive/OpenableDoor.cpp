// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "OpenableDoor.h"

UOpenableDoor::UOpenableDoor()
	: LastOpenedTime(0.f)
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

	if (GetWorld()->GetTimeSeconds() - LastOpenedTime >= CloseDelay)
	{
		Close();
	}
}

void UOpenableDoor::Open()
{
	LastOpenedTime = GetWorld()->GetTimeSeconds();
    OnOpen.Broadcast();
}

void UOpenableDoor::Close() const
{
	OnClose.Broadcast();
}