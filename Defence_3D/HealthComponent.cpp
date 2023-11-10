// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
//#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"
#include "InGamePlayerController.h"
#include "WeakestMob.h"
#include "Kismet/GameplayStatics.h"
#include "Defence_3DCharacter.h"
#include "FPSCharacter.h"
#include "EliteMob.h"
#include "BossMob.h"
#include "BaseCamp.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::LoseHealth(float Amount)
{
	CurrentHealth -= Amount;

	if (CurrentHealth <= 0.0f) {
		CurrentHealth = 0.0f;

		//UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);

		AInGamePlayerController* PlayerController = nullptr;

		//플레이어 컨트롤러 찾기
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
			PlayerController = Cast<AInGamePlayerController>(It->Get());

			if (PlayerController)
			{
				PlayerController->AddTotalKills();
				break;
			}
		}

		//ADefence_3DCharacter* Player = Cast<ADefence_3DCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		AFPSCharacter* Player = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

		if (Player)
		{
			/*Player->GetPoint();*/
			AWeakestMob* a1 = Cast<AWeakestMob>(GetOwner());
			AEliteMob* a2 = Cast<AEliteMob>(GetOwner());
			ABossMob* a3 = Cast<ABossMob>(GetOwner());
			ABaseCamp* a4 = Cast<ABaseCamp>(GetOwner());
			if (a1) {
				Player->GetPoint();
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You Kill Weakable Mob!"));
			}

			if (a2) {
				Player->GetPoints(ElitePoint);
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You Kill Elite Mob!"));
			}

			if (a3) {
				Player->GetPoints(BossPoint);
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("You Kill Boss Mob!"));
			}
			if (a4) {
				if (PlayerController)
				{
					PlayerController->ShowRestartWidget();
				}
			}
		}

		GetOwner()->Destroy();
	}

	else {
		;
	}
}

void UHealthComponent::GetHealth(float Amount)
{
	CurrentHealth += Amount;

	if (CurrentHealth >= MaxHealth) {
		CurrentHealth = MaxHealth;
	}

	else {
		;
	}
}

void UHealthComponent::SetMaxHealth(float Amount)
{
	MaxHealth = Amount;
	CurrentHealth = MaxHealth;
}

float UHealthComponent::ReturnCurrentHealth()
{
	return CurrentHealth;
}

float UHealthComponent::ReturnMaxHealth()
{
	return MaxHealth;
}

float UHealthComponent::ReturnHealthRatio()
{
	if (CurrentHealth / MaxHealth > 0)
	{
		return CurrentHealth / MaxHealth;
	}
	else {
		return 0.0f;
	}
}