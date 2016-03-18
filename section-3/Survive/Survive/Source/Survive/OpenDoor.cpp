// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	OpenerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (OpenerTriggerVolume->IsOverlappingActor(OpenerActor))
	{
		OpenDoor();
	}
}

void UOpenDoor::OpenDoor() const
{
	AActor* Owner = GetOwner();
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}