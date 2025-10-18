// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/Mage/C_MgBaseAttackAN.h"
#include "Character/C_Mage.h"

void UC_MgBaseAttackAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp)return;


	AC_Mage* Mage = Cast<AC_Mage>(MeshComp->GetOwner());//PlayerCharacter�� ����ȯ
	if (!Mage)return;
	
	if (!Mage->SkillSytemComponent->CurSkill)return;

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
	if (Mage->HasAuthority())
	{
		FVector ForwardVector = Mage->GetActorForwardVector(); // ������ �չ��� ����
		FRotator SpawnRotation = Mage->GetActorRotation(); // ���� ���� ����
		FVector SpawnLocation= MeshComp->GetSocketLocation("FX_Hand_R4") + ForwardVector * SPAWNED_DISTANCE;
		if (Mage->SkillSytemComponent->CurSkill->SkillCombo == 2)
		{
			SpawnLocation = MeshComp->GetSocketLocation("FX_Hand_L4") + ForwardVector * SPAWNED_DISTANCE;
		}
		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = Mage;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		SpawnedProjectile = MeshComp->GetWorld()->SpawnActor<AC_MgBaseAttackPr>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParam); // ���� ��ȯ
	}
}
