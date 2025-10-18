// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/Mage/C_MgNovaStepANS.h"
#include "Character/C_Mage.h"

void UC_MgNovaStepANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotlaDuration)
{
	if (!MeshComp)return;


	AC_Mage* Mage = Cast<AC_Mage>(MeshComp->GetOwner());
	if (!Mage)return;

	if (Mage->HasAuthority())
	{
		FVector ForwardVector = Mage->GetActorForwardVector(); // 마법사 앞방향 저장
		FVector SpawnLocation = Mage->GetActorLocation() + ForwardVector * 150.0f; // 마법사 위치에서 2미터 앞
		FRotator SpawnRotation = Mage->GetActorRotation(); // 마법사 각도 저장

		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("ProjectileSpawnFunc"), MeshComp);

		MeshComp->GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, TimerDel, 0.25f, false);
	}
}

void UC_MgNovaStepANS::ProjectileSpawnFunc(USkeletalMeshComponent* MeshComp)
{
	if (!MeshComp || !MeshComp->GetOwner() || !ProjectileClass)return;

	UWorld* World = MeshComp->GetWorld();
	if (!World)return;

	AC_Mage* Mage = Cast<AC_Mage>(MeshComp->GetOwner());
	if (!Mage)return;

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = Mage;

	for (int32 i = 1; i < 6; ++i)
	{
		float Angle = i * GAP_ANGLE +30;
		FVector RotatedDir = FRotationMatrix(FRotator(0.0f, Angle, 0.0f)).TransformVector(Mage->GetActorRightVector() * (-1.0f));
		FVector SpawnLocation = Mage->GetActorLocation() + RotatedDir * 180.0f + FVector(0.0f, 0.0f, 200.0f);
		FRotator SpawnRotation = RotatedDir.Rotation() + FRotator(-25.0f, 0.0f, 0.0f);


		SpawnedProjectile = MeshComp->GetWorld()->SpawnActor<AC_MgNovaStepPr>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParam);
	}

	FVector TempVector = FVector(0.0f, 0.0f, JUMP_HEIGHT) + Mage->GetActorForwardVector() * BACK_DISTANCE;

	Mage->LaunchCharacter(TempVector, true, true);

}
