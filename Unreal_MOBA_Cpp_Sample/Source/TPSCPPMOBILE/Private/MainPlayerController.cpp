// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "ViewingTarget.h"
#include "Net/UnrealNetwork.h"

//AMainPlayerController::AMainPlayerController():ScreenScrollSpeed(20.f)
//{
//
//}
//
//void AMainPlayerController::BeginPlay()
//{
//	Super::BeginPlay();
//
//	EnableCursorVisibility();
//}
//
//void AMainPlayerController::AcknowledgePossession(APawn* P)
//{
//	Super::AcknowledgePossession(P);
//
//	if (P)
//	{
//		S_SpawnViewingTarget(P->GetActorLocation(), P->GetActorRotation());
//	}
//}
//
//void AMainPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//	DOREPLIFETIME(AMainPlayerController, ViewTarget);
//}
//
//void AMainPlayerController::Tick(float DeltaSeconds)
//{
//	Super::Tick(DeltaSeconds);
//
//	UpdateScreenScrolling();
//}
//
//void AMainPlayerController::S_SpawnViewingTarget_Implementation(const FVector& loc, const FRotator& rot)
//{
//	SpawnViewingTarget(loc, rot);
//}
//
//bool AMainPlayerController::S_SpawnViewingTarget_Validate(const FVector& loc, const FRotator& rot)
//{
//	return true;
//}
//
//void AMainPlayerController::SpawnViewingTarget(const FVector& loc, const FRotator& rot)
//{
//	FActorSpawnParameters Spawnparams;
//	Spawnparams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//	ViewTarget = GetWorld()->SpawnActor<AViewingTarget>(loc, rot, Spawnparams);
//}
//
//void AMainPlayerController::OnRep_ViewTarget()
//{
//	if (ViewTarget)
//	{
//		//FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
//		SetViewTarget(ViewTarget);
//	}
//}
//
//void AMainPlayerController::UpdateScreenScrolling() const
//{
//	if (IsLocalController() && ViewTarget)
//	{
//		FVector2D MouseLoc;
//		GetMousePosition(MouseLoc.X, MouseLoc.Y);
//		int ViewPortSizeX, ViewPortSizeY;
//		GetViewportSize(ViewPortSizeX, ViewPortSizeY);
//		if (MouseLoc.X < 20.f || MouseLoc.X > ViewPortSizeX - 20.f)
//		{
//			const float ScrollDir = MouseLoc.X < ViewPortSizeX / 2 ? -1 : 1;
//			ViewTarget->MoveScreenRight(ScrollDir * ScreenScrollSpeed);
//		}
//		if (MouseLoc.Y < 20.f || MouseLoc.Y > ViewPortSizeY - 20.f)
//		{
//			const float ScrollDir = MouseLoc.Y < ViewPortSizeY / 2 ? -1 : 1;
//			ViewTarget->MoveScreenUp(ScrollDir * ScreenScrollSpeed);
//		}
//	}
//}
//
//void AMainPlayerController::EnableCursorVisibility()
//{
//	FInputModeGameAndUI InputMode;
//	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
//	bShowMouseCursor = true;
//	SetInputMode(InputMode);
//}
