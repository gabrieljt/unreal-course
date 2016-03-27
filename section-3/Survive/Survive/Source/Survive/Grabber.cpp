// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "Grabber.h"

#define OUT

UGrabber::UGrabber()
	: InputComponent(nullptr)
	, PhysicsHandleComponent(nullptr)
	, TraceParameters(FCollisionQueryParams(FName(TEXT("")), false, GetOwner()))
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	SetupInputComponent();
	FindPhysicsHandleComponent();
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber Component of %s could not find the UInputComponent"), *GetOwner()->GetName())
	}
	else
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandleComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber Component of %s could not find the UPhysicsHandleComponent"), *GetOwner()->GetName())
	}
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandleComponent->GrabbedComponent)
	{
		SetGrabbedComponentLocation();
	}
}

void UGrabber::SetGrabbedComponentLocation()
{
	PhysicsHandleComponent->SetTargetLocation(GetGrabberCoordinates().TargetLocation);
}

UGrabber::EGrabberCoordinates UGrabber::GetGrabberCoordinates() const
{
	FVector Location;
	FRotator Rotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT Location,
		OUT Rotation
		);
	return EGrabberCoordinates(Location, Rotation, Reach);
}

void UGrabber::Grab()
{
	FHitResult TraceHit;
	EGrabberCoordinates GrabberCoordinates = GetGrabberCoordinates();

	if (GetWorld()->LineTraceSingleByObjectType(
		OUT TraceHit,
		GrabberCoordinates.OriginLocation,
		GrabberCoordinates.TargetLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
		))
	{
		if (TraceHit.GetActor())
		{
			PhysicsHandleComponent->GrabComponent(
				TraceHit.GetComponent(),
				NAME_None,
				TraceHit.GetComponent()->GetOwner()->GetActorLocation(),
				true
				);
		}
	}
}

void UGrabber::Release()
{
	PhysicsHandleComponent->ReleaseComponent();
}