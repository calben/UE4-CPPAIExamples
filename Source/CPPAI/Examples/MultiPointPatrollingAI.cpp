// Fill out your copyright notice in the Description page of Project Settings.

#include "CPPAI.h"
#include "MultiPointPatrollingAI.h"

void AMultiPointPatrollingAI::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	GetWorld()->GetTimerManager().SetTimer(EvaluateCurrentTargetLocationTimer, this, &AMultiPointPatrollingAI::EvaluateCurrentTargetLocation, .25f, true);
	MoveToLocation(PatrolPoints[CurrentPatrolPointIndex], -1.f, true, true, false, true, 0, true);
}

void AMultiPointPatrollingAI::EvaluateCurrentTargetLocation()
{
	UE_LOG(LogTemp, Warning, TEXT("EVALUATING"));
	// remember that because your pawn may have some height, if you compare to a point on the ground (0)
	// you may need to make the tolerance a little larger to compensate
	if (FVector::Dist(GetControlledPawn()->GetActorLocation(), PatrolPoints[CurrentPatrolPointIndex % PatrolPoints.Num()]) <= 100.f)
	{
		CurrentPatrolPointIndex++;
		MoveToLocation(PatrolPoints[CurrentPatrolPointIndex % PatrolPoints.Num()], -1.f, true, true, false, true, 0, true);
	}
}


