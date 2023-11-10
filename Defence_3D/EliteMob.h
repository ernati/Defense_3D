// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EliteMob.generated.h"

/**
 *
 */
UCLASS()
class DEFENCE_3D_API AEliteMob : public AEnemy
{
	GENERATED_BODY()

		AEliteMob();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//baseCamp에 부딪힐 경우 데미지를 줌.
	UFUNCTION(BlueprintCallable)
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(BlueprintReadWrite, Category = UI)
		class UWidgetComponent* HPBarWidget;

};
