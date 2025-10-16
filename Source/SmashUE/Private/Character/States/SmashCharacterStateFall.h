// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "SmashCharacterStateFall.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateFall : public USmashCharacterState
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USmashCharacterStateFall();

	virtual ESmashCharacterStateID GetStateID() override;

	UFUNCTION()
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;

	UFUNCTION()
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;

	virtual void StateTick(float Deltatime) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> AnimMontageFall;

	UPROPERTY(EditAnywhere)
	float FallHorizontalMoveSpeed;

	UPROPERTY(EditAnywhere)
	float FallAirControl;

	UPROPERTY(EditAnywhere)
	float FallGravityScale;

	UPROPERTY(EditAnywhere)
	float FallFastGravityScale;

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
