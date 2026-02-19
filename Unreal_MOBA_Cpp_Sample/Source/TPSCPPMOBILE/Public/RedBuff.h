// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RedBuff.generated.h"

UENUM(BlueprintType)
enum class ERedBuffStatus : uint8
{
	ERBS_Idle UMETA(DisplayName = "Idle"),
	ERBS_MoveToTarget UMETA(DisplayName = "MoveToTarget"),
	ERBS_Attacking UMETA(DisplayName = "Attacking"),

	ERBS_Max UMETA(DisplayName = "DefaultMax")
};

UCLASS()
class TPSCPPMOBILE_API ARedBuff : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARedBuff();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RedBuff Status")
	ERedBuffStatus RedBuffStatus;

	FORCEINLINE void SetRedBuffStatus(ERedBuffStatus Status) { RedBuffStatus = Status; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
