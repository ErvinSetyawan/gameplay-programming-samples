// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretActor.generated.h"

class AEnemyProjectile;

UCLASS()
class TPSCPPMOBILE_API ATurretActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretActor();

	UPROPERTY(visibleanywhere, BlueprintReadWrite)
	class UWidgetComponent* WidgetComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Turret)
	class USphereComponent* TriggerSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Turret)
	class UStaticMeshComponent* BoxTurretTes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Turret)
	UStaticMeshComponent* ProjectileSpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Turret)
	TSubclassOf<AEnemyProjectile> ProjectileClass;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cannon)
	float FireRate;
	
	FTimerHandle ShotTimerHandle;

	void SpawnProjectileTowardsCharacter();

	bool bInTurret = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurretEnemyStats)
	float TEHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurretEnemyStats)
	float TEMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurretEnemyStats)
	float TEDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TurretEnemyStats)
	class UParticleSystem* HitParticles;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
