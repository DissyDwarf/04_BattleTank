// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AITankController Begin Play"));

	auto AIControlledTank = GetAIControlledTank();

	if(!AIControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("AITankController not controlling Tanks"))
	
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AITankController possesing %s"), *AIControlledTank->GetName())
	
	}

}



ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());

}