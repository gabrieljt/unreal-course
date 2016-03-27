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

	UPROPERTY(EditAnywhere)
		float OpenAngle;

	UPROPERTY(EditAnywhere)
		float CloseDelay;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* OpenerTriggerVolume;

	UPROPERTY(EditAnywhere)
		AActor* OpenerActor;

	float LastOpenedTime;

	float CloseAngle;
};
