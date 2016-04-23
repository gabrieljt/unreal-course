// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "MassDoorOpener.h"

UMassDoorOpener::UMassDoorOpener()
	: UDoorOpener()
{
	CloseDelay = INFINITY;
}

bool UMassDoorOpener::WantsToOpen() const
{
	return GetOverlappingActorsTotalMass() >= RequiredMass;
}

float UMassDoorOpener::GetOverlappingActorsTotalMass() const
{
	TArray<AActor*> OverlappingActors;
	float TotalMass = 0.f;

	OpenerTriggerVolume->GetOverlappingActors(OUT OverlappingActors);

	for (const auto& Actor : OverlappingActors)
	{
		UPrimitiveComponent* ActorPrimitiveComponent = Actor->FindComponentByClass<UPrimitiveComponent>();
		if (ActorPrimitiveComponent->IsSimulatingPhysics())
		{
			TotalMass += ActorPrimitiveComponent->GetMass();
		}
	}

	return TotalMass;
}