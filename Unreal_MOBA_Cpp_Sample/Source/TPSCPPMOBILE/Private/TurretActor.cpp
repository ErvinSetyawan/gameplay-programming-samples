// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretActor.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include "EnemyProjectile.h"
#include "Main.h"
#include <Kismet/GameplayStatics.h>
#include <Components/WidgetComponent.h>

// Sets default values
ATurretActor::ATurretActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>("TriggerSphere");
	RootComponent = TriggerSphere;

	TriggerSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerSphere->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	TriggerSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	TriggerSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	TriggerSphere->SetSphereRadius(100.f);

	BoxTurretTes = CreateDefaultSubobject<UStaticMeshComponent>("BoxTurretTes");
	BoxTurretTes->SetupAttachment(RootComponent);

	ProjectileSpawnLocation = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileSpawnLocation");
	ProjectileSpawnLocation->SetupAttachment(RootComponent);

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>("WidgetComp");
	WidgetComp->SetupAttachment(RootComponent);

	FireRate = 1.f;

	TEHealth = 4600.f;
	TEMaxHealth = 4600.f;
	TEHealth = TEMaxHealth;
}

void ATurretActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"))

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ATurretActor::SpawnProjectileTowardsCharacter, FireRate, true, 0.0);
}

void ATurretActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End"))

	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ATurretActor::SpawnProjectileTowardsCharacter, FireRate, false);
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

// Called when the game starts or when spawned
void ATurretActor::BeginPlay()
{
	Super::BeginPlay();

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &ATurretActor::OnBeginOverlap);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &ATurretActor::OnEndOverlap);
}

// Called every frame
void ATurretActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
}

void ATurretActor::SpawnProjectileTowardsCharacter()
{
	// Get a reference to the player character
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	// Get the spawn location and rotation for the actor
	FVector SpawnLocation = ProjectileSpawnLocation->GetComponentLocation();
	FRotator SpawnRotation = (PlayerPawn->GetActorLocation() - SpawnLocation).Rotation();

	// Spawn the actor with the calculated location and rotation
	GetWorld()->SpawnActor<AEnemyProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
}
