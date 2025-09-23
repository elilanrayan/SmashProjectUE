// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/SmashCharacterStateRun.h"

#include "SmashCharacter.h"
#include "Character/SmashCharacterStateID.h"


// Sets default values for this component's properties
USmashCharacterStateRun::USmashCharacterStateRun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

ESmashCharacterStateID USmashCharacterStateRun::GetStateID()
{
	return ESmashCharacterStateID::Run;
}

void USmashCharacterStateRun::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character -> PlayAnimMontage(AnimMontageRun);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, "Enter StateRun");
}

void USmashCharacterStateRun::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character -> StopAnimMontage(AnimMontageRun);
	Character->AddMovementInput(FVector(0, 0, 0));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, "Exit StateRun");
	
}

void USmashCharacterStateRun::StateTick(float Deltatime)
{
	Super::StateTick(Deltatime);
	FVector MovementDirection = FVector(MaxRunSpeed * Character-> GetOrientX() * Deltatime, 0, 0);
	Character->AddMovementInput(MovementDirection);
	GEngine-> AddOnScreenDebugMessage(-1, 0.1f, FColor::Green , "Tick StateRun");
}


// Called when the game starts
void USmashCharacterStateRun::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USmashCharacterStateRun::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

