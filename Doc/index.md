# Introduction: Why Make AI Exclusively in CPP?

Particularly since Unreal 4.6, there are a lot of convenient tools for working with AI.
Most programmers seem to use the behaviour trees and blackboard classes available to work with AI.
When AI starts to become more complicated, it can be convenient to express the AI as a simple behaviour tree.
However, I'm extremely uncomfortable with using Blueprints for any nontrivial functionality for a few reasons, including that they're difficult to manage under revision control, difficult to edit, and difficult to read in comparison to code.
Also while the blackboards and behaviour trees provide a lot of useful functionality, they also add a bit of boilerplate and another thing that can go wrong in AI setup.
Beyond that, you might eventually find there are some things that blackboards just make very difficult to do.

So let me convince you that AI can be written and managed very clearly in CPP for all your needs.
This little guide will start with the very basics of creating an AI Controller entirely in C++, present a few examples, and hopefully include more advanced examples including working with environmental queries.

# Creating and Using a Basic CPP AI Controller

## Creating the CPP File 

1. Open your project and enter the "New C++ Class" Wizard.
1. Check "Show all classes"
1. Search for and select AIController as your base class and create your C++ class

You've now created an AI Controller that can run from C++.
To test your controller, verify that navigation is working, you can create a command for your controlled pawn by overriding BeginPlay, as shown below.

```
--------
IN CPPBaseAIController.h

public:

	void BeginPlay() override;


-------
IN CPPBaseAIController.cpp 

void ACPPBaseAIController::BeginPlay()
{
	Super::BeginPlay();
	//	MoveToLocation(FVector(0.f, 0.f, 0.f), -1.f, true, true, false, true, 0, true);
	MoveToActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}
```

## Attaching to a Pawn

Create a pawn to use your AI.
I like to create a new Blueprint character and using Starter Kit Manneqin with the Third Person Animations, but any pawn will do.
Under "Pawn" under "AI Controller Class" in your pawn, you may select your CPP class directly.
Drag your pawn into a world and test that it moves to the correct location (don't forget to set up the navigation volume).

# Creating Behaviour On Possession

Pawns that spawn into the world typically do so using the SpawnAIFromClass Blueprint Node or from C++ directly.
In BP, you'd usually set up "initialisation" code for the AI Controller in the `OnPossess` implementable event, but in C++ we need to override the virtual function `Possess()`.
There is perhaps confusingly also an `OnPossess` function available to C++, but you'll ignore that when you're not using Blueprints.
So put your initialisation code in the Possess function like this:

```
--------
IN BehaveOnPossessionController.h

public:

	virtual void Possess(APawn* InPawn) override;

-------
IN BehaveOnPossessionController.cpp 

void ABehaveOnPossessionController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("HELP HELP I'VE BEEN POSSESSED!  THE CULPRIT IS %s"), *InPawn->GetName());
}
```

# Creating a Patrolling AI

You don't want your AI to re-evaluate its behaviour on every tick, especially not if that evaluation is an expensive computation including multiple environmental queries and parameters, so we will set up our patrolling AI to run on a timer.

```
--------
IN MultiPointPatrollingAI.h

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


-------
IN MultiPointPatrollingAI.cpp 

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
```

# Using Environmental Queries from CPP


