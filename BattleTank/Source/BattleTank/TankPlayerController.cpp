// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"//must be the first 
#include "BattleTank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is not controlling a tank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player IS controlling: %s"), *ControlledTank->GetName());
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

	     //UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *OutHitLocation.ToString())
		//TODO tell controlled tank to aim at this point
	
	}

}

//get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation)
{
	// find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if(GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *LookDirection.ToString())
	}

	// line-trace along that direction, and see what we hit(up to max range)
	return true;

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