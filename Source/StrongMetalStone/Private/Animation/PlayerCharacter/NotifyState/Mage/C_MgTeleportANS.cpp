// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/Mage/C_MgTeleportANS.h"
#include "Character/C_Mage.h"
#include "GameFramework/SpringArmComponent.h"

void UC_MgTeleportANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp)return;

	AC_Mage* Mage = Cast<AC_Mage>(MeshComp->GetOwner());
	if (!Mage)return;

	FVector Start = Mage->GetActorLocation() + FVector(0.0f, 0.0f, TRACE_HEIGHT);
	FVector End = Start + (Mage->GetActorForwardVector() * TELEPORT_DISTANCE) + FVector(0.0f, 0.0f, TRACE_HEIGHT);
	FVector HitBack = Mage->GetActorForwardVector() * (-BACK_DISTANCE) + FVector(0.0f, 0.0f, TRACE_HEIGHT);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.bTraceComplex = true;
	Params.AddIgnoredActor(MeshComp->GetOwner());

	bool bHit = Mage->GetWorld()->LineTraceSingleByProfile(HitResult, Start, End, FName("BlockAll"), Params);

	Mage->Absolute = true;
	OriginCameraDistance = Mage->CameraBoom->TargetArmLength;

	if (!bHit)
	{
		if (Mage->IsLocallyControlled())
		{
			CameraDistance = TELEPORT_DISTANCE;
			Mage->CameraBoom->TargetArmLength+= CameraDistance;
		}
		Mage->SetActorLocation(End);
	}
	else if (bHit)
	{
		if (Mage->IsLocallyControlled())
		{
			CameraDistance = FVector::Dist(Mage->GetActorLocation(), HitResult.Location);
			Mage->CameraBoom->TargetArmLength += CameraDistance;
		}
		FVector HitLocation = HitResult.Location + HitBack;
		Mage->SetActorLocation(HitLocation);
	}
}

void UC_MgTeleportANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (!MeshComp) return;

	AC_Mage* Mage = Cast<AC_Mage>(MeshComp->GetOwner());
	if (!Mage)return;

	/*Mage->CameraBoom->TargetArmLength = FMath::FInterpTo(Mage->CameraBoom->TargetArmLength, OriginCameraDistance, FrameDeltaTime,3.0f);*/
	Mage->CameraBoom->TargetArmLength = FMath::FInterpTo(Mage->CameraBoom->TargetArmLength, OriginCameraDistance,FrameDeltaTime,8.f);
}

void UC_MgTeleportANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	AC_Mage* Mage = Cast<AC_Mage>(MeshComp->GetOwner());
	if (!Mage)return;

	Mage->Absolute = false;

	if (Mage->IsLocallyControlled())
	{
		Mage->CameraBoom->TargetArmLength = OriginCameraDistance;
	}

	if (Mage)
	{
		Mage->ServerStopMontage();
	}
}
