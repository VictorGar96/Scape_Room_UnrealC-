// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Gameframework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	actorToOverlap = GetWorld()->GetFirstPlayerController()->GetPawn();

	owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{

	FRotator newRotation = FRotator(0.f, openAngle, 0.f);

	owner->SetActorRotation(newRotation);

}

void UOpenDoor::CloseDoor()
{
	FRotator defaultRot = FRotator(0.f, 0.f, 0.f);

	owner->SetActorRotation(defaultRot);

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (pressurePlate->IsOverlappingActor(actorToOverlap))
	{
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();

	}
	if(GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay)
		 CloseDoor();

 
}

