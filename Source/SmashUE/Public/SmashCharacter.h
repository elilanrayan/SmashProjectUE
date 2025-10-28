// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraFollowTarget.h"
#include "GameFramework/Character.h"
#include "SmashCharacter.generated.h"

class UEnhancedInputComponent;
class USmashCharacterInputData;
class UInputMappingContext;
class USmashCharacterStateMachine;
struct FInputActionValue;

UCLASS()

class SMASHUE_API ASmashCharacter : public ACharacter,public ICameraFollowTarget
{
	GENERATED_BODY()

	
#pragma region Unreal Default
public:
	// Sets default values for this character's properties
	ASmashCharacter();
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAnimMontage> AnimMontage;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma endregion Unreal Default


#pragma region Orient

public :
	float GetOrientX() const;

	void SetOrientX(float NewOrientX);

	

	protected :
	UPROPERTY(BlueprintReadOnly)
	float OrientX = 1.1f;

	void RotateMeshUsingOrientX() const;
#pragma endregion Orient

#pragma region State Machine

public:
	void CreateStateMachine();
	void InitStateMachine();

	void TicketStateMachine(float DeltaTime) const;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USmashCharacterStateMachine> StateMachine;

	
	#pragma endregion State Machine

#pragma region Input Data / Mapping Context
	public:
	UPROPERTY()
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY()
	TObjectPtr<USmashCharacterInputData> InputData;

	protected:
	void SetupMappingContextIntoController() const;
	#pragma endregion Input Data / Mapping Context

#pragma region Input Move X
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputMoveXEvent,float,InputMoveX);
	public:
	float GetInputMoveX() const;

	UPROPERTY()
	FInputMoveXEvent InputMoveXFastEvent;

	
	

protected :
	UPROPERTY()
	float InputMoveX = 0.0f;

private :
	void OnInputMoveFastX(const FInputActionValue& InputActionValue);
	void BindInputMoveXAxisAndActions(UEnhancedInputComponent* EnhancedInputComponent);
	void OnInputMoveX(const FInputActionValue& InputActionValue);
	#pragma endregion Input Move X

#pragma region Input Jump
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputJumpEvent,bool,InputJump);
public:
	bool GetInputJump() const;

	UPROPERTY()
	FInputJumpEvent InputJumpEvent;
	
protected :
	UPROPERTY()
	bool isJumping = false;

private:
	void OnInputJump(const FInputActionValue& InputActionValue);

#pragma endregion Input Jump

	
#pragma region Interface Camera
public:
	virtual FVector GetFollowPosition() override;
	virtual bool IsFollowable() override;

#pragma endregion Interface Camera
};


