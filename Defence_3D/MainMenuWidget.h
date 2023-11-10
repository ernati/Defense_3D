// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 *
 */
UCLASS()
class DEFENCE_3D_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* CloseButton;

	virtual void NativeOnInitialized() override;

protected:
	UFUNCTION()
		void OnStartClicked();

	UFUNCTION()
		void OnCloseClicked();
};
