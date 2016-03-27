// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "Door.h"

UDoor::UDoor()
	: LastOpenedTime(0.f)
	, CloseAngle(0.f)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoor::BeginPlay()
{
	Super::BeginPlay();

	CloseAngle = GetOwner()->GetTransform().Rotator().Yaw;

	if (!OpenerActor)
	{
		OpenerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
}

void UDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (OpenerTriggerVolume->IsOverlappingActor(OpenerActor))
	{
		Open();
		LastOpenedTime = GetWorld()->GetTimeSeconds();
	}
	else if (GetWorld()->GetTimeSeconds() - LastOpenedTime >= CloseDelay)
	{
		Close();
	}
}

void UDoor::Open() const
{
	GetOwner()->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UDoor::Close() const
{
	GetOwner()->SetActorRotation(FRotator(0.f, CloseAngle, 0.f));
}