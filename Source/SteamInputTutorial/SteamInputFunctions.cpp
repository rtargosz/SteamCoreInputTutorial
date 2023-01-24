// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamInputFunctions.h"
#include "Misc/CoreDelegates.h"
#include "GenericPlatform/GenericApplication.h"
#include "Framework/Application/SlateApplication.h"


void USteamInputFunctions::BroadcastSteamInputWidgetKeyDown(uint8 KeyIndex)
{
	static TSharedRef< FGenericApplicationMessageHandler > tempMsg = FSlateApplication::Get().GetPlatformApplication()->GetMessageHandler();
	static TSharedRef< FSteamInputInterface > handlerRef = FSteamInputInterface::Create(tempMsg);
	handlerRef->BroadcastSteamInputWidgetKeyDown(KeyIndex);
}

void USteamInputFunctions::BroadcastSteamInputWidgetKeyUp(uint8 KeyIndex)
{
	static TSharedRef< FGenericApplicationMessageHandler > tempMsg = FSlateApplication::Get().GetPlatformApplication()->GetMessageHandler();
	static TSharedRef< FSteamInputInterface > handlerRef = FSteamInputInterface::Create(tempMsg);
	handlerRef->BroadcastSteamInputWidgetKeyUp(KeyIndex);
}

uint32 LegacyMapVirtualKey(uint32 InVirtualKey)
{
	if ((InVirtualKey >= 48 && InVirtualKey <= 57)
		|| (InVirtualKey >= 65 && InVirtualKey <= 90)
		|| InVirtualKey == 8
		|| InVirtualKey == 9
		|| InVirtualKey == 13
		|| InVirtualKey == 27
		|| InVirtualKey == 32)
	{
		return InVirtualKey;
	}

	if (InVirtualKey >= 96 && InVirtualKey <= 105)
	{
		return InVirtualKey - 48;
	}

	if ((InVirtualKey == 106 || InVirtualKey == 107)
		|| (InVirtualKey >= 109 && InVirtualKey <= 111))
	{
		return InVirtualKey - 64;
	}

	// Special keys
	switch (InVirtualKey)
	{
	case 0x6A: return '*';
	case 0x6B: return '+';
	case 0x6D: return '-';
	case 0x6E: return '.';
	case 0x6F: return '/';

	case 0xBA: return ';';  // VK_OEM_1
	case 0xBB: return '=';  // VK_OEM_PLUS
	case 0xBC: return ',';  // VK_OEM_COMMA
	case 0xBD: return '_';  // VK_OEM_MINUS
	case 0xBE: return '.';  // VK_OEM_PERIOD
	case 0xBF: return '/';  // VK_OEM_2
	case 0xC0: return '`';  // VK_OEM_3

	case 0xDB: return '[';  // VK_OEM_4
	case 0xDC: return '\\'; // VK_OEM_5
	case 0xDD: return ']';  // VK_OEM_6
	case 0xDE: return '\''; // VK_OEM_7
	}

	return 0;
}

TSharedRef< FSteamInputInterface > FSteamInputInterface::Create(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
{
	return MakeShareable(new FSteamInputInterface(InMessageHandler));
}

FSteamInputInterface::FSteamInputInterface(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler) : MessageHandler(InMessageHandler)
{
}

FSteamInputInterface::~FSteamInputInterface()
{
}

void FSteamInputInterface::SetMessageHandler(const TSharedRef< FGenericApplicationMessageHandler >& InMessageHandler)
{
	MessageHandler = InMessageHandler;
}

void FSteamInputInterface::BroadcastSteamInputWidgetKeyDown(int8 KeyIndex)
{
	uint32 CharCode = LegacyMapVirtualKey(KeyIndex);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("BroadcastSteamInputWidgetKeyDown %i"), KeyIndex));
	MessageHandler->OnKeyDown(KeyIndex, CharCode, false);
}

void FSteamInputInterface::BroadcastSteamInputWidgetKeyUp(int8 KeyIndex)
{
	uint32 CharCode = LegacyMapVirtualKey(KeyIndex);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("BroadcastSteamInputWidgetKeyUp %i"), KeyIndex));
	MessageHandler->OnKeyUp(KeyIndex, CharCode, false);
}