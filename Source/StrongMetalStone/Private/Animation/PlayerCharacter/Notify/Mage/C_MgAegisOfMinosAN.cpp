// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/Mage/C_MgAegisOfMinosAN.h"
#include "Character/C_Mage.h"

void UC_MgAegisOfMinosAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp)return;


	AC_Mage* Mage = Cast< AC_Mage>(MeshComp->GetOwner());
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
	if (Mage->HasAuthority()) // ���������� ��ȯ
	{
		FVector ForwardVector = Mage->GetActorForwardVector(); // ������ �չ��� ����
		FVector SpawnLocation = Mage->GetActorLocation() + ForwardVector * 200.0f; // ������ ��ġ���� 2���� ��
		FRotator SpawnRotation = Mage->GetActorRotation(); // ������ ���� ����

		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = Mage;
		SpawnedAttackParticle = MeshComp->GetWorld()->SpawnActor<AC_MgAegisOfMinosAP>(AttackParticleClass, SpawnLocation, SpawnRotation, SpawnParam); // ���� ��ȯ
	}
}
