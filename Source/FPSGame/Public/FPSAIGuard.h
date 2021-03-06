// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)

enum class EAIState :uint8 {
		Idle,Suspicious,Alerted
};
UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnSeePawn(APawn* Pawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	FRotator OriginalRotation;
	FTimerHandle TimerHandle_ResetOrientation;
	void ResetOrientation();

	UPROPERTY(ReplicatedUsing = OnRep_GuardState)
	EAIState GuardState;

	void SetGuardState(EAIState NewState);

	UFUNCTION()
	void OnRep_GuardState();

	UFUNCTION(BlueprintImplementableEvent,Category = "AI")
	void OnStateChanged(EAIState NewState);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
