// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTService/C_BTService_Minion.h"
#include "Ai/C_MinionAiController.h"
#include "Character/C_Minion.h"
#include "Character/C_PlayerCharacter.h"
#include "Character/C_Minion_Hostile.h"


#include "BehaviorTree/BlackboardComponent.h"

UC_BTService_Minion::UC_BTService_Minion()
{


	// ���񽺰� Ʈ���� ���Ե� �� �ڵ����� ����ǵ��� ����
	bNotifyBecomeRelevant = true;
	// Tick �Լ��� �ֱ������� ����ǵ��� ����
	bNotifyTick = true;
	// Tick �ֱ� ���� (0.5�ʸ��� ����)
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

	// ���� Ÿ�� ��������
	AC_PlayerCharacter* CurrentTarget = Cast<AC_PlayerCharacter>(BBComp->GetValueAsObject(KeyTarget.SelectedKeyName));






	// ��Ŀ�� ���� �غ���
	//MinionAiController->SetFocus(CurrentTarget);






	// ����: ���� Ÿ���� ���� ��� �ٷ� ����
	if (!CurrentTarget)
	{
		BBComp->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, 0.0f);


	
		//  ���⼭ ���������� Ÿ�� üũ
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

	// ���� 1: ���� Ÿ���� �׾��°�?
	bool bTargetDead = !bTargetValid;

	// ���� 2: ���� �����ΰ�?
	bool bIsTaunt = BBComp->GetValueAsBool(KeyIsTaunt.SelectedKeyName);
	AC_PlayerCharacter* TauntCharacter = Cast<AC_PlayerCharacter>(BBComp->GetValueAsObject(KeyTauntCharacter.SelectedKeyName));

	// ���� 3: ���� ���� �ð� üũ
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

	// �Ǵ� �� Ÿ�� ����
	if (bIsTaunt && TauntCharacter)
	{
		BBComp->SetValueAsObject(KeyTarget.SelectedKeyName, TauntCharacter);
		BBComp->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, 0.0f); // ���� �� ���� ����
	}
	else if (bTargetDead || bPlayerRanAway)
	{
		BBComp->SetValueAsObject(KeyTarget.SelectedKeyName, nullptr);
		
		BBComp->SetValueAsFloat(KeyTimeSinceLastAttack.SelectedKeyName, 0.0f); // �ʱ�ȭ
	}

	// Ÿ�ٰ��� �Ÿ�
	float Distance = FVector::Dist(SelfActor->GetActorLocation(), CurrentTarget->GetActorLocation());
	BBComp->SetValueAsFloat(KeyDistanceToTarget.SelectedKeyName, Distance);




}

void UC_BTService_Minion::SkillCoolTimeEvent(AAIController* AIController, APawn* ControlledPawn, UBlackboardComponent* BBComp, float DeltaSeconds)
{


	// Ÿ�� ���� ���� üũ
	AActor* Target = Cast<AActor>(BBComp->GetValueAsObject(KeyTarget.SelectedKeyName));

	// Ÿ���� ������ ��Ÿ�� �ʱ�ȭ �Ǵ� ����
	if (!Target)
	{
		BBComp->SetValueAsFloat(KeySkillCoolTime.SelectedKeyName, 0.0f);
		BBComp->SetValueAsBool(KeyOnSkill.SelectedKeyName, false);


		BBComp->SetValueAsFloat(KeySkillCoolTime2.SelectedKeyName, 0.0f);
		BBComp->SetValueAsBool(KeyOnSkill2.SelectedKeyName, false);

		return;
	}


	
    // ��ų  ��Ÿ�� (10��)
	float CoolTime1 = BBComp->GetValueAsFloat(KeySkillCoolTime.SelectedKeyName);
	CoolTime1 += DeltaSeconds;
	BBComp->SetValueAsFloat(KeySkillCoolTime.SelectedKeyName, CoolTime1);
	BBComp->SetValueAsBool(KeyOnSkill.SelectedKeyName, CoolTime1 > 10.0f);

	// ��ų 2 ��Ÿ�� (15��)
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
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);  // ���ϴ� ������Ʈ Ÿ�� (��: Pawn)

	UKismetSystemLibrary::SphereOverlapActors
	(
		SelfActor->GetWorld(),
		SelfActor->GetActorLocation(),
		Radius,
		ObjectTypes,                                 // ���� ��ü��
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
