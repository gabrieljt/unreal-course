// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "Door.h"

// Sets default values for this component's properties
UDoor::UDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	OpenerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	CloseAngle = Owner->GetTransform().Rotator().Yaw;
}

// Called every frame
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