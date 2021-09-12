// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PLayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}


// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PLayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}

	RotateTurret(PLayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	// if player == null || is Dead THEN BAIL!!!
	if (!PLayerPawn || !PLayerPawn->GetIsPlayerAlive())
	{
		return;
	}
	// if player IS in range THEN FIRE!!!
	if (ReturnDistanceToPlayer() <= FireRange)
	{
			Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PLayerPawn)
	{
		return 0.0f;
	}

	return FVector::Dist(PLayerPawn->GetActorLocation(), GetActorLocation());
}
