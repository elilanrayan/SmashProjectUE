// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerGameViewportClient.h"
#include "LocalMultiplayerSubsystem.h"
#include "LocalMultiplayerSettings.h"
#include "VisualizeTexture.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"

void ULocalMultiplayerGameViewportClient::PostInitProperties()
{
	MaxSplitscreenPlayers = 8;
	Super::PostInitProperties();
}


bool ULocalMultiplayerGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	MultiSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULocalMultiplayerSubsystem>();
	FInputKeyParams param(EventArgs.Key, EventArgs.Event, EventArgs.AmountDepressed);
	if (EventArgs.Key.IsGamepadKey())
	{
		int DeviceID = EventArgs.InputDevice.GetId();
		int IndexPlayer = MultiSubsystem->GetAssignedPlayerIndexFromGamepadDeviceID(DeviceID);
		if (IndexPlayer == -1)
		{
			int newPlayer = MultiSubsystem->AssignNewPlayerToGamepadDeviceID(DeviceID);
			MultiSubsystem->AssignGamepadInputMapping(newPlayer, ELocalMultiplayerInputMappingType::InGame);
		}
		APlayerController* LocalPlayer = UGameplayStatics::GetPlayerController(GetWorld(), IndexPlayer);
		return LocalPlayer->InputKey(param);
	}


	MultiSettings = GetMutableDefault<ULocalMultiplayerSettings>();
	int Index = MultiSettings->
		FindKeyboardProfileIndexFromKey(EventArgs.Key, ELocalMultiplayerInputMappingType::InGame);
	if (Index != -1)
	{
		int IndexPlayer = MultiSubsystem->GetAssignedPlayerIndexFromKeyboardProfileIndex(Index);
		if (IndexPlayer == -1)
		{
			int newPlayer = MultiSubsystem->AssignNewPlayerToKeyboardProfile(Index);
			MultiSubsystem->AssignKeyboardMapping(newPlayer, Index, ELocalMultiplayerInputMappingType::InGame);
			IndexPlayer = newPlayer;
		}
		APlayerController* LocalPlayer = UGameplayStatics::GetPlayerController(GetWorld(), IndexPlayer);
		return LocalPlayer->InputKey(param);
	}

	return Super::InputKey(EventArgs);
}


bool ULocalMultiplayerGameViewportClient::InputAxis(FViewport* PViewport, FInputDeviceId InputDevice, FKey Key,
                                                    float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	MultiSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULocalMultiplayerSubsystem>();
	if (bGamepad)
	{
		int DeviceID = InputDevice.GetId();
		int IndexPlayer = MultiSubsystem->GetAssignedPlayerIndexFromGamepadDeviceID(DeviceID);
		if (IndexPlayer == -1)
		{
			int newPlayer = MultiSubsystem->AssignNewPlayerToGamepadDeviceID(DeviceID);
			MultiSubsystem->AssignGamepadInputMapping(newPlayer, ELocalMultiplayerInputMappingType::InGame);
		}
		APlayerController* LocalPlayer = UGameplayStatics::GetPlayerController(GetWorld(), IndexPlayer);
		LocalPlayer->InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
	}
	return Super::InputAxis(Viewport, InputDevice, Key, Delta, DeltaTime, NumSamples, bGamepad);
}
