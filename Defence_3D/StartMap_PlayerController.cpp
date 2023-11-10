// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMap_PlayerController.h"

void AStartMap_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

	if (BP_MainMenuWidget != nullptr)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, BP_MainMenuWidget);
		MainMenuWidget->AddToViewport();
	}
}
