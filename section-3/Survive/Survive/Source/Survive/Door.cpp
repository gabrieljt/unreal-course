// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "Door.h"

UDoor::UDoor()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	CloseAngle = Owner->GetTransform().Rotator().Yaw;
}

void UDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (OpenerTriggerVolume->IsOverlappingActor(OpenerActor))
	{
		Open();
		LastOpenedTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastOpenedTime >= CloseDelay)
	{
		Close();
	}
}

void UDoor::Open() const
{
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UDoor::Close() const
{
	Owner->SetActorRotation(FRotator(0.f, CloseAngle, 0.f));
}