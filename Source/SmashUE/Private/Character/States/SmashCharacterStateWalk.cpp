// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/SmashCharacterStateWalk.h"

#include "SmashCharacter.h"
#include "Character/SmashCharacterSettings.h"
#include "Character/SmashCharacterStateID.h"
#include "Character/SmashCharacterStateMachine.h"


// Sets default values for this component's properties
USmashCharacterStateWalk::USmashCharacterStateWalk()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

ESmashCharacterStateID USmashCharacterStateWalk::GetStateID()
{
	return ESmashCharacterStateID::Walk;
}

void USmashCharacterStateWalk::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->PlayAnimMontage(AnimMontageWalk);
	Character->InputMoveXFastEvent.AddDynamic(this,&USmashCharacterStateWalk::OnInputMoveXFast);
	Character->InputJumpEvent.AddDynamic(this,&USmashCharacterStateWalk::OnInputJump);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, "Enter State Walk");
}

void USmashCharacterStateWalk::OnInputMoveXFast(float InputMoveXFast)
{
	StateMachine->ChangeState(ESmashCharacterStateID::Run);
}

void USmashCharacterStateWalk::OnInputJump(bool isJumping)
{
	StateMachine->ChangeState(ESmashCharacterStateID::Jump);
}

void USmashCharacterStateWalk::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character->AddMovementInput(FVector(0, 0, 0));
	Character->InputMoveXFastEvent.RemoveDynamic(this,&USmashCharacterStateWalk::OnInputMoveXFast);
	Character->InputJumpEvent.RemoveDynamic(this,&USmashCharacterStateWalk::OnInputJump);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Exit State Walk");
}

void USmashCharacterStateWalk::StateTick(float Deltatime)
{
	Super::StateTick(Deltatime);
	//FVector MovementDirection = FVector(MaxWalkSpeed * Character-> GetOrientX() * Deltatime, 0, 0);
	//Character->AddMovementInput(MovementDirection);
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, "Tick State Walk");
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
	
}


// Called when the game starts
void USmashCharacterStateWalk::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USmashCharacterStateWalk::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

