// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/States/SmashCharacterStateJump.h"

#include "MaterialHLSLTree.h"
#include "SmashCharacter.h"
#include "Character/SmashCharacterStateID.h"
#include "Character/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
USmashCharacterStateJump::USmashCharacterStateJump()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

ESmashCharacterStateID USmashCharacterStateJump::GetStateID()
{
	return ESmashCharacterStateID::Jump;
}

void USmashCharacterStateJump::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->PlayAnimMontage(AnimMontageJump);
	CharacterMovementComponent->AirControl = JumpAirControl;
	float Gravity = -CharacterMovementComponent->GetGravityZ();
	float GravityJump = (8*MaxHeight)/(JumpDuration*JumpDuration);
	float VelocityJump = (GravityJump*JumpDuration)/2;
	CharacterMovementComponent->JumpZVelocity = VelocityJump;
	CharacterMovementComponent->GravityScale = GravityJump/Gravity;
	CharacterMovementComponent->Velocity = FVector(JumpWalkSpeed * Character->GetOrientX(),CharacterMovementComponent->Velocity.Y,CharacterMovementComponent->Velocity.Z);
	Character->Jump();
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, "Enter State Jump");
}

void USmashCharacterStateJump::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Exit State Jump");
}

void USmashCharacterStateJump::StateTick(float Deltatime)
{
	Super::StateTick(Deltatime);
	if (Character->GetVelocity().Z<=0)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Fall);
	}
}


// Called when the game starts
void USmashCharacterStateJump::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USmashCharacterStateJump::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

