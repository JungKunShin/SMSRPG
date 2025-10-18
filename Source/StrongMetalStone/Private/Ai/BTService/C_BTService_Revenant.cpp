// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTService/C_BTService_Revenant.h"
#include "AIController.h" 
#include "Character/C_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Windows.h>

#include "Character/C_RevenantBossCharacter.h"

UC_BTService_Revenant::UC_BTService_Revenant()
{

	// 서비스가 트리에 포함될 때 자동으로 실행되도록 설정
	bNotifyBecomeRelevant = true;
	// Tick 함수가 주기적으로 실행되도록 설정
	bNotifyTick = true;
	// Tick 주기 설정 (0.5초마다 실행)
	Interval = 0.5f;


}







void UC_BTService_Revenant::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return;

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn) return;

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (!BBComp) return;


	DetectTargetEvent(AIController, ControlledPawn, BBComp, DeltaSeconds);

	SelfHp(ControlledPawn , BBComp);

	QSkill(ControlledPawn, BBComp, DeltaSeconds);

	WSkill(ControlledPawn, BBComp, DeltaSeconds);

	ESkill(ControlledPawn, BBComp, DeltaSeconds);

	RSkill(ControlledPawn, BBComp, DeltaSeconds);

	DodgeSkill(ControlledPawn, BBComp, DeltaSeconds);

}


// 플레이어 블랙보드에 타겟 설정
void UC_BTService_Revenant::DetectTargetEvent(AAIController* AIController, APawn* ControlledPawn,  UBlackboardComponent* BBComp, float DeltaSeconds)
{

	if (!AIController || !ControlledPawn || !BBComp)
		return;

	AC_PlayerCharacter* CurrentTarget = Cast<AC_PlayerCharacter>(BBComp->GetValueAsObject(KeyTarget.SelectedKeyName));
	bool bIsValid = IsValidTarget(CurrentTarget);

	// 유효한 타겟일 경우 거리 계산 + 유지 시간 누적
	if (bIsValid)
	{
		float Distance = FVector::Dist(ControlledPawn->GetActorLocation(), CurrentTarget->GetActorLocation());
		BBComp->SetValueAsFloat(KeyDistanceToTarget.SelectedKeyName, Distance);

		TimeSinceTargetSet += DeltaSeconds;
	}

	// 타겟이 없거나 유지 시간이 초과된 경우 새 타겟 설정
	if (!bIsValid || TimeSinceTargetSet >= MaxTargetHoldTime)
	{
		// 주변 플레이어 탐지
		TArray<AC_PlayerCharacter*> Players = PerformPlayerDetection(ControlledPawn);

		// 현재 타겟은 제외	
		if (CurrentTarget)
		{
			Players.Remove(CurrentTarget);
		}

		// 도발 상태 확인
		bool bIsTaunt = BBComp->GetValueAsBool(KeyIsTaunt.SelectedKeyName);
		AC_PlayerCharacter* TauntCharacter = Cast<AC_PlayerCharacter>(BBComp->GetValueAsObject(KeyTauntCharacter.SelectedKeyName));

		AC_PlayerCharacter* NewTarget = nullptr;

		if (Players.Num() > 0)
		{
			if (bIsTaunt && TauntCharacter && TauntCharacter != CurrentTarget)
			{
				NewTarget = TauntCharacter;
			}
			else
			{
				NewTarget = SelectRandomTarget(Players);
			}
		}

		// 최종 타겟 지정
		if (NewTarget)
		{
			BBComp->SetValueAsObject(KeyTarget.SelectedKeyName, NewTarget);
		}
		else if (!bIsValid)
		{
			// 타겟이 유효하지 않았고, 대체할 타겟도 없다면 타겟을 null로 설정
			BBComp->SetValueAsObject(KeyTarget.SelectedKeyName, nullptr);
		}

		TimeSinceTargetSet = 0.0f;
	}

	

	//// 보스 주변 플레이어 감지 (1500.f 반경)
	//TArray<AC_PlayerCharacter*> Players = PerformPlayerDetection(ControlledPawn);

	//// 도발 상태 및 도발자 가져오기
	//bool bIsTaunt = BBComp->GetValueAsBool(KeyIsTaunt.SelectedKeyName);

	//AC_PlayerCharacter* TauntCharacter = Cast<AC_PlayerCharacter>(BBComp->GetValueAsObject(KeyTauntCharacter.SelectedKeyName));

	//// 현재 타겟이 유효한 경우 도발자가 존재하면 교체
	//if (IsValidTarget(CurrentTarget))
	//{
	//	if (bIsTaunt && TauntCharacter && TauntCharacter != CurrentTarget)
	//	{
	//		// 도발자가 유효하면 타겟 교체
	//		BBComp->SetValueAsObject(KeyTarget.SelectedKeyName, TauntCharacter);
	//	}
	//	// 도발이 아니면 타겟 유지
	//	return;
	//}

	// 현재 타겟이 없거나 무효한 경우 새 타겟 설정
	//AC_PlayerCharacter* NewTarget = nullptr;
	//if (Players.Num() > 0)
	//{
	//	if (bIsTaunt && TauntCharacter)
	//	{
	//		// 도발 상태이면 도발자를 타겟으로 설정
	//		NewTarget = TauntCharacter;
	//	}
	//	else
	//	{
	//		// 아니면 플레이어 중 랜덤하게 타겟 설정
	//		NewTarget = SelectRandomTarget(Players);
	//	}
	//}

	//// 최종적으로 블랙보드에 타겟 등록
	//if (NewTarget)
	//{
	//	BBComp->SetValueAsObject(KeyTarget.SelectedKeyName, NewTarget);
	//}
}

// 보스 체력/스텟 관리 
void UC_BTService_Revenant::SelfHp(APawn* ControlledPawn, UBlackboardComponent* BBComp)
{

	AC_RevenantBossCharacter* Revenant = Cast< AC_RevenantBossCharacter >(ControlledPawn);
	if (!Revenant) return;

	   
		
		if (Revenant->EnemyInfo.Curhp < 0.f)
		{
			Revenant->EnemyInfo.Curhp = 0.f; // 음수 체력 방지

		}



        float RevenantCurHp = Revenant->EnemyInfo.Curhp;
		float RevenantMaxHp = Revenant->EnemyInfo.Maxhp;

        BBComp->SetValueAsFloat(KeySelfHp.SelectedKeyName, RevenantCurHp);

	    // 피가 0이하일경우 bool isdead -> true
		bool bIsDead = RevenantCurHp <= 0.f;
		if(bIsDead)
		{ 
		BBComp->SetValueAsBool(KeyIsDead.SelectedKeyName, true);
        }
		// 페이즈 2 돌입 조건 (50% 이하)

		bool bIsPhase2 = (RevenantCurHp <= RevenantMaxHp * 0.5f);
		if (bIsPhase2)
		{

         BBComp->SetValueAsBool(KeyPhase1.SelectedKeyName, true);
		}
		

		// 그로기 게이지가 다찼으면 
		
		float CurGroggy = Revenant->EnemyInfo.CurGroggy;
		float MaxGroggy = Revenant->EnemyInfo.MaxGroggy;

		if (CurGroggy == MaxGroggy)
		{

			BBComp->SetValueAsBool(KeyHasGroogy.SelectedKeyName, true);

			CurGroggy = 0.0f;

		}







}


void UC_BTService_Revenant::QSkill(APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds)
{

	AC_RevenantBossCharacter* Revenant = Cast<AC_RevenantBossCharacter>(ControlledPawn);
	if (!Revenant) return;


	float CurHp = Revenant->EnemyInfo.Curhp;

	float CurMp = Revenant->EnemyInfo.CurMp;

	float QSkillCooldown = BBComp->GetValueAsFloat(KeyQSkillCooldown.SelectedKeyName);
    QSkillCooldown = FMath::Min(QSkillCooldown + DeltaSeconds, 999.0f);

	BBComp->SetValueAsFloat(KeyQSkillCooldown.SelectedKeyName, QSkillCooldown);

	
	// QSkillCooldown 몽타주 끝나면 초기화해줄것 
	bool CanUseQSkill = (CurHp > 1.0f) && (CurMp >= 40.0f) && (QSkillCooldown >= 10.0f);
	
	if (CanUseQSkill)
	{
		// Q스킬 사용 가능: 기본공격 끄기
		BBComp->SetValueAsBool(KeyOnQSkill.SelectedKeyName, true);
		//BBComp->SetValueAsBool(KeybCanAttack.SelectedKeyName, false);
	}




}

void UC_BTService_Revenant::WSkill(APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds)
{

	AC_RevenantBossCharacter* Revenant = Cast<AC_RevenantBossCharacter>(ControlledPawn);
	if (!Revenant) return;


	float CurHp = Revenant->EnemyInfo.Curhp;

	float CurMp = Revenant->EnemyInfo.CurMp;

	float WSkillCooldown = BBComp->GetValueAsFloat(KeyWSkillCooldown.SelectedKeyName);
	WSkillCooldown = FMath::Min(WSkillCooldown + DeltaSeconds, 999.0f);

	BBComp->SetValueAsFloat(KeyWSkillCooldown.SelectedKeyName, WSkillCooldown);


	// w SkillCooldown 몽타주 끝나면 초기화해줄것 
	bool CanUseWSkill = (CurHp > 1.0f) && (CurMp >= 60.0f) && (WSkillCooldown >= 20.0f);

	if (CanUseWSkill)
	{
		// w스킬 사용 가능: 기본공격 끄기
		BBComp->SetValueAsBool(KeyOnWSkill.SelectedKeyName, true);
		//BBComp->SetValueAsBool(KeybCanAttack.SelectedKeyName, false);
	}
	




}

void UC_BTService_Revenant::ESkill(APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds)
{




	AC_RevenantBossCharacter* Revenant = Cast<AC_RevenantBossCharacter>(ControlledPawn);
	if (!Revenant) return;


	float CurHp = Revenant->EnemyInfo.Curhp;

	float CurMp = Revenant->EnemyInfo.CurMp;

	float ESkillCooldown = BBComp->GetValueAsFloat(KeyESkillCooldown.SelectedKeyName);
	ESkillCooldown = FMath::Min(ESkillCooldown + DeltaSeconds, 999.0f);

	BBComp->SetValueAsFloat(KeyESkillCooldown.SelectedKeyName, ESkillCooldown);


	// e SkillCooldown 몽타주 끝나면 초기화해줄것 
	bool CanUseESkill = (CurHp > 1.0f) && (CurMp >= 80.0f) && (ESkillCooldown >= 30.0f);

	if (CanUseESkill)
	{
		// w스킬 사용 가능: 기본공격 끄기
		BBComp->SetValueAsBool(KeyOnESkill.SelectedKeyName, true);
		
	}
	

}

void UC_BTService_Revenant::RSkill(APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds)
{


	AC_RevenantBossCharacter* Revenant = Cast<AC_RevenantBossCharacter>(ControlledPawn);
	if (!Revenant) return;


	float CurHp = Revenant->EnemyInfo.Curhp;
	float MaxHp = Revenant->EnemyInfo.Maxhp;

	bool CanUseRSkill = false;
		
	// 체력이 70% 이하일 때, 아직 70% 스킬 안 썼다면
	if (CurHp <= MaxHp * 0.7f && !UsedRSkill70)
	{
		UsedRSkill70 = true;
		CanUseRSkill = true;
	}

	// 체력이 30% 이하일 때, 아직 30% 스킬 안 썼다면
	if (CurHp <= MaxHp * 0.3f && !UsedRSkill30)
	{
		UsedRSkill30 = true;
		CanUseRSkill = true;
	}

	if (CanUseRSkill)
	{
		BBComp->SetValueAsBool(KeyOnRSkill.SelectedKeyName, true);
	}

}

void UC_BTService_Revenant::DodgeSkill(APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds)
{


	AC_RevenantBossCharacter* Revenant = Cast<AC_RevenantBossCharacter>(ControlledPawn);
	if (!Revenant) return;

	float CurHp = Revenant->EnemyInfo.Curhp;
	float MaxHp = Revenant->EnemyInfo.Maxhp;

	float DodgeSkillCooldown = BBComp->GetValueAsFloat(KeyDodgeSkillCooldown.SelectedKeyName);
	DodgeSkillCooldown = FMath::Min(DodgeSkillCooldown + DeltaSeconds, 999.0f);

	BBComp->SetValueAsFloat(KeyDodgeSkillCooldown.SelectedKeyName, DodgeSkillCooldown);


	// e SkillCooldown 몽타주 끝나면 초기화해줄것 
	bool CanUseESkill = (CurHp > 1.0f) && (DodgeSkillCooldown >= 10.0f);

	if (CanUseESkill)
	{
		// w스킬 사용 가능: 기본공격 끄기
		BBComp->SetValueAsBool(KeyOnDodgeSkill.SelectedKeyName, true);

	}



}









// 타겟이 존재하고 살아있는 유효한 캐릭터인지 판단
bool UC_BTService_Revenant::IsValidTarget(AC_PlayerCharacter* Target)
{
	// 타겟이 존재하고 살아있는 유효한 캐릭터인지 판단
	AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(Target);
	return Target && IsValid(Target) && Character && Character->CharacterInfo.Curhp > 0.0f;

}


// 트레이서로 주변 순회해 플레이어 탐지
TArray<AC_PlayerCharacter*> UC_BTService_Revenant::PerformPlayerDetection(APawn* BossPawn)
{
	TArray<AC_PlayerCharacter*> DetectedPlayers;
	TArray<AActor*> TempActors;
	TArray<AActor*> Ignored;
	Ignored.Add(BossPawn); // 자기 자신은 감지 제외

	// 주변 1500.f 반경 안에 있는 캐릭터들을 감지
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9); // 커스텀 오브젝트 채널을 사용하는 중이라 9번째 커스텀채널로 설정

	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(), BossPawn->GetActorLocation(), 4000.f,
		ObjectTypes, ACharacter::StaticClass(), Ignored, TempActors); // SphereOverlapActorssms AActor로 사용되니깐 AActor 배열로 수행

	

	// 체력이 1 이상이고 살아있는 플레이어만 필터링
	for (AActor* Actor : TempActors)
	{
		AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(Actor);
		if (Character && Character->CharacterInfo.Curhp > 0.0f)
		{
			DetectedPlayers.Add(Character);
		}
	}

	return DetectedPlayers;
}


// 랜덤 타겟 설정
AC_PlayerCharacter* UC_BTService_Revenant::SelectRandomTarget(const TArray<AC_PlayerCharacter*>& Players)
{
	// 플레이어 배열이 비어있지 않다면 랜덤하게 하나 선택
	if (Players.Num() == 0) return nullptr;
	int32 Index = FMath::RandRange(0, Players.Num() - 1);
	return Players[Index];
}






