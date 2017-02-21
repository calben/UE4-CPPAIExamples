// Fill out your copyright notice in the Description page of Project Settings.

#include "CPPAI.h"
#include "BehaveOnPossessionController.h"

void ABehaveOnPossessionController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("HELP HELP I'VE BEEN POSSESSED!  THE CULPRIT IS %s"), *InPawn->GetName());
}
