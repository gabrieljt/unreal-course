// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenableDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);

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
		FOnOpenRequest OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
		FOnCloseRequest OnCloseRequest;

private:
	void Close() const;

	UPROPERTY(EditAnywhere)
		float CloseDelay;

	float LastOpenedTime;
};