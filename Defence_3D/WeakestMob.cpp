// Fill out your copyright notice in the Description page of Project Settings.


#include "WeakestMob.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "HealthComponent.h"
#include "BaseCamp.h"
#include "Components/WidgetComponent.h"

AWeakestMob::AWeakestMob() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Damage = 20.0f;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(50.0f);
	CollisionComp->SetCollisionProfileName(FName("Enemy"));
	CollisionComp->OnComponentHit.AddDynamic(this, &AWeakestMob::OnHit);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AWeakestMob::OnBeginOverlap);

	RootComponent = CollisionComp;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComponent->SetRelativeLocation(FVector(-6.0f, 0.0f, -32.0f));
	MeshComponent->SetRelativeScale3D(FVector(2.5f, 2.5, 4.0f));
	MeshComponent->SetCollisionProfileName(FName("Enemy"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("health"));
	HealthComponent->SetMaxHealth(80);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 100.0f;
	ProjectileMovement->MaxSpeed = 100.0f;

	HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget->SetupAttachment(CollisionComp);
	HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));

	/*static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Defense/Widgets/Ingame/BP_HPBar.BP_HPBar'"));
	if (UI_HUD.Succeeded()) {
		HPBarWidget->SetWidgetClass(UI_HUD.Class);
		HPBarWidget->SetDrawSize(FVector2D(50.0f, 15.0f));
	}*/

}

// Called every frame
void AWeakestMob::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void AWeakestMob::BeginPlay()
{
	Super::BeginPlay();

}

void AWeakestMob::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ABaseCamp* basecamp = Cast< ABaseCamp >(OtherActor);

	if (basecamp) {
		//basecamp의 체력을 깎는다.

		UHealthComponent* HealthComp = basecamp->GetHealthComponent();

		if (HealthComp)
		{
			HealthComp->LoseHealth(Damage);
		}
		
		//UE_LOG(LogTemp, Warning, TEXT("BaseCamp's Current Health is %f"), HealthComp->ReturnCurrentHealth());
		Destroy();
	}

}

void AWeakestMob::OnBeginOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

}