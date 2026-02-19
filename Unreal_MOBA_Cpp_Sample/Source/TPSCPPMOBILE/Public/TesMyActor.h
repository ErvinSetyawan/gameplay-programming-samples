// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TesMyActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class TPSCPPMOBILE_API ATesMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATesMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* BackgroundMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		TArray<UStaticMeshComponent*> HealthSegments;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
		float CurrentHealth;

	/*UFUNCTION()
		void OnRep_CurrentHealth();*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void SetHealth(float NewHealth);
};
