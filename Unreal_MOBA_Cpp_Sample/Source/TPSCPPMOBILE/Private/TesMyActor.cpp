// Fill out your copyright notice in the Description page of Project Settings.


#include "TesMyActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATesMyActor::ATesMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BackgroundMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackgroundMeshComponent"));
    RootComponent = BackgroundMeshComponent;

    // Create health segments dynamically
    int32 NumSegments = 5; // Set the number of health segments
    HealthSegments.SetNum(NumSegments);

    for (int32 i = 0; i < NumSegments; i++)
    {
        FString SegmentName = FString::Printf(TEXT("HealthSegment_%d"), i);
        HealthSegments[i] = CreateDefaultSubobject<UStaticMeshComponent>(*SegmentName);
        HealthSegments[i]->SetupAttachment(RootComponent);
    }
}

// Called when the game starts or when spawned
void ATesMyActor::BeginPlay()
{
	Super::BeginPlay();
    CurrentHealth = MaxHealth;
}

// Called every frame
void ATesMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // Calculate the number of segments to display based on the current health
    int32 NumSegmentsToDisplay = FMath::CeilToInt((CurrentHealth / MaxHealth) * HealthSegments.Num());

    // Show or hide segments based on the current health
    for (int32 i = 0; i < HealthSegments.Num(); i++)
    {
        if (i < NumSegmentsToDisplay)
        {
            HealthSegments[i]->SetVisibility(true);
        }
        else
        {
            HealthSegments[i]->SetVisibility(false);
        }
    }
}

//void ATesMyActor::SetHealth(float NewHealth)
//{
//    CurrentHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);
//}
//
//void ATesMyActor::OnRep_CurrentHealth()
//{
//    
//}