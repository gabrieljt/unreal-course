// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DoorOpener.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVE_API UDoorOpener : public UActorComponent
{
	GENERATED_BODY()

public:
	UDoorOpener();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere)
		float OpenAngle;

	UPROPERTY(EditAnywhere)
		float CloseDelay;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* OpenerTriggerVolume;

	UPROPERTY(EditAnywhere)
		bool bWantsToOpen;

	float LastOpenedTime;

	float CloseAngle;

private:
	void Open() const;

	void Close() const;
};
