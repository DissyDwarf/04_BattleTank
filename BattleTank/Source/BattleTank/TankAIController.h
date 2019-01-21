// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, Category = Setup)
	float AcceptanceRadius = 8000; //How close can the AI Tank get

private:
	
	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION()
	void OnPossessedTankDeath();
};
