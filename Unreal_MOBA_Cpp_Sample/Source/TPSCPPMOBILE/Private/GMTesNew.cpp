// Fill out your copyright notice in the Description page of Project Settings.


#include "GMTesNew.h"
#include <TimerManager.h>
#include <GameFramework/Actor.h>
#include "Minion.h"
#include "MainActorComponent.h"

AGMTesNew::AGMTesNew()
{
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGMTesNew::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGMTesNew::SpawnActorEvery30Seconds, 5.0f, true);
}

void AGMTesNew::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UpdateStopwatch();
}

//void AGMTesNew::StartStopwatch()
//{
//    if (!bIsRunning)
//    {
//        GetWorldTimerManager().SetTimer(TimerHandle, this, &AGMTesNew::UpdateStopwatch, 0.01f, true);
//        bIsRunning = true;
//    }
//}
//
//void AGMTesNew::StopStopwatch()
//{
//    if (bIsRunning)
//    {
//        GetWorldTimerManager().ClearTimer(TimerHandle);
//        bIsRunning = false;
//    }
//}

void AGMTesNew::SpawnActorEvery30Seconds()
{
    FVector SpawnLocation = FVector(6285.280273, 11801.833984, 7.106995);
    FRotator SpawnRotation = FRotator::ZeroRotator;

    AMinion* SpawnedActor = GetWorld()->SpawnActor<AMinion>(MinionClass, SpawnLocation, SpawnRotation);
}

//void AGMTesNew::UpdateStopwatch()
//{
//    ElapsedTime += 0.01f; // Increment the elapsed time
//    // You can perform any additional logic here with the elapsed time
//    // Convert elapsed time to minutes, seconds, and milliseconds
//    Minutes = FMath::FloorToInt(ElapsedTime / 60.0f);
//    Seconds = FMath::FloorToInt(FMath::Fmod(ElapsedTime, 60.0f));
//
//    // Print the stopwatch time
//    FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
//    UE_LOG(LogTemp, Warning, TEXT("Stopwatch Time: %s"), *TimeString);
//
//   // Main = Cast<AMain>(GetWorld());
//
//	if (ElapsedTime >= 5) {
//		UE_LOG(LogTemp, Warning, TEXT("5"));
//	}
//
//    if (ElapsedTime >= 10) {
//        UE_LOG(LogTemp, Warning, TEXT("5"));
//        //MainActorComp->Level = 2;
//    }
//
//    if (ElapsedTime >= 40) {
//        UE_LOG(LogTemp, Warning, TEXT("40"));
//    }
//}