// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "DoorOpener.h"

UDoorOpener::UDoorOpener()
	: bWantsToOpen(false)
	, LastOpenedTime(0.f)
	, CloseAngle(0.f)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	CloseAngle = GetOwner()->GetTransform().Rotator().Yaw;
}

void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bWantsToOpen)
	{
		bWantsToOpen = false;
		Open();
		LastOpenedTime = GetWorld()->GetTimeSeconds();
	}
	else if (GetWorld()->GetTimeSeconds() - LastOpenedTime >= CloseDelay)
	{
		Close();
	}
}

void UDoorOpener::Open() const
{
	GetOwner()->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UDoorOpener::Close() const
{
	GetOwner()->SetActorRotation(FRotator(0.f, CloseAngle, 0.f));
}