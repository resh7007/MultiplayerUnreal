// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BlasterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API ABlasterPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDScore(float Score);
	void SetHUDDefeats(int32 Defeats);
	void SetHUDDefeatText();
	void HideHUDDefeatText();
	void SetHUDWeaponAmmo(int32 Ammo);
	void SetHUDCarriedAmmo(int32 Ammo);
	void SetHUDMatchCountdown(float CountdownTime);

	virtual void OnPossess(APawn* InPawn) override; 
	virtual void Tick(float DeltaTime) override;
protected:
 	virtual void BeginPlay() override;
	void SetHUDTime();
private:
	UPROPERTY()
	class ABlasterHUD* BlasterHUD;
	FTimerHandle InputTimeHandle;
	float MatchTime = 120.f;
	uint32 CountDownInt=0;
};
