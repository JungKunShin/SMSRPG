// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/Mage/C_MgPlasmaDescentAN.h"
#include "Character/C_Mage.h"

void UC_MgPlasmaDescentAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp)return;


	AC_Mage* Mage = Cast<AC_Mage>(MeshComp->GetOwner());//PlayerCharacter�� ����ȯ
	if (!Mage)return;

	// ������ �ι� ���°� ���� �ڵ�
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	static TMap<TWeakObjectPtr<AActor>, float> LastNotifyTimes;
	const float CurrentTime = MeshComp->GetWorld()->GetTimeSeconds();

	constexpr float MinInterval = 0.05f; // ���� ������ �� �ߺ� ����
	if (LastNotifyTimes.Contains(Owner))
	{
		float LastTime = LastNotifyTimes[Owner];
		if (CurrentTime - LastTime < MinInterval)
		{
			// �ʹ� ª�� �ð� �� �� �� ������ ����
			return;
		}
	}

	LastNotifyTimes.Add(Owner, CurrentTime);
	//
	if (Mage->HasAuthority()) // ����������
	{
		FVector ForwardVector = Mage->GetActorForwardVector(); // ���� �չ��� ����
		FVector SpawnLocation = Mage->GetActorLocation() + ForwardVector * FORWARD_DISTANCE +FVector(0.0f,0.0f,DOWN_HEIGHT); // ���� ��ġ���� �չ������� 7����+���� �Ʒ� ����
		FRotator SpawnRotation = Mage->GetActorRotation(); // ���� ���� ����

		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = Mage;
		SpawnedAttackParticle = MeshComp->GetWorld()->SpawnActor<AC_MgPlasmaDescentAP>(AttackParticleClass, SpawnLocation, SpawnRotation, SpawnParam); // ���� ��ȯ
	}
}
