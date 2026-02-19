// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewingTarget.h"
#include <Components/SceneComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>

// Sets default values
AViewingTarget::AViewingTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	SetRootComponent(RootComp);
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComp);
	PlayerEye = CreateDefaultSubobject<UCameraComponent>("PlayerEye");
	PlayerEye->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	bReplicates = true;

	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritRoll = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
	CameraBoom->TargetArmLength = 1400;

}

// Called when the game starts or when spawned
void AViewingTarget::BeginPlay()
{
	Super::BeginPlay();
	SetReplicateMovement(false);
	ScreenRightDir = PlayerEye->GetRightVector();
	ScreeUpDir = FVector::CrossProduct(FVector(0, 0, 1), ScreenRightDir);
}

// Called every frame
void AViewingTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AViewingTarget::MoveScreenUp(float amt)
{
	AddActorLocalOffset(ScreeUpDir * amt);
}

void AViewingTarget::MoveScreenRight(float amt)
{
	AddActorLocalOffset(ScreenRightDir * amt);
}

