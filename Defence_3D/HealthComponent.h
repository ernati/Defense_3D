// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEFENCE_3D_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	void LoseHealth(float Amount);
	void GetHealth(float Amount);
	FORCEINLINE float GetHealthPercent() const { return CurrentHealth / MaxHealth; };

	void SetMaxHealth(float Amount);

	float ReturnCurrentHealth();
	float ReturnMaxHealth();

	UFUNCTION(BluePrintCallable)
	float ReturnHealthRatio();

	int32 BossPoint = 100.0;
	int32 ElitePoint = 40.0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Health)
		float MaxHealth;

	UPROPERTY(EditDefaultsOnly, Category = Health)
		float CurrentHealth;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
