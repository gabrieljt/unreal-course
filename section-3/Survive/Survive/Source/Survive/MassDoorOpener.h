// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DoorOpener.h"
#include "MassDoorOpener.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVE_API UMassDoorOpener : public UDoorOpener
{
	GENERATED_BODY()

public:
	UMassDoorOpener();

	virtual bool WantsToOpen() const override;

private:
	float GetOverlappingActorsTotalMass() const;

	UPROPERTY(EditAnywhere)
		float RequiredMass;
};
