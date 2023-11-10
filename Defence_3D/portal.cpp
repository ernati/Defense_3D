// Fill out your copyright notice in the Description page of Project Settings.


#include "portal.h"

// Sets default values
Aportal::Aportal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void Aportal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Aportal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called every frame
void Aportal::SpawnMobs()
{
	;
}