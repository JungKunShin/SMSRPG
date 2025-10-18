// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_Horse_Skill1_AN.h"
#include "Character/C_UndeadHorse.h"
#include "Character/C_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void UC_Horse_Skill1_AN::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{



	AC_UndeadHorse* UndeadHorse = Cast<AC_UndeadHorse>(MeshComp->GetOwner());

	if (!UndeadHorse)return;


	// �������� üũ 
	if (!UndeadHorse->HasAuthority())
	{
		return;
	}


	// �ش� ��Ƽ������ ���ʰ� �ǰ� 1�̻����� üũ
	if (UndeadHorse->EnemyInfo.Curhp <= 0.0f) return;



	// �ݿ��� ���� �÷��̾ �����ϰ� ������ ó���ϱ�

	FVector ToiletLocation = UndeadHorse->GetMesh()->GetSocketLocation(SocketName);
	float Radius = 300.0f;

	// �÷��̾�
	TArray<AActor*> OverlappedActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);

	// �ڱ��ڽ�
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(UndeadHorse);

	// ������ ����
	bool bHit = UKismetSystemLibrary::SphereOverlapActors
	(
		UndeadHorse->GetWorld(),
		ToiletLocation,                 // ���� ��ġ
		Radius,                      // ����
		ObjectTypes,                // ������ƮŸ��
		ACharacter::StaticClass(), // Actor Class Filter
		ActorsToIgnore,           // �����ҿ��͵�
		OverlappedActors         // �������� ���͵�
	);

	if (!bHit) return;

	DrawDebugSphere(UndeadHorse->GetWorld(), ToiletLocation, Radius, 16, FColor::Red, false, 1.0f);

	for (AActor* Actor : OverlappedActors)
	{
		AC_PlayerCharacter* Player = Cast<AC_PlayerCharacter>(Actor);
		if (!Player) return;



		FHitResult HitResult;
		//                                 ������ ,������ ,�������� ,�׳���Ʈ���, �����̻�ȿ��,
		UC_DamageManager::ApplyPointDamage(Player, UndeadHorse, UndeadHorse->EnemyInfo.Damage, HitResult);



		// �߷� ��ȭ
		Player->GetCharacterMovement()->GravityScale = 0.4f;


		FVector ForwardDirection = -UndeadHorse->GetActorForwardVector();
		FVector LaunchVelocity = ForwardDirection * 1000.f + FVector(0, 0, 400.f); // ���ε� ��¦ ���

		Player->LaunchCharacter(LaunchVelocity, true, true);

		

		FTimerHandle GravityResetHandle;
		GetWorld()->GetTimerManager().SetTimer(GravityResetHandle, [=]()
			{
				Player->GetCharacterMovement()->GravityScale = 1.0f;
			}, 1.0f, false);  // 2�� �� �������


	}


}
