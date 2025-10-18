// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_Undead_Attack_AN.h"
#include "Character/C_Undead.h"
#include "Character/C_PlayerCharacter.h"

void UC_Undead_Attack_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{





	AC_Undead* Undead = Cast<AC_Undead>(MeshComp->GetOwner());

	if (!Undead)return;


	// �������� üũ 
	if (!Undead->HasAuthority())
	{
		return;
	}


	// �ش� ��Ƽ������ ���ʰ� �ǰ� 1�̻����� üũ
	if (Undead->EnemyInfo.Curhp <= 0.0f) return;



	// �ݿ��� ���� �÷��̾ �����ϰ� ������ ó���ϱ�

	FVector ToiletLocation = Undead->GetMesh()->GetSocketLocation(SocketName);
	float Radius = 200.0f;

	// �÷��̾�
	TArray<AActor*> OverlappedActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);

	// �ڱ��ڽ�
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Undead);

	// ������ ����
	bool bHit = UKismetSystemLibrary::SphereOverlapActors
	(
		Undead->GetWorld(),
		ToiletLocation,                 // ���� ��ġ
		Radius,                      // ����
		ObjectTypes,                // ������ƮŸ��
		ACharacter::StaticClass(), // Actor Class Filter
		ActorsToIgnore,           // �����ҿ��͵�
		OverlappedActors         // �������� ���͵�
	);

	if (!bHit) return;

	DrawDebugSphere(Undead->GetWorld(), ToiletLocation, Radius, 16, FColor::Red, false, 1.0f);

	for (AActor* Actor : OverlappedActors)
	{
		AC_PlayerCharacter* Player = Cast<AC_PlayerCharacter>(Actor);
		if (!Player) return;



		FHitResult HitResult;
		//                                 ������ ,������ ,�������� ,�׳���Ʈ���, �����̻�ȿ��,
		UC_DamageManager::ApplyPointDamage(Player, Undead, Undead->EnemyInfo.Damage, HitResult);


		Player->PlayCameraShake2(Undead->CamShakeClass);

	}



}
