// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "AttackTower.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCE_3D_API AAttackTower : public ATower
{
	GENERATED_BODY()

	AAttackTower();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnProjectile();


	float SpawnRate;
	bool bSpawning;

private:
	FTimerHandle SpawnHandle;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//weaponcomponent
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USceneComponent* scenecomp;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AAttackTowerProjectile> attackTowerProjectile;
};
