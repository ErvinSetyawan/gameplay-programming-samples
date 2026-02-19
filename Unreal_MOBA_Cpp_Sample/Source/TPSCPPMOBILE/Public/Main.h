// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Components/TimelineComponent.h>
#include "Main.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TPSCPPMOBILE_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComp;

	UPROPERTY(visibleanywhere, BlueprintReadWrite)
	class UWidgetComponent* WidgetComp;

	UPROPERTY(VisibleAnywhere)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere)
	bool bIsMoving;

	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	class UTimelineComponent* MyTimeline;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	class UCurveFloat* CurveFloat;

	FOnTimelineFloat InterpFunction;
	FOnTimelineEvent TimelineFinishedCallback;

	UFUNCTION(BlueprintCallable)
	void TimelineFloatReturn(float Value);

	UFUNCTION(BlueprintCallable)
	void TimelineFinishedCallbackFunc();

	UFUNCTION(BlueprintCallable)
	void PlayTimeline();

	UFUNCTION(BlueprintCallable)
	void PlayReverseTimeline();

	UFUNCTION()
	void EventDamagedHP(float val);
	
	UFUNCTION()
	void EventRegenHP(float val);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Stats)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float RegenHealth;
	
	UFUNCTION()
	void HPDamageProgressBarShow();

	UFUNCTION()
	void HPRegenProgressBarShow();

	UPROPERTY(EditAnywhere, Category = "Show HP Bar")
	bool bIsShowDamageHPBar;

	UPROPERTY(EditAnywhere, Category = "Show HP Bar")
	bool bIsShowRegenHPBar;

	FTimerHandle TimerSegments;

	void ZKey();
	void CKey();
	void VKey();

    UFUNCTION(BlueprintCallable, Category = "ProgessLevel")
    void ProgressLevelEvery1Seconds();

	UFUNCTION(BlueprintCallable, Category = "Segments HP")
	void AddSegmentsHPBar();

	bool bIsMaxHealthUp = false;

	float NewHPVar;
	float NewAddHPVar;
	float NewDamageHPVar;
	float NewHPDivideVar;
	float NewLevel;
	float NewSegment;

	class UUserWidget* Widget;
	class UProgressBar* HPDamageProgressBar;
	class UProgressBar* HPProgressBar;
	class UTextBlock* HPVar;
	class UTextBlock* MaxHPVar;
	class UImage* LevelProgressimg;
	class UHorizontalBox* SegmentsHorizonBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Classtype)
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(EditAnywhere, Category = Classtype)
	TSubclassOf<UUserWidget> SegmentWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = Ates)
	class UTESWIDGET* TESWIDGET;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	class UMainActorComponent* AttributeComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float val);
	void MoveRight(float val);

	void TurnAtRate(float rate);
	void LookUpAtRate(float rate);

	// Attack

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
    float ComboCooldown;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
    float PlayRate;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
    TArray<UAnimMontage*> ComboMontages;

    UFUNCTION(BlueprintCallable, Category = "Attack")
    void ComboInput();

	UFUNCTION(BlueprintCallable, Category = "Attack")
    void StopAllMontages();

	//FORCEINLINE class USpringArmComponent* GetSpringArmCamera() const { return SpringArmComp; }
	//FORCEINLINE class UCameraComponent* GetCameraComp() const { return CameraComp; }

	// Mobile



private:

	// Combo attack
	int32 CurrentComboIndex;
	TArray<UAnimMontage*> ActiveMontages;
	float LastComboTime;

	// Input mobile

};
