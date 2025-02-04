// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerVolume.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/Components/AudioComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	UPROPERTY(EditAnywhere)
	float openAngle = -60.f;

	//UPROPERTY(EditDefaultsOnly, Category = Audio, meta = (AllowPrivateAcces = "true"))
	//class USoundCue* openDoorSound = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 1.f;

	UPROPERTY(BlueprintAssignable)
	FOnOpenRequest onOpenRequest;


	UPROPERTY(BlueprintAssignable)
	FOnOpenRequest onCloseRequest;

	float lastDoorOpenTime;

	
	AActor* owner = nullptr;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetTotalMassOfActor();
};
