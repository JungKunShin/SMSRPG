// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/Notify/Warrior/C_WrSlashAN.h"
#include "Character/C_Warrior.h"

void UC_WrSlashAN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    Super::Notify(MeshComp, Animation);
    if (!MeshComp)return;

    AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());//PlayerCharacter로 형변환
    if (!Warrior)return;

   //임시로 주석처리 한것
    if (!Warrior->SkillSytemComponent->CurSkill) return;
    Warrior->SkillSytemComponent->CurSkill->SkillCombo += 1; // 스킬 콤보 1증가

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
    if (Warrior->HasAuthority())
    {
        //FName SocketName = TEXT("FX_Sword_Top"); // 소환하고자하는 위치(전사 검 끝 소켓)이름 저장
        //FVector SpawnLocation = MeshComp->GetSocketLocation(SocketName); // 소환 위치 저장
        //FRotator SpawnRotation = MeshComp->GetSocketRotation(SocketName); // 소환 각도 저장
        FVector ForwardVector = Warrior->GetActorForwardVector(); // 전사 앞방향 저장
        FVector SpawnLocation = Warrior->GetActorLocation() + ForwardVector * 150.0f; // 전사 위치에서 1미터 앞
        FRotator SpawnRotation = Warrior->GetActorRotation(); // 전사 각도 저장

        FActorSpawnParameters SpawnParam;
        SpawnParam.Owner = Warrior;
        SpawnedAttackParticle = MeshComp->GetWorld()->SpawnActor<AC_WrSlashAP>(AttackParticleClass, SpawnLocation, SpawnRotation, SpawnParam); // 액터 소환
    }
}