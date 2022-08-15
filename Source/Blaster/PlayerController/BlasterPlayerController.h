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

	virtual float GetServerTime();// Synced with server world clock
	virtual void ReceivedPlayer() override; // sync with server clock as soon as possible
protected:
 	virtual void BeginPlay() override;
	void SetHUDTime();

	/**
	 *  Sync time between client and server
	 */
	//Requests the current server time, passing in the client's time when the request was sent
	UFUNCTION(Server, Reliable)
	void ServerRequestServerTime(float TimeOfCLientRequest);

	// reports the current server time to the client in response to ServerRequestServerTime
	UFUNCTION(Server, Reliable)
	void ClientReportServerTime(float TimeOfCLientRequest, float TimeServerReceivedClientRequest);

	float ClientServerDelta = 0.f; // difference between client and server time
	UPROPERTY(EditAnywhere, Category = Time)
	float TimeSyncFrequency = 9.f;

	float TimeSyncRunningTime = 0.f;
	void CheckTimeSync(float DeltaTime);
private:
	UPROPERTY()
	class ABlasterHUD* BlasterHUD;
	FTimerHandle InputTimeHandle;
	float MatchTime = 120.f;
	uint32 CountDownInt=0;
};
