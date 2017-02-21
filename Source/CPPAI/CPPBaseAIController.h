// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CPPBaseAIController.generated.h"

/**
 *
 */
UCLASS()
class CPPAI_API ACPPBaseAIController : public AAIController
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

};
