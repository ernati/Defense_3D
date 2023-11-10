// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (StartButton != nullptr) {
		StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartClicked);
	}
	if (CloseButton != nullptr) {
		CloseButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnCloseClicked);
	}
}

//시작 버튼 -> Level1 을 open한다.
void UMainMenuWidget::OnStartClicked()
{

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Ingame"));
}

//종료 버튼 -> 게임을 종료한다.
void UMainMenuWidget::OnCloseClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

