// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "BehaveOnPossessionController.generated.h"

/**
 * 
 */
UCLASS()
class CPPAI_API ABehaveOnPossessionController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void Possess(APawn* InPawn) override;

};
