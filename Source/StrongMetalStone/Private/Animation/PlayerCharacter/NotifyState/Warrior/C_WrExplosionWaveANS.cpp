// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/Warrior/C_WrExplosionWaveANS.h"
#include "Character/C_Warrior.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_WrExplosionWaveANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp)return;
	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC)return;

	if (Warrior->HasAuthority()) // ���������� ��ȯ
	{
		FVector SpawnLocation = MeshComp->GetSocketLocation("FX_Sword_Top"); // ���� �� �� ��������
		FRotator SpawnRotation = MeshComp->GetSocketRotation("FX_Sword_Top");

		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = Warrior;
		SpawnedAttackParticle = MeshComp->GetWorld()->SpawnActor<AC_WrExplosionWaveAP>(AttackParticleClass, SpawnLocation, SpawnRotation, SpawnParam); // ���� ��ȯ

		FTimerDelegate TimerDel;
		TimerDel.BindUFunction(this, FName("SpawnDelayedActor"), MeshComp); // SpawnDelayedActor �Լ� ���ε�

		MeshComp->GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, TimerDel, 0.2f, false); // �� Ÿ�̸Ӻ��� �� �ð��� ���� ��ȯ
		MeshComp->GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle1, TimerDel, 0.4f, false);
		MeshComp->GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle2, TimerDel, 0.6f, false);
		MeshComp->GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle3, TimerDel, 0.8f, false);
	}
}

void UC_WrExplosionWaveANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp)return;
	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC)return;

	if (MeshComp->GetWorld())
	{
		MeshComp->GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle); // Ÿ�̸��ڵ� clear
		MeshComp->GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle1);
		MeshComp->GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle2);
		MeshComp->GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle3);
		Distance = 500.0f; //�Ÿ��� �ʱ�ȭ
		TotalScale = FVector(FIRST_SCALE, FIRST_SCALE, FIRST_SCALE); // �����ϰ� �ʱ�ȭ
	}
}

void UC_WrExplosionWaveANS::SpawnDelayedActor(USkeletalMeshComponent* MeshComp)
{
	if (!MeshComp || !MeshComp->GetOwner() || !AttackParticleClass)
	{
		return;
	}
	UWorld* World = MeshComp->GetWorld();

	if (!World)
	{
		return;
	}

	if (!MeshComp)return;
	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC)return;

	FVector ForwardVector = Warrior->GetActorForwardVector();
	FVector SpawnLocation = MeshComp->GetSocketLocation("FX_Sword_Top") + ForwardVector * Distance; // ���� �� �� ���� ��ġ�κ��� �չ������� Distanc���Ϳ���
	FRotator SpawnRotation = MeshComp->GetSocketRotation("FX_Sword_Top");
	Distance += 500.0f; // �Ÿ��� 5���� �߰�

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = Warrior;

	SpawnedAttackParticle = MeshComp->GetWorld()->SpawnActor<AC_WrExplosionWaveAP>(AttackParticleClass, SpawnLocation, SpawnRotation, SpawnParam); // ���� ��ȯ
	SpawnedAttackParticle->SetActorScale3D(TotalScale); // ������ �� ����
	TotalScale.X += ADD_SCALE; // ������ �� �߰�
	TotalScale.Y += ADD_SCALE;
	TotalScale.Z += ADD_SCALE;
}
