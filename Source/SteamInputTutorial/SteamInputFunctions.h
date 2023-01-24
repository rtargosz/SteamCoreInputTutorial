// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericPlatform/IInputInterface.h"
#include "GenericPlatform/GenericApplicationMessageHandler.h"
#include "Math/Color.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SteamInputFunctions.generated.h"

/**
 * 
 */
UCLASS()
class STEAMINPUTTUTORIAL_API USteamInputFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "SteamInputFunctions")
		static void BroadcastSteamInputWidgetKeyDown(uint8 KeyIndex);

	UFUNCTION(BlueprintCallable, Category = "SteamInputFunctions")
		static void BroadcastSteamInputWidgetKeyUp(uint8 KeyIndex);
};

class FSteamInputInterface
	: public IInputInterface
{
public:

	static TSharedRef< FSteamInputInterface > Create(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler);
	void BroadcastSteamInputWidgetKeyDown(int8 KeyID);
	void BroadcastSteamInputWidgetKeyUp(int8 KeyID);

	~FSteamInputInterface();

	void SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler);

	/** Sets the strength/speed of the given channel for the given controller id. */
	virtual void SetForceFeedbackChannelValue(int32 ControllerId, FForceFeedbackChannelType ChannelType, float Value) override { /* nop */ }

	/** Sets the strength/speed of all the channels for the given controller id. */
	virtual void SetForceFeedbackChannelValues(int32 ControllerId, const FForceFeedbackValues& Values) override { /* nop */ }

	/* Ignored if controller does not support a color. */
	virtual void SetLightColor(int32 ControllerId, struct FColor Color) override { /* nop */ }

	virtual void ResetLightColor(int32 ControllerId) override { /* nop */ }

private:

	FSteamInputInterface(const TSharedRef< FGenericApplicationMessageHandler >& MessageHandler);

	TSharedRef< FGenericApplicationMessageHandler > MessageHandler;
};