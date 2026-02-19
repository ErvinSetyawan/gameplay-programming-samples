// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCannon.generated.h"

class AEnemyProjectile;
class UArrowComponent;

UCLASS()
class TPSCPPMOBILE_API AEnemyCannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyCannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArrowComponent* ProjectileSpawnLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cannon)
	TSubclassOf<AEnemyProjectile> ProjectileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cannon)
	float FireRate;

	APawn* PlayerPawn;
	
	FTimerHandle ShotTimerHandle;
	
	void ShootCannon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cannon)
		int32 MaxHits;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Cannon)
		int32 NumHits;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Cannon)
		void DestroyCannon();
	
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, 
          class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, 
          FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

};
