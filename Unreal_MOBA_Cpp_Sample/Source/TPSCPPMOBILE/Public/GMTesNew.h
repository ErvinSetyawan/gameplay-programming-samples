// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GMTesNew.generated.h"

class AMinion;

/**
 * 
 */
UCLASS()
class TPSCPPMOBILE_API AGMTesNew : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    AGMTesNew();

    virtual void Tick(float DeltaTime) override;

	/* UFUNCTION(BlueprintCallable, Category = "Stopwatch")
	 void StartStopwatch();

	 UFUNCTION(BlueprintCallable, Category = "Stopwatch")
	 void StopStopwatch();

	 UPROPERTY(BlueprintReadOnly)
	 int Minutes;

	 UPROPERTY(BlueprintReadOnly)
	 int Seconds;*/

    UFUNCTION(BlueprintCallable, Category = "Stopwatch")
    void SpawnActorEvery30Seconds();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Turret)
	TSubclassOf<AMinion> MinionClass;

    class UMainActorComponent* MainComp;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
	FTimerHandle TimerHandle;
	/*FTimerHandle TimerHandle;
	float ElapsedTime;
	bool bIsRunning;

	UFUNCTION(BlueprintCallable, Category = "Stopwatch")
	void UpdateStopwatch();*/
};
