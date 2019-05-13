// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Gameframework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//static ConstructorHelpers::FObjectFinder openDoorSoundObject(TEXT("SoundCue'/Game/Audio/open_door.open_door'"));

	//if (openDoorSoundObject.Succeeded())
	//{
	//	openDoorSound = openDoorSoundObject.Object;
	//}
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();

	

	if (!pressurePlate)
	{ 
		UE_LOG(LogTemp, Error, TEXT("%s missing preasure plate"), *GetOwner()->GetName()); 
	}

}

void UOpenDoor::OpenDoor()
{
	onOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	onCloseRequest.Broadcast();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActor() > 50.f)
	{
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds(); 
	}
	if(GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay)
		 CloseDoor();
}

float UOpenDoor::GetTotalMassOfActor()
{
	float totalMass = 0.f;

	/// Find all the overlapping actor 
	TArray<AActor*> overlappingActors;

	if (!pressurePlate) { return totalMass; }
	pressurePlate->GetOverlappingActors(OUT overlappingActors);

	for (const AActor* actor : overlappingActors )
	{
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on presure plate"), *actor->GetName());
	}


	/// Iterate through them adding theur masses

	return totalMass;
}

