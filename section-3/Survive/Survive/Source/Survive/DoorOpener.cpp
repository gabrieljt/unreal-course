// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "DoorOpener.h"

UDoorOpener::UDoorOpener()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	if (!OpenableDoorActor)
	{
		UE_LOG(LogTemp, Error, TEXT("OpenableDoorActor not set for %s"),
			*GetOwner()->GetName());
	}
	else
	{
		OpenableDoorActorComponent = OpenableDoorActor->FindComponentByClass<UOpenableDoor>();
	}

}

void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (WantsToOpen())
	{
		OpenableDoorActorComponent->Open();
	}
}

bool UDoorOpener::WantsToOpen() const
{
	return false;
}