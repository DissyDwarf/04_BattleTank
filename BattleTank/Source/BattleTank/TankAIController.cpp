// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Classes/Engine/World.h"
#include "TankAimingComponent.h"
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	

}

void ATankAIController::Tick(float DeltaTime) 
{
	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	Super::Tick(DeltaTime);
	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	// move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	//Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if(AimingComponent->GetFiringState() != EFiringStatus::Locked)
	{
		AimingComponent->Fire(); //TODO dont fire every frame
	}

}


