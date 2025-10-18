// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/BTTask/C_BTTask_Base.h"
#include "Ai/C_SMSAIController.h"
#include "Character/C_PlayerCharacter.h"
#include "Character/C_Enemy.h"

#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UC_BTTask_Base::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	

	AActor* Owner = OwnerComp.GetOwner();
	if (!Owner) return EBTNodeResult::Failed;


	AC_SMSAIController* EnemyAiController = Cast<AC_SMSAIController>(Owner);
	if (!EnemyAiController) return EBTNodeResult::Failed;


	BBComp = EnemyAiController->GetBlackboardComponent();


	UObject* TargetObj = EnemyAiController->GetBlackboardComponent()->GetValueAsObject(KeyTarget.SelectedKeyName);
	if (!TargetObj ) return EBTNodeResult::Failed;


	Target = Cast<AC_PlayerCharacter>(TargetObj);
	if (!Target || Target->CharacterInfo.Curhp <= 0.0f ) return EBTNodeResult::Failed;



	UObject* SelfActorObj = EnemyAiController->GetBlackboardComponent()->GetValueAsObject(KeySelfActor.SelectedKeyName);
	if (!SelfActorObj) return EBTNodeResult::Failed;

	SelfActor = Cast<AC_Enemy>(SelfActorObj);
	if (!SelfActor || SelfActor->EnemyInfo.Curhp <= 0.0f) return EBTNodeResult::Failed;




	return ExecuteCustomTask(OwnerComp, NodeMemory);


}

EBTNodeResult::Type UC_BTTask_Base::ExecuteCustomTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Succeeded;
}
