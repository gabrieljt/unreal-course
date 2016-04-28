// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenableDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVE_API UOpenableDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	UOpenableDoor();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Open();

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;

private:
	bool WantsToClose() const;

	void Close();

	UPROPERTY(EditAnywhere)
		float CloseDelay;

	UPROPERTY(VisibleAnywhere)
		bool bIsOpen;

	float LastOpenRequestTime;
};