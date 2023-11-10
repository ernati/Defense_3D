// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCamp.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ABaseCamp::ABaseCamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(100.0f);
	CollisionComp->SetCollisionProfileName(FName("basecamp"));
	//CollisionComponent->OnComponentHit.AddDynamic(this, &APlayerProjectile::OnHit);

	RootComponent = CollisionComp;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComponent->SetCollisionProfileName(FName("basecamp"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("health"));
	HealthComponent->SetMaxHealth(5000);

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget->SetupAttachment(MeshComponent);
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	
	////에셋 지정
	//ConstructorHelpers::FObjectFinder<UStaticMesh> Shape_Cylinder(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));

	//if (Shape_Cylinder.Succeeded())
	//{
	//	MeshComponent->SetStaticMesh(Shape_Cylinder.Object);
	//}

}

// Called when the game starts or when spawned
void ABaseCamp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//==============GET=================

UHealthComponent* ABaseCamp::GetHealthComponent() {
	return HealthComponent;
}
