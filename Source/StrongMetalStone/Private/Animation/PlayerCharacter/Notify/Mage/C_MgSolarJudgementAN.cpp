// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/Mage/C_MgSolarJudgementAN.h"
#include "Character/C_Mage.h"

void UC_MgSolarJudgementAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (!MeshComp)return;


	AC_Mage* Mage = Cast< AC_Mage>(MeshComp->GetOwner());
	if (!Mage)return;

	// 데미지 두번 들어가는것 방지 코드
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	static TMap<TWeakObjectPtr<AActor>, float> LastNotifyTimes;
	const float CurrentTime = MeshComp->GetWorld()->GetTimeSeconds();

	constexpr float MinInterval = 0.05f; // 같은 프레임 내 중복 방지
	if (LastNotifyTimes.Contains(Owner))
	{
		float LastTime = LastNotifyTimes[Owner];
		if (CurrentTime - LastTime < MinInterval)
		{
			// 너무 짧은 시간 내 두 번 들어오면 무시
			return;
		}
	}

	LastNotifyTimes.Add(Owner, CurrentTime);
	//
	if (Mage->HasAuthority()) // 서버에서만 소환
	{
		FVector SpawnLocation = Mage->GetActorLocation() + FVector(0.0f, 0.0f, 700.0f);
		FRotator SpawnRotation = Mage->GetActorRotation() + FRotator(-35.0f, 0.0f, 0.0f);

		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = Mage;
		SpawnedProjectile = MeshComp->GetWorld()->SpawnActor<AC_MgSolarJudgetmentPr>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParam); // 액터 소환
	}
}
