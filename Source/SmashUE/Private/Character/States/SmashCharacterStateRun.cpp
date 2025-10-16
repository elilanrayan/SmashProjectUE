// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/SmashCharacterStateRun.h"

#include "SmashCharacter.h"
#include "Character/SmashCharacterSettings.h"
#include "Character/SmashCharacterStateID.h"
#include "Character/SmashCharacterStateMachine.h"


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
	Character -> InputJumpEvent.AddDynamic(this,&USmashCharacterStateRun::OnInputJump);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, "Enter StateRun");
}

void USmashCharacterStateRun::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character -> StopAnimMontage(AnimMontageRun);
	Character -> InputJumpEvent.RemoveDynamic(this,&USmashCharacterStateRun::OnInputJump);
	Character->AddMovementInput(FVector(0, 0, 0));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, "Exit StateRun");
	
}

void USmashCharacterStateRun::StateTick(float Deltatime)
{
	Super::StateTick(Deltatime);
	const USmashCharacterSettings* Settings = GetDefault<USmashCharacterSettings>();
	
	if (FMath::Abs(Character->GetInputMoveX()) < Settings->InputMoveXThreshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
	else
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector,Character->GetOrientX());
	}
	//FVector MovementDirection = FVector(MaxRunSpeed * Character-> GetOrientX() * Deltatime, 0, 0);
	//Character->AddMovementInput(MovementDirection);
	GEngine-> AddOnScreenDebugMessage(-1, 0.1f, FColor::Green , "Tick StateRun");
}

void USmashCharacterStateRun::OnInputJump(bool isJumping)
{
	StateMachine->ChangeState(ESmashCharacterStateID::Jump);
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

