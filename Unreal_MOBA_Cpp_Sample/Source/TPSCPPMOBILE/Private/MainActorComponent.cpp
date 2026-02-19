// Fill out your copyright notice in the Description page of Project Settings.


#include "MainActorComponent.h"
#include "GMTesNew.h"
#include <TimerManager.h>

// Sets default values for this component's properties
UMainActorComponent::UMainActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 2500.f;
	Health = MaxHealth;
    RegenHealth = 122.f;
    Damage = 230.f;
	Segments = 1;
	MaxMana = 200.f;
	Mana = 100.f;
    ProgressLevel = 0.f;
    ProgressMaxLevel = 100.f;
	Level = 1;
}


// Called when the game starts
void UMainActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMainActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//bool UMainActorComponent::ApplyHeatlhChange(float Delta)
//{
//	Health += Delta;
//
//	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
//
//	return true;
//}

