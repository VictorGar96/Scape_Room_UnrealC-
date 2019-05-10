// Fill out your copyright notice in the Description page of Project Settings.

#include "Position.h"
#include "Gameframework/Actor.h"


// Sets default values for this component's properties
UPosition::UPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPosition::BeginPlay()
{
	Super::BeginPlay();

	
	FString objectName = GetOwner()->GetName();
	FString objectPos = GetOwner()->GetTargetLocation().ToString();
	
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *objectName, *objectPos);
	
}


// Called every frame
void UPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

