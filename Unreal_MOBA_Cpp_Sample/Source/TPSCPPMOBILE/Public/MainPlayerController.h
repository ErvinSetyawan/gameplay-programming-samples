// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

//class APawn;

/**
 * 
 */
UCLASS()
class TPSCPPMOBILE_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

//public:
//	AMainPlayerController();
//	virtual void BeginPlay() override;
//
//	virtual void AcknowledgePossession(APawn* P) override;
//
//	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Viewing")
//	float ScreenScrollSpeed;
//
//protected:
//	// Called every frame
//	virtual void Tick(float DeltaSeconds) override;
//
//private:
//	UFUNCTION(Server, Reliable, WithValidation)
//	void S_SpawnViewingTarget(const FVector& loc, const FRotator& rot);
//
//	void SpawnViewingTarget(const FVector& loc, const FRotator& rot);
//
//	UPROPERTY(ReplicatedUsing = OnRep_ViewTarget)
//	class AViewingTarget* ViewTarget;
//
//	UFUNCTION()
//	void OnRep_ViewTarget();
//
//	void UpdateScreenScrolling() const;
//
//	void EnableCursorVisibility();
};
