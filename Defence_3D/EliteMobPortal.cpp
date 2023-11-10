// Fill out your copyright notice in the Description page of Project Settings.


#include "EliteMobPortal.h"
#include "Components/StaticMeshComponent.h"
#include "EliteMob.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseCamp.h"
#include "EngineUtils.h"
#include "InGamePlayerController.h"
#include "Components/SceneComponent.h"

AEliteMobPortal::AEliteMobPortal()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnRate = 14.27f;

	bSpawning = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, 90.0f));
	MeshComponent->SetRelativeScale3D(FVector(4.0f, 4.0f, 4.0f));
	MeshComponent->BodyInstance.SetCollisionProfileName("NoCollision");


	////에셋 지정
	//ConstructorHelpers::FObjectFinder<UStaticMesh> Shape_Torus(TEXT("/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus"));

	//if (Shape_Torus.Succeeded())
	//{
	//	MeshComponent->SetStaticMesh(Shape_Torus.Object);
	//}

}

void AEliteMobPortal::BeginPlay()
{
	Super::BeginPlay();


	//몬스터 소환
	GetWorldTimerManager().SetTimer(SpawnHandle, this, &AEliteMobPortal::SpawnMobs, SpawnRate, true, 0.0);
}

void AEliteMobPortal::Tick(float DeltaTime)
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

void AEliteMobPortal::SpawnMobs()
{
	if (EliteMob)
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

			AEliteMob* EliteMobs = World->SpawnActor<AEliteMob>(EliteMob, SpawnLocation, Rotation, SpawnParams);

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