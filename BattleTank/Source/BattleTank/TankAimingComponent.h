// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};


//Forward declaration
class UTanKBarrel; 
class UTankTurret;

//Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTanKBarrel*);
	void SetTurretReference(UTankTurret*);

	void AimAt(FVector OutHitLocation, float LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = Setup)
	EFiringStatus FiringState = EFiringStatus::Reloading;


private:
	UTanKBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	
	


	void MoveBarrelTowards(FVector AimDirection);

};
