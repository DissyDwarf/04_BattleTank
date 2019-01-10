// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"//must be the first 
#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Classes/Engine/World.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if(AimingComponent)
	{ 
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerControler cant find aiming component at begin play"))
	}
}


void ATankPlayerController::Tick(float deltatime)
{
	Super::Tick(deltatime);
	AimTowardsCrosshair();

}
	



ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation; //out parameter
	if(GetSightRayHitLocation(OutHitLocation)) //Has "side effect", is going to line trace
	{

	    
		GetControlledTank()->AimAt(OutHitLocation);
	
	}

}

//get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation, LookDirection))
	{
		// line-trace along that direction, and see what we hit(up to max range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	
	return true;

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const 
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if(GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	
	OutHitLocation = FVector(0);
	return false; // line trace didnt suceed
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;// TO be discared
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);
}