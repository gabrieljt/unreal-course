// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PositionReporter.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	UGrabber();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void SetupInputComponent();

	void FindPhysicsHandleComponent();

	void SetGrabberParameters();

	FVector GetGrabLocation() const;

	void Grab();

	void Release();

	UPROPERTY(VisibleAnywhere)
		bool bIsGrabbing = false;

	UPROPERTY(EditAnywhere)
		float Reach = 100.f;

	FVector Location;

	FRotator Rotation;

	UInputComponent* InputComponent = nullptr;

	UPhysicsHandleComponent* PhysicsHandleComponent = nullptr;

	AActor* GrabbedObject = nullptr;

	const FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
};
