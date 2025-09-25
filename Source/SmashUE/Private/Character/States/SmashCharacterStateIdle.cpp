// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/SmashCharacterStateIdle.h"

#include "SmashCharacter.h"
#include "Character/SmashCharacterStateID.h"
#include "Character/SmashCharacterStateMachine.h"


// Sets default values for this component's properties
USmashCharacterStateIdle::USmashCharacterStateIdle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

ESmashCharacterStateID USmashCharacterStateIdle::GetStateID()
{
	return ESmashCharacterStateID::Idle;
}

void USmashCharacterStateIdle::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->PlayAnimMontage(AnimMontageIdle);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Enter StateIdle");
}

void USmashCharacterStateIdle::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow , "Exit StateIdle");
}

void USmashCharacterStateIdle::StateTick(float Deltatime)
{
	Super::StateTick(Deltatime);
	GEngine-> AddOnScreenDebugMessage(-1, 0.1f, FColor::Green , "Tick StateIdle");

	if (FMath::Abs(Character->GetInputMoveX()) > 0.1f)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Walk);
	}
}


// Called when the game starts
void USmashCharacterStateIdle::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USmashCharacterStateIdle::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

