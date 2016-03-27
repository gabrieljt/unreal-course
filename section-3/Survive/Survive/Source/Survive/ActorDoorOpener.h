// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DoorOpener.h"
#include "ActorDoorOpener.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVE_API UActorDoorOpener : public UDoorOpener
{
	GENERATED_BODY()

public:
	UActorDoorOpener();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
		AActor* OpenerActor;
};
