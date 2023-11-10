// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "portal.generated.h"

UCLASS()
class DEFENCE_3D_API Aportal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Aportal();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* MeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SpawnMobs();


	float SpawnRate;
	bool bSpawning;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
