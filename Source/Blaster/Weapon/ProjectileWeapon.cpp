// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Projectile.h"
void AProjectileWeapon:: Fire(const FVector& HitTarget) 
{
    Super::Fire(HitTarget);
    APawn* InstigatorPawn = Cast<APawn>(GetOwner());
    const USkeletalMeshSocket* MuzzleFLashSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));
    if(MuzzleFLashSocket)
    {
        FTransform SocketTransform = MuzzleFLashSocket->GetSocketTransform(GetWeaponMesh());
        // From muzzleFlashSocket to Hit location from TraceUnderCrosshairs
        FVector ToTarget = HitTarget - SocketTransform.GetLocation();
        FRotator TargetRotation = ToTarget.Rotation();
        if(ProjectileClass && InstigatorPawn)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = GetOwner();
            SpawnParams.Instigator = InstigatorPawn;
            UWorld* World = GetWorld();
            if(World)
            {
                World->SpawnActor<AProjectile>(
                    ProjectileClass,
                    SocketTransform.GetLocation(),
                    TargetRotation,
                    SpawnParams
                );
            }
        }
    }
}