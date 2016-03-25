// Fill out your copyright notice in the Description page of Project Settings.

#include "Survive.h"
#include "Grabber.h"

#define OUT

UGrabber::UGrabber()
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

	SetGrabberParameters();

	if (bIsGrabbing)
	{
		FVector GrabLocation = GetGrabLocation();

		DrawDebugLine(GetWorld(),
			Location,
			GrabLocation,
			FColor(255, 0, 0),
			false,
			0.f,
			0.f,
			10.f
			);

		UPositionReporter* GrabbedObjectReporter = GrabbedObject->FindComponentByClass<UPositionReporter>();
		if (GrabbedObjectReporter)
		{
			GrabbedObjectReporter->Report();
		}
	}
}

void UGrabber::SetGrabberParameters()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT Location,
		OUT Rotation
		);
}

FVector UGrabber::GetGrabLocation() const
{
	return Location + Rotation.Vector() * Reach;
}

void UGrabber::Grab()
{
	FHitResult TraceHit;

	if (GetWorld()->LineTraceSingleByObjectType(
		OUT TraceHit,
		Location,
		GetGrabLocation(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
		))
	{
		bIsGrabbing = true;
		GrabbedObject = TraceHit.GetActor();
	}
}

void UGrabber::Release()
{
	bIsGrabbing = false;
	GrabbedObject = nullptr;
}