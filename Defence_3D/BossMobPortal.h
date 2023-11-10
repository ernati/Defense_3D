// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "portal.h"
#include "BossMobPortal.generated.h"

/**
 *
 */
UCLASS()
class DEFENCE_3D_API ABossMobPortal : public Aportal
{
	GENERATED_BODY()

	ABossMobPortal();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void FoundPlayerController();

	
private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABossMob> BossMob;

	class AInGamePlayerController* PlayerController;

public:

	virtual void SpawnMobs() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
