// Fill out your copyright notice in the Description page of Project Settings.


#include "Casing.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "TimerManager.h"

ACasing::ACasing()
{ 
	PrimaryActorTick.bCanEverTick = false;
	CasingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CasingMesh"));
	SetRootComponent(CasingMesh);
	CasingMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	CasingMesh->SetSimulatePhysics(true);
	CasingMesh->SetEnableGravity(true);
	CasingMesh->SetNotifyRigidBodyCollision(true);
	ShellEjectionImpulse = 10.f;
	bCasingHitFloor = false;
}
 
void ACasing::BeginPlay()
{
	Super::BeginPlay();

	CasingMesh->OnComponentHit.AddDynamic(this, &ACasing::OnHit);
	FVector RandomVector = GetActorForwardVector();
	RandomVector.X  =	RandomVector.X * FMath::RandRange(1,6);
	RandomVector.Z  =	RandomVector.Z * FMath::RandRange(1,6);

	CasingMesh->AddImpulse(RandomVector*ShellEjectionImpulse);
}

void ACasing::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{  
	if(bCasingHitFloor) return;

	if(ShellSound)
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
	 
	GetWorldTimerManager().SetTimer(InputTimeHandle, this, &ACasing::DestroyCasing, 0.01f, false, 1.7f);
	bCasingHitFloor=true;
}
 
void ACasing::DestroyCasing()
{
	GetWorld()->GetTimerManager().ClearTimer(InputTimeHandle);
	Destroy();
}

