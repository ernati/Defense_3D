// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCE_3D_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()

		AInGamePlayerController();

public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UIngameWidget> BP_IngameWidget;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class URestartWidget> BP_RestartWidget;

private:
	UPROPERTY()
		class UIngameWidget* IngameWidget;

	UPROPERTY()
		class URestartWidget* RestartWidget;

	
public:
	UPROPERTY(BlueprintReadWrite)
	int32 totalNumberOfMobs = 0;

	int32 totalkills = 0;

	int32 Finish = 2000;

	UPROPERTY(BlueprintReadWrite)
	int32 BossSpawnMobNums = 100;

	void AddTotalNumberofMobs();
	int32 GetTotalNumberofMobs();

	void AddTotalKills();
	int32 GetTotalKills();
	void UpdateData();

	void ShowRestartWidget();
	void HideRestartWidget();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};
