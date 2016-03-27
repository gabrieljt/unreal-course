// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	struct EGrabberCoordinates
	{
	public:
		EGrabberCoordinates(const FVector OriginLocation, const FRotator Rotator, const float Reach)
			: OriginLocation(OriginLocation)
			, TargetLocation(OriginLocation + Rotator.Vector() * Reach)
			, Rotator(Rotator)
		{
		}

		const FVector OriginLocation;
		const FVector TargetLocation;
		const FRotator Rotator;
	};

	UGrabber();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void SetupInputComponent();

	void FindPhysicsHandleComponent();

	void SetGrabbedComponentLocation();

	EGrabberCoordinates GetGrabberCoordinates() const;

	void Grab();

	void Release();

	UPROPERTY(EditAnywhere)
		float Reach;

	UInputComponent* InputComponent;

	UPhysicsHandleComponent* PhysicsHandleComponent;

	const FCollisionQueryParams TraceParameters;
};
