// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMobPortal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "BossMob.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "BaseCamp.h"
#include "EngineUtils.h"
#include "InGamePlayerController.h"

ABossMobPortal::ABossMobPortal()
{
	PrimaryActorTick.bCanEverTick = true;

	bSpawning = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComponent->SetRelativeRotation(FRotator(90.0f, 0.0f, 90.0f));
	MeshComponent->SetRelativeScale3D(FVector(4.0f, 4.0f, 4.0f));
	MeshComponent->BodyInstance.SetCollisionProfileName("NoCollision");

	////에셋 지정
	//ConstructorHelpers::FObjectFinder<UStaticMesh> Shape_QuadPyramid(TEXT("/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid"));

	//if (Shape_QuadPyramid.Succeeded())
	//{
	//	MeshComponent->SetStaticMesh(Shape_QuadPyramid.Object);
	//}
}

void ABossMobPortal::BeginPlay()
{
	Super::BeginPlay();

	FoundPlayerController();
}

void ABossMobPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController)
	{
		int32 tmp = PlayerController->GetTotalNumberofMobs();
		if (tmp > 0 && tmp % 100 == 0) SpawnMobs();
	}
	else {
		FoundPlayerController();
	}
}

void ABossMobPortal::FoundPlayerController()
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
		PlayerController = Cast<AInGamePlayerController>(It->Get());
		if (PlayerController)
		{
			break;
		}
	}
}

void ABossMobPortal::SpawnMobs()
{
	if (BossMob)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;

			const FVector SpawnLocation = GetActorLocation();
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f %f %f"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z));
			//const FRotator Rotation = GetActorForwardVector().Rotation();

			FVector End;

			for (TActorIterator<ABaseCamp> It(GetWorld()); It; ++It)
			{
				End = (*It)->GetActorLocation();

			}

			FVector Start = GetActorLocation();

			FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

			ABossMob* BossMobs = World->SpawnActor<ABossMob>(BossMob, SpawnLocation, Rotation, SpawnParams);

			//플레이어 컨트롤러 찾기
			for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It) {
				PlayerController = Cast<AInGamePlayerController>(It->Get());

				if (PlayerController)
				{
					PlayerController->AddTotalNumberofMobs();
					break;
				}
			}

		}
	}
}