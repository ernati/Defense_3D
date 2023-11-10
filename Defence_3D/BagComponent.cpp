// Fill out your copyright notice in the Description page of Project Settings.


#include "BagComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UBagComponent::UBagComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UBagComponent::GetPoint()
{
	point++;
}

void UBagComponent::GetPoints(int32 Amount)
{
	point+=Amount;
}

int32 UBagComponent::ReturnPoint()
{
	return point;
}

void UBagComponent::UsePoint(int32 use)
{
	if (point >= use) {
		point -= use;
	}
}


// Called when the game starts
void UBagComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UBagComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


