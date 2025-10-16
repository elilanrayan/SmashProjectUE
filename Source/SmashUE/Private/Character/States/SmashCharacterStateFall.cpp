// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCharacterStateFall.h"

#include "SmashCharacter.h"
#include "Character/SmashCharacterStateID.h"
#include "Character/SmashCharacterStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
USmashCharacterStateFall::USmashCharacterStateFall()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

ESmashCharacterStateID USmashCharacterStateFall::GetStateID()
{
	return ESmashCharacterStateID::Fall;
}

void USmashCharacterStateFall::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->PlayAnimMontage(AnimMontageFall);
	CharacterMovementComponent->AirControl = FallAirControl;
	CharacterMovementComponent->GravityScale = FallGravityScale;
	CharacterMovementComponent->Velocity.X= FallHorizontalMoveSpeed * Character->GetOrientX();
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "Enter State Fall");
}

void USmashCharacterStateFall::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	CharacterMovementComponent->GravityScale =1;
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, "Exit State Fall");
}

void USmashCharacterStateFall::StateTick(float Deltatime)
{
	Super::StateTick(Deltatime);
	if (Character->GetVelocity().Z<=-500)
	{
		CharacterMovementComponent->GravityScale = FallFastGravityScale;
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "Grosse Chute");
	}
	if (Character->GetVelocity().Z==0)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
}


// Called when the game starts
void USmashCharacterStateFall::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USmashCharacterStateFall::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

