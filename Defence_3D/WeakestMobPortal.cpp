// Fill out your copyright notice in the Description page of Project Settings.


#include "WeakestMobPortal.h"
#include "Components/StaticMeshComponent.h"
#include "WeakestMob.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseCamp.h"
#include "EngineUtils.h"
#include "InGamePlayerController.h"
#include "Components/SceneComponent.h"

AWeakestMobPortal::AWeakestMobPortal()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnRate = 1.85f;

	bSpawning = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, 90.0f));
	MeshComponent->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
	MeshComponent->BodyInstance.SetCollisionProfileName("NoCollision");


	////에셋 지정
	//ConstructorHelpers::FObjectFinder<UStaticMesh> Shape_Pipe(TEXT("/Game/StarterContent/Shapes/Shape_Pipe.Shape_Pipe"));

	//if (Shape_Pipe.Succeeded())
	//{
	//	MeshComponent->SetStaticMesh(Shape_Pipe.Object);
	//}

}

void AWeakestMobPortal::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

	//몬스터 소환
	GetWorldTimerManager().SetTimer(SpawnHandle, this, &AWeakestMobPortal::SpawnMobs, SpawnRate, true, 0.0);
}

void AWeakestMobPortal::Tick(float DeltaTime)
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

void AWeakestMobPortal::SpawnMobs()
{
	if (WeakestMob)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;

			const FVector SpawnLocation = GetActorLocation();
			//const FRotator Rotation = GetActorForwardVector().Rotation();

			FVector End;

			for (TActorIterator<ABaseCamp> It(GetWorld()); It; ++It)
			{
				End = (*It)->GetActorLocation();

			}

			FVector Start = GetActorLocation();

			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

			AWeakestMob* WeakestMobs = World->SpawnActor<AWeakestMob>(WeakestMob, SpawnLocation, Rotation, SpawnParams);

			//플레이어 컨트롤러 찾기
			for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
				const auto PlayerController = Cast<AInGamePlayerController>(It->Get());

				if (PlayerController)
				{
					PlayerController->AddTotalNumberofMobs();
					break;
				}
			}
		}
	}
}