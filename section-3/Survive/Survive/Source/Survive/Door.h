// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Door.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVE_API UDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	UDoor();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void Open() const;

	void Close() const;

	AActor* Owner;

	AActor* OpenerActor;

	float LastOpenedTime;

	float CloseAngle;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* OpenerTriggerVolume;

	UPROPERTY(EditAnywhere)
		float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
		float CloseDelay = 1.0f;
};
