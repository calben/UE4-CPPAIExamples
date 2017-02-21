// Fill out your copyright notice in the Description page of Project Settings.

#include "CPPAI.h"
#include "CPPBaseAIController.h"

void ACPPBaseAIController::BeginPlay()
{
	Super::BeginPlay();
	//	MoveToLocation(FVector(0.f, 0.f, 0.f), -1.f, true, true, false, true, 0, true);
	MoveToActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}
