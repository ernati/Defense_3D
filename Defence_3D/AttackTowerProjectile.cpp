// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTowerProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "WeakestMob.h"
#include "EliteMob.h"
#include "BossMob.h"
#include "HealthComponent.h"

// Sets default values
AAttackTowerProjectile::AAttackTowerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(15.0f);
	CollisionComp->SetCollisionProfileName(FName("Projectile"));
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AAttackTowerProjectile::OnBeginOverlap);

	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	MeshComp->SetCollisionProfileName(FName("Projectile"));

	InitialLifeSpan = 3.0f;

	////에셋 지정
	//ConstructorHelpers::FObjectFinder<UStaticMesh> Shape_Cube(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	//if (Shape_Cube.Succeeded())
	//{
	//	MeshComp->SetStaticMesh(Shape_Cube.Object);
	//}

}


void AAttackTowerProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (auto mob = Cast<AWeakestMob>(OtherActor))
	{
		if (mob) {
			UHealthComponent* HealthComponent = mob->FindComponentByClass<UHealthComponent>();

			if (HealthComponent)
			{
				HealthComponent->LoseHealth(damage);

				Destroy();
			}

		}
	}

	else if (auto mob2 = Cast<AEliteMob>(OtherActor))
	{
		if (mob2) {
			UHealthComponent* HealthComponent = mob2->FindComponentByClass<UHealthComponent>();

			if (HealthComponent)
			{
				HealthComponent->LoseHealth(damage);

				Destroy();
			}

		}
	}

	else if (auto mob3 = Cast<ABossMob>(OtherActor))
	{
		if (mob3) {
			UHealthComponent* HealthComponent = mob3->FindComponentByClass<UHealthComponent>();

			if (HealthComponent)
			{
				HealthComponent->LoseHealth(damage);

				Destroy();
			}

		}
	}



	

}
