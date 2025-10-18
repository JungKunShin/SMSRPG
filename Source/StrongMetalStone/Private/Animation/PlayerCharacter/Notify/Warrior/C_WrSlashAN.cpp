// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/Warrior/C_WrSlashAN.h"
#include "Character/C_Warrior.h"

void UC_WrSlashAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);
    if (!MeshComp)return;

    AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());//PlayerCharacter�� ����ȯ
    if (!Warrior)return;

   //�ӽ÷� �ּ�ó�� �Ѱ�
    if (!Warrior->SkillSytemComponent->CurSkill) return;
    Warrior->SkillSytemComponent->CurSkill->SkillCombo += 1; // ��ų �޺� 1����

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
    if (Warrior->HasAuthority())
    {
        //FName SocketName = TEXT("FX_Sword_Top"); // ��ȯ�ϰ����ϴ� ��ġ(���� �� �� ����)�̸� ����
        //FVector SpawnLocation = MeshComp->GetSocketLocation(SocketName); // ��ȯ ��ġ ����
        //FRotator SpawnRotation = MeshComp->GetSocketRotation(SocketName); // ��ȯ ���� ����
        FVector ForwardVector = Warrior->GetActorForwardVector(); // ���� �չ��� ����
        FVector SpawnLocation = Warrior->GetActorLocation() + ForwardVector * 150.0f; // ���� ��ġ���� 1���� ��
        FRotator SpawnRotation = Warrior->GetActorRotation(); // ���� ���� ����

        FActorSpawnParameters SpawnParam;
        SpawnParam.Owner = Warrior;
        SpawnedAttackParticle = MeshComp->GetWorld()->SpawnActor<AC_WrSlashAP>(AttackParticleClass, SpawnLocation, SpawnRotation, SpawnParam); // ���� ��ȯ
    }
}