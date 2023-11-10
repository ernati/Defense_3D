// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTower.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "AttackTowerProjectile.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"
#include "WeakestMob.h"

AAttackTower::AAttackTower()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnRate = 2.5f;

	bSpawning = true;

	meshcomp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	scenecomp = CreateDefaultSubobject<USceneComponent>(TEXT("scene"));

	RootComponent = meshcomp;

	////에셋 지정
	//ConstructorHelpers::FObjectFinder<UStaticMesh> Shape_Cone(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));

	//if (Shape_Cone.Succeeded())
	//{
	//	meshcomp->SetStaticMesh(Shape_Cone.Object);
	//}
}


// Called when the game starts or when spawned
void AAttackTower::BeginPlay()
{
	Super::BeginPlay();

	//몬스터 소환
	GetWorldTimerManager().SetTimer(SpawnHandle, this, &AAttackTower::SpawnProjectile, SpawnRate, true, 0.0);
}

// Called every frame
void AAttackTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSpawning)
	{
		;
	}

	else {
		//몬스터 소환을 멈춘다.
		GetWorldTimerManager().ClearTimer(SpawnHandle);
	}

}

void AAttackTower::SpawnProjectile()
{
	if (attackTowerProjectile)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;

			//const FVector SpawnLocation = scenecomp->GetComponentLocation();
			const FVector SpawnLocation = GetActorLocation();
			//const FRotator Rotation = GetActorForwardVector().Rotation();

			FVector End;

			float min_distance = 100000.0f;

			//몹 찾기
			for (TActorIterator<AEnemy> It(GetWorld()); It; ++It)
			{
				if (*It) {
					//End = (*It)->GetActorLocation();
					auto temp = (*It)->GetActorLocation();
					auto dist = FVector::Dist(temp, SpawnLocation);

					if (dist < min_distance) {
						min_distance = dist;
						End = temp;
					}
				}
			}

			FVector Start = GetActorLocation();

			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

			AAttackTowerProjectile* projectiles = World->SpawnActor<AAttackTowerProjectile>(attackTowerProjectile, SpawnLocation, Rotation, SpawnParams);

		}
	}
}