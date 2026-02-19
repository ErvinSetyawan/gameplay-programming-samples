// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCannon.h"
#include <Components/ArrowComponent.h>
#include <Kismet/GameplayStatics.h>
#include "EnemyProjectile.h"
#include "Main.h"
#include <GameFramework/Actor.h>

// Sets default values
AEnemyCannon::AEnemyCannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	StaticMesh->SetupAttachment(RootScene);

	ProjectileSpawnLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnLocation"));
	ProjectileSpawnLocation->SetupAttachment(StaticMesh);

	FireRate = 5.f;
	MaxHits = 5;
}

// Called when the game starts or when spawned
void AEnemyCannon::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AEnemyCannon::ShootCannon, FireRate, true);
}

// Called every frame
void AEnemyCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Direction = PlayerPawn->GetActorLocation() - StaticMesh->GetComponentLocation();

	FRotator Rotator = FVector(Direction.X, Direction.Y, 0).Rotation();

	StaticMesh->SetWorldRotation(Rotator);
}

void AEnemyCannon::ShootCannon()
{
	GetWorld()->SpawnActor<AEnemyProjectile>(ProjectileClass, ProjectileSpawnLocation->GetComponentTransform());
}

void AEnemyCannon::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other,
	class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation,
	FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal,
		NormalImpulse, Hit);

	if (Cast<AMain>(Other) != nullptr)
	{
		NumHits++;

		if (NumHits == MaxHits)
		{
			DestroyCannon();
		}
	}
}

void AEnemyCannon::DestroyCannon_Implementation()
{
	Destroy();
}