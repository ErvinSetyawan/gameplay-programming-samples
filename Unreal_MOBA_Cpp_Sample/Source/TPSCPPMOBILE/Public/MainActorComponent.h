// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MainActorComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UMainActorComponent*, OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TPSCPPMOBILE_API UMainActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMainActorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	//Stats hero

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float RegenHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Damage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int Segments;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
	float MaxMana;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float ProgressLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float ProgressMaxLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int Level;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*UFUNCTION(BlueprintCallable, Category = Stats)
	bool ApplyHeatlhChange(float Delta);*/

	/*UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;*/

};
