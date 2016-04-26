// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "OpenableDoor.h"

UOpenableDoor::UOpenableDoor()
	: LastOpenedTime(0.f)
	, CloseAngle(0.f)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UOpenableDoor::BeginPlay()
{
	Super::BeginPlay();

	CloseAngle = GetOwner()->GetTransform().Rotator().Yaw;
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
	GetOwner()->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
    //OnOpenRequest.Broadcast();
	LastOpenedTime = GetWorld()->GetTimeSeconds();
}

void UOpenableDoor::Close() const
{
	GetOwner()->SetActorRotation(FRotator(0.f, CloseAngle, 0.f));
}