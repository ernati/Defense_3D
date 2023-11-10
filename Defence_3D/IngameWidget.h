// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IngameWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCE_3D_API UIngameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NumofTotalSpawn;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NumofTotalKills;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Points;

	void UpdateData(int32 totalNumberOfMobs, int32 totalkills, int32 point);

};
