// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Classes/Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AITankController Begin Play"));

	auto PlayerTank = GetPlayerTank();

	if(!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Can not find Player Tank!"))
	
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Player Tank Possesing %s"), *PlayerTank->GetName())
	
	}

}



ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);


}