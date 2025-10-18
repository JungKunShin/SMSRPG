// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTService/C_BTService_Minion.h"
#include "Ai/C_MinionAiController.h"
#include "Character/C_Minion.h"
#include "Character/C_PlayerCharacter.h"
#include "Character/C_Minion_Hostile.h"


#include "BehaviorTree/BlackboardComponent.h"

UC_BTService_Minion::UC_BTService_Minion()
{


	// 서비스가 트리에 포함될 때 자동으로 실행되도록 설정
	bNotifyBecomeRelevant = true;
	// Tick 함수가 주기적으로 실행되도록 설정
	bNotifyTick = true;
	// Tick 주기 설정 (0.5초마다 실행)
	Interval = 0.5f;



}

void UC_BTService_Minion::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return;

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn) return;

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (!BBComp) return;


	DetectTargetEvent(AIController, ControlledPawn, BBComp, DeltaSeconds);

	SkillCoolTimeEvent(AIController, ControlledPawn, BBComp, DeltaSeconds);

}

void UC_BTService_Minion::DetectTargetEvent(AAIController* AIController, APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds)
{

	if (!AIController || !ControlledPawn || !BBComp)
		return;

	AC_MinionAiController* MinionAiController = Cast<AC_MinionAiController>(AIController);
	AC_Minion* SelfActor = Cast<AC_Minion>(ControlledPawn);
	if (!MinionAiController || !SelfActor) return;

	// 현재 타겟 가져오기
	AC_PlayerCharacter* CurrentTarget = Cast<AC_PlayerCharacter>(BBComp->GetValueAsObject(KeyTarget.SelectedKeyName));






	// 포커스 설정 해보기
	//MinionAiController->SetFocus(CurrentTarget);






	// 예외: 현재 타겟이 없는 경우 바로 종료
	if (!CurrentTarget)
	{
		BBComp->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, 0.0f);


	
		//  여기서 선공몹인지 타입 체크
		if (SelfActor->IsA(AC_Minion_Hostile::StaticClass()))
		{
			AC_PlayerCharacter* FoundTarget = FindTargetByTrace(SelfActor);
			if (FoundTarget)
			{
				BBComp->SetValueAsObject(KeyTarget.SelectedKeyName, FoundTarget);
				BBComp->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, 0.0f);
			}
		}




		return;
	}

	bool bTargetValid = CurrentTarget->CharacterInfo.Curhp > 0;

	// 조건 1: 현재 타겟이 죽었는가?
	bool bTargetDead = !bTargetValid;

	// 조건 2: 도발 상태인가?
	bool bIsTaunt = BBComp->GetValueAsBool(KeyIsTaunt.SelectedKeyName);
	AC_PlayerCharacter* TauntCharacter = Cast<AC_PlayerCharacter>(BBComp->GetValueAsObject(KeyTauntCharacter.SelectedKeyName));

	// 조건 3: 공격 못한 시간 체크
	float TimeSinceLastAttack = BBComp->GetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName);
	if (bTargetValid)
	{
		TimeSinceLastAttack += DeltaSeconds;
		BBComp->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, TimeSinceLastAttack);
	}
	else
	{
		TimeSinceLastAttack = 0.0f;
		BBComp->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, 0.0f);
	}

	bool bPlayerRanAway = TimeSinceLastAttack > 15.0f;

	// 판단 및 타겟 설정
	if (bIsTaunt && TauntCharacter)
	{
		BBComp->SetValueAsObject(KeyTarget.SelectedKeyName, TauntCharacter);
		BBComp->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, 0.0f); // 도발 중 공격 간주
	}
	else if (bTargetDead || bPlayerRanAway)
	{
		BBComp->SetValueAsObject(KeyTarget.SelectedKeyName, nullptr);
		
		BBComp->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, 0.0f); // 초기화
	}

	// 타겟과의 거리
	float Distance = FVector::Dist(SelfActor->GetActorLocation(), CurrentTarget->GetActorLocation());
	BBComp->SetValueAsFloat(KeyDistanceToTarget.SelectedKeyName, Distance);




}

void UC_BTService_Minion::SkillCoolTimeEvent(AAIController* AIController, APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds)
{


	// 타겟 존재 여부 체크
	AActor* Target = Cast<AActor>(BBComp->GetValueAsObject(KeyTarget.SelectedKeyName));

	// 타겟이 없으면 쿨타임 초기화 또는 무시
	if (!Target)
	{
		BBComp->SetValueAsFloat(KeySkillCoolTime.SelectedKeyName, 0.0f);
		BBComp->SetValueAsBool(KeyOnSkill.SelectedKeyName, false);


		BBComp->SetValueAsFloat(KeySkillCoolTime2.SelectedKeyName, 0.0f);
		BBComp->SetValueAsBool(KeyOnSkill2.SelectedKeyName, false);

		return;
	}


	
    // 스킬  쿨타임 (10초)
	float CoolTime1 = BBComp->GetValueAsFloat(KeySkillCoolTime.SelectedKeyName);
	CoolTime1 += DeltaSeconds;
	BBComp->SetValueAsFloat(KeySkillCoolTime.SelectedKeyName, CoolTime1);
	BBComp->SetValueAsBool(KeyOnSkill.SelectedKeyName, CoolTime1 > 10.0f);

	// 스킬 2 쿨타임 (15초)
	float CoolTime2 = BBComp->GetValueAsFloat(KeySkillCoolTime2.SelectedKeyName);
	CoolTime2 += DeltaSeconds;
	BBComp->SetValueAsFloat(KeySkillCoolTime2.SelectedKeyName, CoolTime2);
	BBComp->SetValueAsBool(KeyOnSkill2.SelectedKeyName, CoolTime2 > 15.0f);
	

}

AC_PlayerCharacter* UC_BTService_Minion::FindTargetByTrace(AC_Minion* SelfActor)
{
	TArray<AActor*> OutActors;
	float Radius = 1000.f;


	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);  // 원하는 오브젝트 타입 (예: Pawn)

	UKismetSystemLibrary::SphereOverlapActors
	(
		SelfActor->GetWorld(),
		SelfActor->GetActorLocation(),
		Radius,
		ObjectTypes,                                 // 여기 대체됨
		AC_PlayerCharacter::StaticClass(),
		TArray<AActor*>(),
		OutActors
	);

	AC_PlayerCharacter* Nearest = nullptr;
	float MinDist = TNumericLimits<float>::Max();

	for (AActor* Actor : OutActors)
	{
		AC_PlayerCharacter* Candidate = Cast<AC_PlayerCharacter>(Actor);
		if (Candidate && Candidate->CharacterInfo.Curhp > 0)
		{
			float Distance = FVector::Dist(SelfActor->GetActorLocation(), Candidate->GetActorLocation());
			if (Distance < MinDist)
			{
				MinDist = Distance;
				Nearest = Candidate;
			}
		}
	}

	return Nearest;
}
