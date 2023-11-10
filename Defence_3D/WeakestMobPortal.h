// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "portal.h"
#include "WeakestMobPortal.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCE_3D_API AWeakestMobPortal : public Aportal
{
	GENERATED_BODY()

	AWeakestMobPortal();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SpawnMobs() override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWeakestMob> WeakestMob;

	FTimerHandle SpawnHandle;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
