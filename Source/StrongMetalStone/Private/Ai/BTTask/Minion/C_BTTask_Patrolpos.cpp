// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/Minion/C_BTTask_Patrolpos.h"
#include "Character/C_Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Ai/C_MinionAiController.h"
#include "AIController.h"

#include "NavigationSystem.h"



//EBTNodeResult::Type UC_BTTask_Patrolpos::ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	/*if (!SelfActor || !BBComp)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("SetPatrolPos: SelfActor or BBComp is null"));
//		return EBTNodeResult::Failed;
//	}*/
//
//	// Ȩ ������ ����
//	FVector HomePos = SelfActor->GetActorLocation();
//	BBComp->SetValueAsVector(KeyHomepos.SelectedKeyName, HomePos);
//
//	//// ���� ���� ���� ���
//	//FVector PatrolPos;
//	//if (!FindRandomPatrolPos(PatrolPos))
//	//{
//	//	UE_LOG(LogTemp, Warning, TEXT("SetPatrolPos: Failed to find patrol pos"));
//	//	return EBTNodeResult::Failed;
//	//}
//
//	//// �����忡 ���� ��ġ ����
//	//BBComp->SetValueAsVector(KeyPatrolpos.SelectedKeyName, PatrolPos);
//	//
//	return EBTNodeResult::Succeeded;
//}
//
//bool UC_BTTask_Patrolpos::FindRandomPatrolPos(FVector& OutPatrolPos) const
//{
//	/*if (!SelfActor) return false;
//
//	UWorld* World = SelfActor->GetWorld();
//	if (!World) return false;
//
//	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
//	if (!NavSystem) return false;
//
//	const float Radius = 1000.f;
//	FNavLocation NavLocation;
//
//	bool bFound = NavSystem->GetRandomReachablePointInRadius(SelfActor->GetActorLocation(), Radius, NavLocation);
//	if (bFound)
//	{
//		OutPatrolPos = NavLocation.Location;
//	}*/
//	return; // bFound;
//}

UC_BTTask_Patrolpos::UC_BTTask_Patrolpos()
{
}

EBTNodeResult::Type UC_BTTask_Patrolpos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;

	APawn* ControlledPawn = AIController->GetPawn();
	if (!ControlledPawn) return EBTNodeResult::Failed;

	AC_Enemy* SelfActor1 = Cast<AC_Enemy>(ControlledPawn);
	if (!SelfActor1 || SelfActor1->EnemyInfo.Curhp <= 0.0f) return EBTNodeResult::Failed;

	UBlackboardComponent* BBComp1 = OwnerComp.GetBlackboardComponent();
	if (!BBComp1 || KeyHomepos.SelectedKeyName.IsNone() || KeyPatrolpos.SelectedKeyName.IsNone())
	{
		
		return EBTNodeResult::Failed;
	}

	// Ȩ ��ġ ����
	FVector HomePos = SelfActor1->GetActorLocation();
	BBComp1->SetValueAsVector(KeyHomepos.SelectedKeyName, HomePos);

	// �׺���̼� �ý��ۿ��� ���� ��ġ ã��
	UWorld* World = SelfActor1->GetWorld();
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
	if (!NavSystem) return EBTNodeResult::Failed;

	const float Radius = 1000.f;
	FNavLocation OutLocation;

	if (!NavSystem->GetRandomReachablePointInRadius(HomePos, Radius, OutLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("NavSystem Ž�� ����"));
		return EBTNodeResult::Failed;
	}

	BBComp1->SetValueAsVector(KeyPatrolpos.SelectedKeyName, OutLocation.Location);

	return EBTNodeResult::Succeeded;
}
