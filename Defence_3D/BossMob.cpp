// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMob.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "HealthComponent.h"
#include "BaseCamp.h"
#include "Components/WidgetComponent.h"

ABossMob::ABossMob() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Damage = 100.0f;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	
	//캡슐 절반높이, 반경 설정, 회전 설정
	CapsuleComp->SetCapsuleHalfHeight(300.0f);
	CapsuleComp->SetCapsuleRadius(130.0f);
	CapsuleComp->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));

	CapsuleComp->SetCollisionProfileName(FName("Enemy"));
	CapsuleComp->OnComponentHit.AddDynamic(this, &ABossMob::OnHit);
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ABossMob::OnBeginOverlap);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->AttachToComponent(CapsuleComp, FAttachmentTransformRules::KeepWorldTransform);
	MeshComponent->SetRelativeLocation(FVector(28.0f, 50.0f, 7.0f));
	MeshComponent->SetRelativeScale3D(FVector(20.0f, 20.0f, 20.0f));
	MeshComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	MeshComponent->SetCollisionProfileName(FName("Enemy"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("health"));
	HealthComponent->SetMaxHealth(2000);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CapsuleComp;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 25.0f;
	ProjectileMovement->MaxSpeed = 25.0f;

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget->SetupAttachment(RootComponent);
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 400.0f));

	/*static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD( TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Defense/Widgets/Ingame/BP_HPBar.BP_HPBar'"));
	if (UI_HUD.Succeeded()) {
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(150.0f, 150.0f));
	}*/


	////에셋 지정
	//ConstructorHelpers::FObjectFinder<UStaticMesh> Shape_Sphere(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	//if (Shape_Sphere.Succeeded())
	//{
	//	MeshComponent->SetStaticMesh(Shape_Sphere.Object);
	//}
}

// Called every frame
void ABossMob::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void ABossMob::BeginPlay()
{
	Super::BeginPlay();

}

void ABossMob::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ABaseCamp* basecamp = Cast< ABaseCamp >(OtherActor);

	if (basecamp) {
		//basecamp의 체력을 깎는다.

		UHealthComponent* HealthComp = basecamp->GetHealthComponent();

		if (HealthComp)
		{
			HealthComp->LoseHealth(Damage);
		}

		Destroy();
	}
	
}

void ABossMob::OnBeginOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

}