// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OpenableDoor.h"
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

private:
	UPROPERTY(EditAnywhere)
		AActor* OpenableDoorActor;

	UOpenableDoor* OpenableDoorActorComponent;
};
