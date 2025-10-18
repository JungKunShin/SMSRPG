// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTService/C_BTService_Revenant.h"
#include "AIController.h" 
#include "Character/C_PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Windows.h>

#include "Character/C_RevenantBossCharacter.h"

UC_BTService_Revenant::UC_BTService_Revenant()
{

	// ���񽺰� Ʈ���� ���Ե� �� �ڵ����� ����ǵ��� ����
	bNotifyBecomeRelevant = true;
	// Tick �Լ��� �ֱ������� ����ǵ��� ����
	bNotifyTick = true;
	// Tick �ֱ� ���� (0.5�ʸ��� ����)
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


// �÷��̾� �����忡 Ÿ�� ����
void UC_BTService_Revenant::DetectTargetEvent(AAIController* AIController, APawn* ControlledPawn,  UBlackboardComponent* BBComp, float DeltaSeconds)
{

	if (!AIController || !ControlledPawn || !BBComp)
		return;

	AC_PlayerCharacter* CurrentTarget = Cast<AC_PlayerCharacter>(BBComp->GetValueAsObject(KeyTarget.SelectedKeyName));
	bool bIsValid = IsValidTarget(CurrentTarget);

	// ��ȿ�� Ÿ���� ��� �Ÿ� ��� + ���� �ð� ����
	if (bIsValid)
	{
		float Distance = FVector::Dist(ControlledPawn->GetActorLocation(), CurrentTarget->GetActorLocation());
		BBComp->SetValueAsFloat(KeyDistanceToTarget.SelectedKeyName, Distance);

		TimeSinceTargetSet += DeltaSeconds;
	}

	// Ÿ���� ���ų� ���� �ð��� �ʰ��� ��� �� Ÿ�� ����
	if (!bIsValid || TimeSinceTargetSet >= MaxTargetHoldTime)
	{
		// �ֺ� �÷��̾� Ž��
		TArray<AC_PlayerCharacter*> Players = PerformPlayerDetection(ControlledPawn);

		// ���� Ÿ���� ����	
		if (CurrentTarget)
		{
			Players.Remove(CurrentTarget);
		}

		// ���� ���� Ȯ��
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

		// ���� Ÿ�� ����
		if (NewTarget)
		{
			BBComp->SetValueAsObject(KeyTarget.SelectedKeyName, NewTarget);
		}
		else if (!bIsValid)
		{
			// Ÿ���� ��ȿ���� �ʾҰ�, ��ü�� Ÿ�ٵ� ���ٸ� Ÿ���� null�� ����
			BBComp->SetValueAsObject(KeyTarget.SelectedKeyName, nullptr);
		}

		TimeSinceTargetSet = 0.0f;
	}

	

	//// ���� �ֺ� �÷��̾� ���� (1500.f �ݰ�)
	//TArray<AC_PlayerCharacter*> Players = PerformPlayerDetection(ControlledPawn);

	//// ���� ���� �� ������ ��������
	//bool bIsTaunt = BBComp->GetValueAsBool(KeyIsTaunt.SelectedKeyName);

	//AC_PlayerCharacter* TauntCharacter = Cast<AC_PlayerCharacter>(BBComp->GetValueAsObject(KeyTauntCharacter.SelectedKeyName));

	//// ���� Ÿ���� ��ȿ�� ��� �����ڰ� �����ϸ� ��ü
	//if (IsValidTarget(CurrentTarget))
	//{
	//	if (bIsTaunt && TauntCharacter && TauntCharacter != CurrentTarget)
	//	{
	//		// �����ڰ� ��ȿ�ϸ� Ÿ�� ��ü
	//		BBComp->SetValueAsObject(KeyTarget.SelectedKeyName, TauntCharacter);
	//	}
	//	// ������ �ƴϸ� Ÿ�� ����
	//	return;
	//}

	// ���� Ÿ���� ���ų� ��ȿ�� ��� �� Ÿ�� ����
	//AC_PlayerCharacter* NewTarget = nullptr;
	//if (Players.Num() > 0)
	//{
	//	if (bIsTaunt && TauntCharacter)
	//	{
	//		// ���� �����̸� �����ڸ� Ÿ������ ����
	//		NewTarget = TauntCharacter;
	//	}
	//	else
	//	{
	//		// �ƴϸ� �÷��̾� �� �����ϰ� Ÿ�� ����
	//		NewTarget = SelectRandomTarget(Players);
	//	}
	//}

	//// ���������� �����忡 Ÿ�� ���
	//if (NewTarget)
	//{
	//	BBComp->SetValueAsObject(KeyTarget.SelectedKeyName, NewTarget);
	//}
}

// ���� ü��/���� ���� 
void UC_BTService_Revenant::SelfHp(APawn* ControlledPawn, UBlackboardComponent* BBComp)
{

	AC_RevenantBossCharacter* Revenant = Cast< AC_RevenantBossCharacter >(ControlledPawn);
	if (!Revenant) return;

	   
		
		if (Revenant->EnemyInfo.Curhp < 0.f)
		{
			Revenant->EnemyInfo.Curhp = 0.f; // ���� ü�� ����

		}



        float RevenantCurHp = Revenant->EnemyInfo.Curhp;
		float RevenantMaxHp = Revenant->EnemyInfo.Maxhp;

        BBComp->SetValueAsFloat(KeySelfHp.SelectedKeyName, RevenantCurHp);

	    // �ǰ� 0�����ϰ�� bool isdead -> true
		bool bIsDead = RevenantCurHp <= 0.f;
		if(bIsDead)
		{ 
		BBComp->SetValueAsBool(KeyIsDead.SelectedKeyName, true);
        }
		// ������ 2 ���� ���� (50% ����)

		bool bIsPhase2 = (RevenantCurHp <= RevenantMaxHp * 0.5f);
		if (bIsPhase2)
		{

         BBComp->SetValueAsBool(KeyPhase1.SelectedKeyName, true);
		}
		

		// �׷α� �������� ��á���� 
		
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

	
	// QSkillCooldown ��Ÿ�� ������ �ʱ�ȭ���ٰ� 
	bool CanUseQSkill = (CurHp > 1.0f) && (CurMp >= 40.0f) && (QSkillCooldown >= 10.0f);
	
	if (CanUseQSkill)
	{
		// Q��ų ��� ����: �⺻���� ����
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


	// w SkillCooldown ��Ÿ�� ������ �ʱ�ȭ���ٰ� 
	bool CanUseWSkill = (CurHp > 1.0f) && (CurMp >= 60.0f) && (WSkillCooldown >= 20.0f);

	if (CanUseWSkill)
	{
		// w��ų ��� ����: �⺻���� ����
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


	// e SkillCooldown ��Ÿ�� ������ �ʱ�ȭ���ٰ� 
	bool CanUseESkill = (CurHp > 1.0f) && (CurMp >= 80.0f) && (ESkillCooldown >= 30.0f);

	if (CanUseESkill)
	{
		// w��ų ��� ����: �⺻���� ����
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
		
	// ü���� 70% ������ ��, ���� 70% ��ų �� ��ٸ�
	if (CurHp <= MaxHp * 0.7f && !UsedRSkill70)
	{
		UsedRSkill70 = true;
		CanUseRSkill = true;
	}

	// ü���� 30% ������ ��, ���� 30% ��ų �� ��ٸ�
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


	// e SkillCooldown ��Ÿ�� ������ �ʱ�ȭ���ٰ� 
	bool CanUseESkill = (CurHp > 1.0f) && (DodgeSkillCooldown >= 10.0f);

	if (CanUseESkill)
	{
		// w��ų ��� ����: �⺻���� ����
		BBComp->SetValueAsBool(KeyOnDodgeSkill.SelectedKeyName, true);

	}



}









// Ÿ���� �����ϰ� ����ִ� ��ȿ�� ĳ�������� �Ǵ�
bool UC_BTService_Revenant::IsValidTarget(AC_PlayerCharacter* Target)
{
	// Ÿ���� �����ϰ� ����ִ� ��ȿ�� ĳ�������� �Ǵ�
	AC_PlayerCharacter* Character = Cast<AC_PlayerCharacter>(Target);
	return Target && IsValid(Target) && Character && Character->CharacterInfo.Curhp > 0.0f;

}


// Ʈ���̼��� �ֺ� ��ȸ�� �÷��̾� Ž��
TArray<AC_PlayerCharacter*> UC_BTService_Revenant::PerformPlayerDetection(APawn* BossPawn)
{
	TArray<AC_PlayerCharacter*> DetectedPlayers;
	TArray<AActor*> TempActors;
	TArray<AActor*> Ignored;
	Ignored.Add(BossPawn); // �ڱ� �ڽ��� ���� ����

	// �ֺ� 1500.f �ݰ� �ȿ� �ִ� ĳ���͵��� ����
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9); // Ŀ���� ������Ʈ ä���� ����ϴ� ���̶� 9��° Ŀ����ä�η� ����

	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(), BossPawn->GetActorLocation(), 4000.f,
		ObjectTypes, ACharacter::StaticClass(), Ignored, TempActors); // SphereOverlapActorssms AActor�� ���Ǵϱ� AActor �迭�� ����

	

	// ü���� 1 �̻��̰� ����ִ� �÷��̾ ���͸�
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


// ���� Ÿ�� ����
AC_PlayerCharacter* UC_BTService_Revenant::SelectRandomTarget(const TArray<AC_PlayerCharacter*>& Players)
{
	// �÷��̾� �迭�� ������� �ʴٸ� �����ϰ� �ϳ� ����
	if (Players.Num() == 0) return nullptr;
	int32 Index = FMath::RandRange(0, Players.Num() - 1);
	return Players[Index];
}






