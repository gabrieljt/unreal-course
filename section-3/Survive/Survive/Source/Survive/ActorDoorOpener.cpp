// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "ActorDoorOpener.h"

UActorDoorOpener::UActorDoorOpener()
	: UDoorOpener()
{
}

void UActorDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	if (!OpenerActor)
	{
		OpenerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
}

bool UActorDoorOpener::WantsToOpen() const
{
	return OpenerTriggerVolume->IsOverlappingActor(OpenerActor);
}