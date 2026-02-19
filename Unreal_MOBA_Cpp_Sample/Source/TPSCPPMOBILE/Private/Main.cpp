// Fill out your copyright notice in the Description page of Project Settings.


#include "Main.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Blueprint/UserWidget.h>
#include <TESWIDGET.h>
#include <Components/WidgetComponent.h>
#include "MainActorComponent.h"
#include <Kismet/GameplayStatics.h>
#include "WidgetStatsHero.h"
#include <Components/ProgressBar.h>
#include <Components/TextBlock.h>
#include <Engine/Engine.h>
#include <Components/TimelineComponent.h>
#include <Components/Image.h>
#include <Components/HorizontalBox.h>
#include "Components/HorizontalBoxSlot.h"

// Sets default values
AMain::AMain()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LastComboTime = 0.0f;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 0.f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	CameraComp->bUsePawnControlRotation = false;
	//CameraComp->SetRelativeLocation(FVector(-520.f, 620.f, 1100.f));
	//CameraComp->SetRelativeRotation(FRotator(0.f, -50.f, -50.f));

	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	GetCapsuleComponent()->SetCapsuleSize(48.f, 105.f);

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;

	WidgetComp = CreateDefaultSubobject<UWidgetComponent>("WidgetComp");
	WidgetComp->SetupAttachment(RootComponent);

	AttributeComp = CreateDefaultSubobject<UMainActorComponent>("AttributeComp");

	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("MyTimeline"));

	InterpFunction.BindUFunction(this, FName("TimelineFloatReturn"));
	TimelineFinishedCallback.BindUFunction(this, FName("TimelineFinishedCallbackFunc"));

	MaxHealth = 2500.f;
	Health = MaxHealth;
	RegenHealth = 122.f;
	SetReplicates(true);
}

void AMain::EventDamagedHP(float val)
{
	HPProgressBar->SetPercent(val);
	HPDamageProgressBarShow();
}

void AMain::EventRegenHP(float val)
{
	HPDamageProgressBar->SetPercent(val);
	HPRegenProgressBarShow();
}

void AMain::HPDamageProgressBarShow()
{
	if (HPProgressBar->Percent != HPDamageProgressBar->Percent)
	{
		if (HPProgressBar->Percent < HPDamageProgressBar->Percent)
		{
			bIsShowDamageHPBar = true;
			bIsShowRegenHPBar = false;
			HPDamageProgressBar->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			bIsShowDamageHPBar = false;
		}
	}
}

void AMain::HPRegenProgressBarShow()
{
	if (HPProgressBar->Percent != HPDamageProgressBar->Percent)
	{
		if (HPDamageProgressBar->Percent > HPProgressBar->Percent)
		{
			bIsShowDamageHPBar = false;
			bIsShowRegenHPBar = true;
			HPDamageProgressBar->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			bIsShowRegenHPBar = false;
		}
	}
}

void AMain::TimelineFloatReturn(float Value)
{
	NewHPVar = FMath::Clamp(Health + RegenHealth, 0.0f, MaxHealth);
	NewHPDivideVar = NewHPVar / MaxHealth;
	EventDamagedHP(FMath::Lerp(Health / MaxHealth, NewHPDivideVar, Value));
}

void AMain::TimelineFinishedCallbackFunc()
{
	// Timeline has finished playing, perform any necessary actions
	UE_LOG(LogTemp, Warning, TEXT("finish"));
}

void AMain::PlayTimeline()
{
	if (MyTimeline != nullptr)
	{
		MyTimeline->AddInterpFloat(CurveFloat, InterpFunction);
		MyTimeline->SetLooping(false);
		MyTimeline->SetNetAddressable(); // This component has a stable name that can be referenced for replication
		MyTimeline->SetTimelineFinishedFunc(TimelineFinishedCallback);
		MyTimeline->PlayFromStart();
	}
}

void AMain::PlayReverseTimeline()
{
	if (MyTimeline != nullptr)
	{
		MyTimeline->AddInterpFloat(CurveFloat, InterpFunction);
		MyTimeline->SetLooping(false);
		MyTimeline->SetNetAddressable(); // This component has a stable name that can be referenced for replication
		MyTimeline->SetTimelineFinishedFunc(TimelineFinishedCallback);
		MyTimeline->ReverseFromEnd();
	}
}

void AMain::ZKey()
{
	NewDamageHPVar = FMath::Clamp(Health - AttributeComp->Damage, 0.0f, MaxHealth);
	Health = NewDamageHPVar;
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("%f"), NewDamageHPVar));
	EventDamagedHP(Health / MaxHealth);
}

void AMain::CKey()
{
	NewAddHPVar = FMath::Clamp(Health + RegenHealth, 0.0f, MaxHealth);
	Health = NewAddHPVar;
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewAddHPVar));
	EventRegenHP(Health / MaxHealth);
}

void AMain::VKey()
{
	NewLevel = 2354.f;
	MaxHealth += NewLevel;
	HPProgressBar->SetPercent(Health / MaxHealth);
	HPDamageProgressBar->SetPercent(Health / MaxHealth);
}

void AMain::ProgressLevelEvery1Seconds()
{
	if (AttributeComp->Level <= 14)
	{
		AttributeComp->ProgressLevel = FMath::Clamp(AttributeComp->ProgressLevel + 20.0f, 0.0f, AttributeComp->ProgressMaxLevel);
		LevelProgressimg->GetDynamicMaterial()->SetScalarParameterValue("GaugePercent", AttributeComp->ProgressLevel / AttributeComp->ProgressMaxLevel);
	}
	if (AttributeComp->Level > 14) {
		GetWorldTimerManager().SetTimer(TimerSegments, this, &AMain::ProgressLevelEvery1Seconds, 0.1f, false);
		GetWorldTimerManager().ClearTimer(TimerSegments);
	}
	if (AttributeComp->ProgressLevel == 100)
	{
		AttributeComp->Level += 1;
		MaxHealth += 300;
		AttributeComp->ProgressLevel = 0.f;
		HPProgressBar->SetPercent(Health / MaxHealth);
		HPDamageProgressBar->SetPercent(Health / MaxHealth);
		LevelProgressimg->GetDynamicMaterial()->SetScalarParameterValue("GaugePercent", AttributeComp->ProgressLevel / AttributeComp->ProgressMaxLevel);

		// Segments HP Bar Logic
		if (MaxHealth >= 2000 && MaxHealth < 3000)
		{
			if (AttributeComp->Segments == 2)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("2222222")));
			}
			else
			{
				AttributeComp->Segments += 1;
				NewSegment = AttributeComp->Segments;
				AddSegmentsHPBar();
				//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
			}
		}
		else
		{
			if (MaxHealth >= 3000 && MaxHealth < 4000)
			{
				if (AttributeComp->Segments == 3)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("33333")));
				}
				else
				{
					AttributeComp->Segments += 1;
					NewSegment = AttributeComp->Segments;
					AddSegmentsHPBar();
					//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
				}
			}
			else
			{
				if (MaxHealth >= 4000 && MaxHealth < 5000)
				{
					if (AttributeComp->Segments == 4)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("444444")));
					}
					else
					{
						AttributeComp->Segments += 1;
						NewSegment = AttributeComp->Segments;
						AddSegmentsHPBar();
						//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
					}
				}
				else
				{
					if (MaxHealth >= 5000 && MaxHealth < 6000)
					{
						if (AttributeComp->Segments == 5)
						{
							//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("5555")));
						}
						else
						{
							AttributeComp->Segments += 1;
							NewSegment = AttributeComp->Segments;
							AddSegmentsHPBar();
							//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
						}
					}
					else
					{
						if (MaxHealth >= 6000 && MaxHealth < 7000)
						{
							if (AttributeComp->Segments == 6)
							{
								//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("6666")));
							}
							else
							{
								AttributeComp->Segments += 1;
								NewSegment = AttributeComp->Segments;
								AddSegmentsHPBar();
								//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
							}
						}
						else
						{
							if (MaxHealth >= 7000 && MaxHealth < 8000)
							{
								if (AttributeComp->Segments == 7)
								{
									//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("7777")));
								}
								else
								{
									AttributeComp->Segments += 1;
									NewSegment = AttributeComp->Segments;
									AddSegmentsHPBar();
									//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
								}
							}
							else
							{
								if (MaxHealth >= 8000 && MaxHealth < 9000)
								{
									if (AttributeComp->Segments == 8)
									{
										//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("8888")));
									}
									else
									{
										AttributeComp->Segments += 1;
										NewSegment = AttributeComp->Segments;
										AddSegmentsHPBar();
										//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
									}
								}
								else
								{
									if (MaxHealth >= 9000 && MaxHealth < 10000)
									{
										if (AttributeComp->Segments == 9)
										{
											//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("99999")));
										}
										else
										{
											AttributeComp->Segments += 1;
											NewSegment = AttributeComp->Segments;
											AddSegmentsHPBar();
											//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
										}
									}
									else
									{
										if (MaxHealth >= 10000 && MaxHealth < 11000)
										{
											if (AttributeComp->Segments == 10)
											{
												//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("101010")));
											}
											else
											{
												AttributeComp->Segments += 1;
												NewSegment = AttributeComp->Segments;
												AddSegmentsHPBar();
												//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
											}
										}
										else
										{
											if (MaxHealth >= 11000 && MaxHealth < 12000)
											{
												if (AttributeComp->Segments == 11)
												{
													//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("111111")));
												}
												else
												{
													AttributeComp->Segments += 1;
													NewSegment = AttributeComp->Segments;
													AddSegmentsHPBar();
													//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
												}
											}
											else
											{
												if (MaxHealth >= 12000 && MaxHealth < 13000)
												{
													if (AttributeComp->Segments == 12)
													{
														//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("121212")));
													}
													else
													{
														AttributeComp->Segments += 1;
														NewSegment = AttributeComp->Segments;
														AddSegmentsHPBar();
														//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
													}
												}
												else
												{
													if (MaxHealth >= 13000 && MaxHealth < 14000)
													{
														if (AttributeComp->Segments == 13)
														{
															//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("131313")));
														}
														else
														{
															AttributeComp->Segments += 1;
															NewSegment = AttributeComp->Segments;
															AddSegmentsHPBar();
															//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
														}
													}
													else
													{
														if (MaxHealth >= 14000 && MaxHealth < 15000)
														{
															if (AttributeComp->Segments == 14)
															{
																//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("141414")));
															}
															else
															{
																AttributeComp->Segments += 1;
																NewSegment = AttributeComp->Segments;
																AddSegmentsHPBar();
																//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
															}
														}
														else
														{
															if (MaxHealth >= 15000)
															{
																if (AttributeComp->Segments == 15)
																{
																	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("151515")));
																}
																else
																{
																	AttributeComp->Segments += 1;
																	NewSegment = AttributeComp->Segments;
																	AddSegmentsHPBar();
																	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("%f"), NewSegment));
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void AMain::AddSegmentsHPBar()
{
	if (IsValid(SegmentWidgetClass))
	{
		UUserWidget* SegmentWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), SegmentWidgetClass);

		if (SegmentWidgetInstance != nullptr)
		{
			UHorizontalBoxSlot* Slot = SegmentsHorizonBox->AddChildToHorizontalBox(SegmentWidgetInstance);
			Slot->SetSize(ESlateSizeRule::Fill);
		}
	}
}

// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();

	Widget = WidgetComp->GetUserWidgetObject();
	HPDamageProgressBar = Cast<UProgressBar>(Widget->GetWidgetFromName(FName("HPDamageProgressBar")));
	HPProgressBar = Cast<UProgressBar>(Widget->GetWidgetFromName(FName("HPProgressBar")));
	HPVar = Cast<UTextBlock>(Widget->GetWidgetFromName(FName("HPVar")));
	MaxHPVar = Cast<UTextBlock>(Widget->GetWidgetFromName(FName("MaxHPVar")));
	LevelProgressimg = Cast<UImage>(Widget->GetWidgetFromName(FName("LevelProgressimg")));
	SegmentsHorizonBox = Cast<UHorizontalBox>(Widget->GetWidgetFromName(FName("SegmentsHorizonBox")));

	if (IsValid(WidgetClass))
	{
		TESWIDGET = Cast<UTESWIDGET>(CreateWidget(GetWorld(), WidgetClass));

		if (TESWIDGET != nullptr)
		{
			TESWIDGET->AddToViewport();
		}
	}

	HPProgressBar->SetPercent(Health / MaxHealth);
	HPDamageProgressBar->SetPercent(Health / MaxHealth);

	GetWorldTimerManager().SetTimer(TimerSegments, this, &AMain::ProgressLevelEvery1Seconds, 0.4f, true);
}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsShowDamageHPBar)
	{
		HPDamageProgressBar->SetPercent(FMath::FInterpTo(HPDamageProgressBar->Percent, HPProgressBar->Percent, DeltaTime, 3.0f));
		if (HPDamageProgressBar->Percent == HPProgressBar->Percent)
		{
			bIsShowDamageHPBar = false;
			bIsShowRegenHPBar = false;
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("TICK DAMAGE END")));
		}
	}
	if (!bIsShowDamageHPBar)
	{
		if (bIsShowRegenHPBar)
		{
			HPProgressBar->SetPercent(FMath::FInterpTo(HPProgressBar->Percent, HPDamageProgressBar->Percent, DeltaTime, 3.0f));
			if (HPDamageProgressBar->Percent == HPProgressBar->Percent)
			{
				bIsShowDamageHPBar = false;
				bIsShowRegenHPBar = false;
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, FString::Printf(TEXT("TICK REGEN END")));
			}
		}
	}
}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("ZKey", IE_Pressed, this, &AMain::ZKey);
	PlayerInputComponent->BindAction("CKey", IE_Pressed, this, &AMain::CKey);
	PlayerInputComponent->BindAction("VKey", IE_Pressed, this, &AMain::VKey);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMain::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMain::LookUpAtRate);

	PlayerInputComponent->BindAction("ComboInput", IE_Pressed, this, &AMain::ComboInput);
}

void AMain::MoveForward(float val)
{
	if ((Controller != nullptr) && (val != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, val);
	}

	// Update movement input and stop animation montage if the player is moving
	bIsMoving = (val != 0.0f);
	if (bIsMoving)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			StopAllMontages();
		}
	}
}

void AMain::MoveRight(float val)
{
	if ((Controller != nullptr) && (val != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, val);
	}

	// Update movement input and stop animation montage if the player is moving
	bIsMoving = (val != 0.0f);
	if (bIsMoving)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			StopAllMontages();
		}
	}
}

void AMain::TurnAtRate(float rate)
{
	AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMain::LookUpAtRate(float rate)
{
	AddControllerPitchInput(rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMain::ComboInput()
{
	if (ComboMontages.IsValidIndex(CurrentComboIndex))
	{
		// Check if enough time has passed since the last combo input
		float CurrentTime = GetWorld()->GetTimeSeconds();
		if (CurrentTime - LastComboTime >= ComboCooldown)
		{
			// Play the combo montage
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if (AnimInstance && ComboMontages[CurrentComboIndex])
			{
				UAnimMontage* MontageToPlay = ComboMontages[CurrentComboIndex];
				AnimInstance->Montage_Play(MontageToPlay, PlayRate, EMontagePlayReturnType::MontageLength, 0.0f);
				ActiveMontages.Add(MontageToPlay);
				CurrentComboIndex++;

				LastComboTime = CurrentTime; // Update the last combo input time
			}
		}
	}
	else
	{
		// The combo index is out of range, so the combo is finished
		CurrentComboIndex = 0;
	}
}

void AMain::StopAllMontages()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		for (UAnimMontage* Montage : ActiveMontages)
		{
			AnimInstance->Montage_Stop(0.0f, Montage);
		}

		ActiveMontages.Empty();
	}
}

