// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"//must be the first 
#include "BattleTank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

	auto ControlledTank = GetControlledTank();

	if(!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Player is not controlling a tank!"));
	} 
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player IS controlling: %s"), *ControlledTank->GetName());
	}
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}