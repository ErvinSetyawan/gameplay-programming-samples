// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ViewingTarget.generated.h"

UCLASS()
class TPSCPPMOBILE_API AViewingTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AViewingTarget();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Viewing")
	class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Viewing")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Viewing")
	class UCameraComponent* PlayerEye;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveScreenUp(float amt);
	void MoveScreenRight(float amt);

private:
	FVector ScreeUpDir;
	FVector ScreenRightDir;
};
