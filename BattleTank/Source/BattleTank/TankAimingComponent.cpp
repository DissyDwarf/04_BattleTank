// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TanKBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Classes/Engine/StaticMesh.h"
#include "Classes/Kismet/GameplayStatics.h"
// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;  

	// ...
}
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTanKBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

 void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
 {	
	 if(RoundsLeft <= 0)
	 {
		 FiringState = EFiringStatus::OutOfAmmo;
	 }
	 else if((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	 {
		 FiringState = EFiringStatus::Reloading;
	 }
	 else if (IsBarrelMoving())		
	 {
		 FiringState = EFiringStatus::Aiming;
	 }
	 else
	 {
		 FiringState = EFiringStatus::Locked;
	 }

 }

 EFiringStatus UTankAimingComponent::GetFiringState() const
 {
	 return FiringState;
 }

 int32 UTankAimingComponent::GetRoundsLeft() const
 {
	 return RoundsLeft;
 }


 bool UTankAimingComponent::IsBarrelMoving()
 {
	 if (!ensure(Barrel)) { return false;}
	 auto BarrelForward = Barrel->GetForwardVector();
	 return !BarrelForward.Equals(AimDirection, 0.01); //Vectors are equal
 }



void UTankAimingComponent::AimAt(FVector OutHitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		OutHitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // Parameter must be present to prevent bug
	);
	if (bHaveAimSolution)

	{
	    AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
	 
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel || !ensure(Turret))) { return; }
	//  Work out difference between current barrel rotation , and AimDirection 
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	// always yaw the shortest way
	Barrel->Elevate(DeltaRotator.Pitch); 
	if(FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else // Avoid going the long way round
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }
	

	if (FiringState == EFiringStatus::Locked || FiringState == EFiringStatus::Aiming)
	{

		// spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		RoundsLeft--;
	}
}

