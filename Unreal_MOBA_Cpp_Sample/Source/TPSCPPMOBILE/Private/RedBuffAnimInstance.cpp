// Fill out your copyright notice in the Description page of Project Settings.


#include "RedBuffAnimInstance.h"
#include "RedBuff.h"

void URedBuffAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
}

void URedBuffAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();
		RedBuff = Cast<ARedBuff>(Pawn);
	}
}