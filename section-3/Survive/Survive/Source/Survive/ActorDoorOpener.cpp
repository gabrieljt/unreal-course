// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "ActorDoorOpener.h"

UActorDoorOpener::UActorDoorOpener()
	: UDoorOpener()
	, OtherDoorOpener(nullptr)
{
}

void UActorDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	if (!OpenerActor)
	{
		OpenerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	}

	OtherDoorOpener = GetOwner()->FindComponentByClass<UMassDoorOpener>();
}

bool UActorDoorOpener::WantsToOpen() const
{
	if (OtherDoorOpener && OtherDoorOpener->WantsToOpen())
	{
		return true;
	}

	return OpenerTriggerVolume->IsOverlappingActor(OpenerActor);
}