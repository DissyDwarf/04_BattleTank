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

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		//TODO move towards the player

		//Aim towards the player
		GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//Fire if ready
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