// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/Mage/C_MgSolarJudgementAN.h"
#include "Character/C_Mage.h"

void UC_MgSolarJudgementAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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
		FVector SpawnLocation = Mage->GetActorLocation() + FVector(0.0f, 0.0f, 700.0f);
		FRotator SpawnRotation = Mage->GetActorRotation() + FRotator(-35.0f, 0.0f, 0.0f);

		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = Mage;
		SpawnedProjectile = MeshComp->GetWorld()->SpawnActor<AC_MgSolarJudgetmentPr>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParam); // ���� ��ȯ
	}
}
