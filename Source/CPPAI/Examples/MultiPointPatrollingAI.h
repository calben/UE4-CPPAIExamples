// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "MultiPointPatrollingAI.generated.h"

/**
 *
 */
UCLASS()
class CPPAI_API AMultiPointPatrollingAI : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere)
		int CurrentPatrolPointIndex = 0;

	UPROPERTY(VisibleAnywhere)
		TArray<FVector> PatrolPoints =
	{
		FVector(0.f, 0.f, 0.f),
		FVector(500.f, 0.f, 0.f),
		FVector(500.f, 500.f, 0.f),
		FVector(0.f, 500.f, 0.f)
	};

	UPROPERTY(VisibleAnywhere)
	FTimerHandle EvaluateCurrentTargetLocationTimer;

	virtual void Possess(APawn* InPawn) override;

	void EvaluateCurrentTargetLocation();

};
