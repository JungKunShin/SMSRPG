// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_Toilet_BaseAttack_AN.h"
#include "Character/C_Minion_Toilet.h"
#include "Character/C_PlayerCharacter.h"

void UC_Toilet_BaseAttack_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{



	AC_Minion_Toilet* Toilet = Cast<AC_Minion_Toilet>(MeshComp->GetOwner());

	if (!Toilet)return;


	// �������� üũ 
	if (!Toilet->HasAuthority())
	{
		return;
	}


	// �ش� ��Ƽ������ ���ʰ� �ǰ� 1�̻����� üũ
	if (Toilet->EnemyInfo.Curhp <= 0.0f) return;



	// �ݿ��� ���� �÷��̾ �����ϰ� ������ ó���ϱ�

	FVector ToiletLocation = Toilet->GetMesh()->GetSocketLocation("hand_r");
	float Radius = 300.0f;

	// �÷��̾�
	TArray<AActor*> OverlappedActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);

	// �ڱ��ڽ�
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Toilet);

	// ������ ����
	bool bHit = UKismetSystemLibrary::SphereOverlapActors
	(
		Toilet->GetWorld(),
		ToiletLocation,                 // ���� ��ġ
		Radius,                      // ����
		ObjectTypes,                // ������ƮŸ��
		ACharacter::StaticClass(), // Actor Class Filter
		ActorsToIgnore,           // �����ҿ��͵�
		OverlappedActors         // �������� ���͵�
	);

	if (!bHit) return;

	DrawDebugSphere(Toilet->GetWorld(), ToiletLocation, Radius, 16, FColor::Red, false, 1.0f);

	for (AActor* Actor : OverlappedActors)
	{
		AC_PlayerCharacter* Player = Cast<AC_PlayerCharacter>(Actor);
		if (!Player) return;

		

			FHitResult HitResult;
			//                                 ������ ,������ ,�������� ,�׳���Ʈ���, �����̻�ȿ��,
			UC_DamageManager::ApplyPointDamage(Player, Toilet, Toilet->EnemyInfo.Damage, HitResult);


			Player->PlayCameraShake2(Toilet->CamShakeClass);
		
	}








}
