// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/Warrior/C_WrKickAN.h"
#include "Character/C_Warrior.h"

void UC_WrKickAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp)return;


	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());//PlayerCharacter�� ����ȯ
	if (!Warrior)return;

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
	if (Warrior->HasAuthority()) // ���������� ��ȯ
	{
		FVector ForwardVector = Warrior->GetActorForwardVector(); // ���� �չ��� ����
		FVector SpawnLocation = Warrior->GetActorLocation() + ForwardVector * 150.0f; // ���� ��ġ���� 2���� ��
		FRotator SpawnRotation = Warrior->GetActorRotation(); // ���� ���� ����

		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = Warrior;
		SpawnedAttackParticle = MeshComp->GetWorld()->SpawnActor<AC_WrKickAP>(AttackParticleClass, SpawnLocation, SpawnRotation, SpawnParam); // ���� ��ȯ
	}
}
