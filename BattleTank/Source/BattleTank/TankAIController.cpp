// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Classes/Engine/World.h"
#include "tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	

}

void ATankAIController::Tick(float DeltaTime) 
{
	auto ControlledTank = Cast<ATank>(GetPawn());
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	Super::Tick(DeltaTime);
	if (ensure(PlayerTank))
	{
		// move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		//Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire(); //TODO dont fire every frame
	}
	 
}


