// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "PositionReporter.h"

UPositionReporter::UPositionReporter()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}

void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();
}

void UPositionReporter::Report() const
{
	UE_LOG(LogTemp, Warning, TEXT("%s @%s"),
		*GetOwner()->GetName(),
		*GetOwner()->GetTransform().GetLocation().ToString()
		)
}

void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}