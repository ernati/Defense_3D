// Fill out your copyright notice in the Description page of Project Settings.


#include "InGamePlayerController.h"
#include "IngameWidget.h"
#include "BossMobPortal.h"
#include "Defence_3DCharacter.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "RestartWidget.h"

AInGamePlayerController::AInGamePlayerController() {
	PrimaryActorTick.bCanEverTick = true;
}

void AInGamePlayerController::Tick(float DeltaTime)
{
	if (totalNumberOfMobs > Finish) {
		ShowRestartWidget();
	}
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

	if (BP_IngameWidget != nullptr)
	{
		IngameWidget = CreateWidget<UIngameWidget>(this, BP_IngameWidget);
		IngameWidget->AddToViewport();

		UpdateData();
	}

}


void AInGamePlayerController::AddTotalNumberofMobs()
{
	totalNumberOfMobs++;
	UpdateData();
}

void AInGamePlayerController::AddTotalKills()
{
	totalkills++;
	UpdateData();
}

int32 AInGamePlayerController::GetTotalNumberofMobs()
{
	return totalNumberOfMobs;
}

int32 AInGamePlayerController::GetTotalKills()
{
	return totalkills;
}

void AInGamePlayerController::UpdateData()
{
	int point;
	//ADefence_3DCharacter* Players = Cast<ADefence_3DCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	AFPSCharacter* Players = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (Players)
	{
		point = Players->ReturnPoint();

		IngameWidget->UpdateData(totalNumberOfMobs, totalkills, point);
	}

}


void AInGamePlayerController::ShowRestartWidget()
{
	if (BP_RestartWidget != nullptr)
	{
		SetPause(true);

		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;

		RestartWidget = CreateWidget<URestartWidget>(this, BP_RestartWidget);
		RestartWidget->AddToViewport();
	}
}


void AInGamePlayerController::HideRestartWidget()
{
	RestartWidget->RemoveFromParent();
	RestartWidget->Destruct();

	SetPause(false);

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}