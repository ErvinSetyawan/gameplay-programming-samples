// Fill out your copyright notice in the Description page of Project Settings.


#include "Minion.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
AMinion::AMinion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MinionSphere = CreateDefaultSubobject<USphereComponent>("MinionSphere");
	RootComponent = MinionSphere;

	MinionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	MinionSphere->SetSphereRadius(50.f);

	MinionMesh = CreateDefaultSubobject<UStaticMeshComponent>("MinionMesh");
	MinionMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMinion::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


