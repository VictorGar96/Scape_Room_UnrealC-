// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	FindInputComponent();

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!physicsHandle) { return; }

	/// if the physics handle is attached 
	/// move the object that we´re holding
	if (physicsHandle->GrabbedComponent)
	{
		physicsHandle->SetTargetLocation(GetReachLineEnd());
	}

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *playerViewPointLocation.ToString(), *playerViewPointRotation.ToString())
}

/// Grab key pressed
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key pressed"));

	auto hitResult = GetFirstPhysicsBodyInReach();
	auto componentToGrab = hitResult.GetComponent();
	auto actorHit = hitResult.GetActor();

	if (actorHit)
	{
		physicsHandle->GrabComponentAtLocationWithRotation(
			componentToGrab,
			NAME_None,
			componentToGrab->GetOwner()->GetActorLocation(),
			componentToGrab->GetOwner()->GetActorRotation()
		);
	}
}

/// Grab key released
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key release"));
	physicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
	/// Look foar attached Physics Handle
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	/// Look for attached physics Handle
	if (physicsHandle == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("%s, Physics Handle Component missing"), *GetOwner()->GetName());
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Physics Handle Component found"), *GetOwner()->GetName());

}

void UGrabber::FindInputComponent()
{
	/// Look for attached Input Component
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (inputComponent == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("%s, Input Component missing"), *GetOwner()->GetName());

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Component found"), *GetOwner()->GetName());

		/// Bind the input axis
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);

	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/*
	DrawDebugLine(
		GetWorld(),
		playerViewPointLocation,
		PlayerViewPoint(),
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10
	);
	*/

	/// Set up Query Parameters
	FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult hit;

	/// Object type == physics body. Used to filter what we want to detect
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), /// Le decimos que solo detecte physics body
		traceParameters
	);

	AActor* colisionObject = hit.GetActor();

	if (colisionObject)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *(colisionObject->GetName()));
	}

	return hit;
}

FVector UGrabber::GetReachLineEnd()
{
	/// Get player view point
	FVector  playerViewPointLocation;
	FRotator playerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);

	FVector lineTraceEnd = playerViewPointLocation + playerViewPointRotation.Vector() * reach;

	return lineTraceEnd;
}

FVector UGrabber::GetReachLineStart()
{
	/// Get player view point
	FVector  playerViewPointLocation;
	FRotator playerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);

	return playerViewPointLocation;
}

