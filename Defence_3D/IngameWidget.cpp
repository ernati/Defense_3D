// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameWidget.h"
#include "Components/TextBlock.h"

void UIngameWidget::UpdateData(int32 totalNumberOfMobs, int32 totalkills, int32 point)
{
	FString strTotalSpawn;
	strTotalSpawn = FString::Printf(TEXT("Total Spawn : %d"), totalNumberOfMobs);

	NumofTotalSpawn->SetText(FText::FromString(strTotalSpawn));

	FString strText;
	strText = FString::Printf(TEXT("Total kills : %d"), totalkills);

	NumofTotalKills->SetText(FText::FromString(strText));

	FString strpoint;
	strpoint = FString::Printf(TEXT("Points : %d"), point);

	Points->SetText(FText::FromString(strpoint));
}