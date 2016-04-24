// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DoorOpener.generated.h"

UCLASS()
class SURVIVE_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:
	UDoorOpener();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool WantsToOpen() const;

protected:

	UPROPERTY(EditAnywhere)
		ATriggerVolume* OpenerTriggerVolume;

	UPROPERTY(EditAnywhere)
		float CloseDelay;

private:
	void Open() const;

	void Close() const;

	UPROPERTY(EditAnywhere)
		float OpenAngle;

	float LastOpenedTime;

	float CloseAngle;
};
