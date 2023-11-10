// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuWidget.h"
#include "StartMap_PlayerController.generated.h"

/**
 *
 */
UCLASS()
class DEFENCE_3D_API AStartMap_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UMainMenuWidget> BP_MainMenuWidget;

private:
	UPROPERTY()
		class UMainMenuWidget* MainMenuWidget;

protected:
	virtual void BeginPlay() override;

};
