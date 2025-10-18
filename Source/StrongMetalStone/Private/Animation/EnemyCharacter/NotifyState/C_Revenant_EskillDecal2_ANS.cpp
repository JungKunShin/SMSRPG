// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_Revenant_EskillDecal2_ANS.h"
#include "Character/C_RevenantBossCharacter.h"
#include "Character/Skill/BossRevenant/BluePrint/C_BPRevenantEskillDecal.h"
#include "Character/Skill/BossRevenant/BluePrint/C_Revenant_SceneComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Actor.h"
#include "Character/C_PlayerCharacter.h"



void UC_Revenant_EskillDecal2_ANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{

	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (!MeshComp)return;


	AC_RevenantBossCharacter* Boss = Cast<AC_RevenantBossCharacter>(MeshComp->GetOwner());

	if (!Boss)return;


	// �������� üũ 
	if (!Boss->HasAuthority())
	{
		return;
	}


	// �ش� ��Ƽ������ ���ʰ� �ǰ� 1�̻����� üũ
	if (Boss->EnemyInfo.Curhp <= 0.0f) return;


	
	
	// ���忡 �ִ� �߾��� ��Ÿ���� �����͸� ã�Ƽ� ��ġ���� ��������
	FVector WorldLoc = FVector::ZeroVector;
	FRotator WorldRot = FRotator::ZeroRotator;


	AC_Revenant_SceneComponent* FoundActor = Cast<AC_Revenant_SceneComponent>(UGameplayStatics::GetActorOfClass(MeshComp->GetWorld(), AC_Revenant_SceneComponent::StaticClass()));


	if (FoundActor)
	{
		AC_Revenant_SceneComponent* CenterActor = Cast<AC_Revenant_SceneComponent>(FoundActor);
		if (CenterActor && CenterActor->WorldCenterPoint)
		{
			WorldLoc = CenterActor->WorldCenterPoint->GetComponentLocation();
			WorldRot = CenterActor->WorldCenterPoint->GetComponentRotation();
		}
	}

	// ������ �� ��ġ�� �̵���Ű�� 
	FVector TargetWorldLoc = FVector(WorldLoc.X, WorldLoc.Y, Boss->GetActorLocation().Z);

	FRotator TargetWorldRot = FRotator::ZeroRotator;



	TargetWorldRot = FRotator(WorldRot.Pitch, WorldRot.Yaw + 180, WorldRot.Roll);

	

	if (TargetWorldLoc.IsZero()) return;
	Boss->SetActorLocation(TargetWorldLoc);
	Boss->SetActorRotation(TargetWorldRot);



	// �� ��ġ���� ��Į ����
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Boss;
	SpawnParams.Instigator = Boss->GetInstigator();


	FVector SpawnLocation = WorldLoc;
	FRotator SpawnRotation = FRotator::ZeroRotator;
	
	SpawnRotation = FRotator(WorldRot.Pitch, WorldRot.Yaw, WorldRot.Roll);

	

	if (!Revenant_BPEskillDecal) return;
	SpawnedDecalActor = MeshComp->GetWorld()->SpawnActor<AActor>(Revenant_BPEskillDecal, SpawnLocation, SpawnRotation, SpawnParams);


	AC_BPRevenantEskillDecal* DecalActor = Cast<AC_BPRevenantEskillDecal>(SpawnedDecalActor);
	if (DecalActor && DecalActor->AttackDecal && DecalActor->WarningDecal)
	{
		// ����/��ǥ ������ ����
		StartScale = FVector(550.f, 550.f, 550.f); // ó���� �۰� ����
		TargetScale = FVector(4000.f, 4000.f, 4000.f); // ���������� WarningDecal�� �ð������� ����
		AccumulatedTime = 0.f;
		Duration = TotalDuration > 0.f ? TotalDuration : 3.f;

		// �ʱ�ȭ
		DecalActor->AttackDecal->SetWorldScale3D(StartScale);
		DecalActor->WarningDecal->SetWorldScale3D(TargetScale);
	}


}

void UC_Revenant_EskillDecal2_ANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{

	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (!SpawnedDecalActor) return;
	AC_BPRevenantEskillDecal* DecalActor = Cast<AC_BPRevenantEskillDecal>(SpawnedDecalActor);
	if (!DecalActor || !DecalActor->AttackDecal) return;

	// ��Į�� ƽ ���̸�ŭ �ø���
	AccumulatedTime += FrameDeltaTime;

	float Alpha = FMath::Clamp(AccumulatedTime / Duration, 0.f, 3.f);

	FVector NewScale = FMath::Lerp(StartScale, TargetScale, Alpha);

	DecalActor->AttackDecal->SetWorldScale3D(NewScale);
	//UE_LOG(LogTemp, Warning, TEXT("Alpha: %.2f | NewScale: %s"), Alpha, *NewScale.ToString());


}

void UC_Revenant_EskillDecal2_ANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{


	Super::NotifyEnd(MeshComp, Animation);
	if (!MeshComp)return;


	AC_RevenantBossCharacter* Boss = Cast<AC_RevenantBossCharacter>(MeshComp->GetOwner());

	if (!Boss)return;


	// �������� üũ 
	if (!Boss->HasAuthority())
	{
		return;
	}


	// �ش� ��Ƽ������ ���ʰ� �ǰ� 1�̻����� üũ
	if (Boss->EnemyInfo.Curhp <= 0.0f) return;


	// ��Į ���� 
	if (IsValid(SpawnedDecalActor))
	{
		SpawnedDecalActor->Destroy();
		SpawnedDecalActor = nullptr;
	}

	AccumulatedTime = 0.f;


	// �ݿ��� ���� �÷��̾ �����ϰ� ������ ó���ϱ�

	FVector BossLocation = Boss->GetActorLocation();
	float Radius = 5000.0f;

	TArray<AActor*> OverlappedActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Boss);

	// ������ ����
	bool bHit = UKismetSystemLibrary::SphereOverlapActors
	(
		Boss->GetWorld(),
		BossLocation,                 // ���� ��ġ
		Radius,                      // ����
		ObjectTypes,                // ������ƮŸ��
		ACharacter::StaticClass(), // Actor Class Filter
		ActorsToIgnore,           // �����ҿ��͵�
		OverlappedActors         // �������� ���͵�
	);

	if (!bHit) return;

	// ���� ��
	FVector BossForward = Boss->GetActorForwardVector();

	for (AActor* Actor : OverlappedActors)
	{
		AC_PlayerCharacter* Player = Cast<AC_PlayerCharacter>(Actor);
		if (!Player) continue;

		FVector ToTarget = (Player->GetActorLocation() - BossLocation).GetSafeNormal();
		float Dot = FVector::DotProduct(BossForward, ToTarget);
		float Degrees = FMath::RadiansToDegrees(FMath::Acos(Dot));

		if (Degrees <= 90.0f)
		{
			// �ݿ� �ȿ� �ִ� �÷��̾��Դϴ�.
			GEngine->AddOnScreenDebugMessage
			(
				-1,                        // Ű�� (-1�� �ڵ� �Ҵ�)
				5.0f,                      // ȭ�鿡 ǥ�õ� �ð� (��)
				FColor::Green,            // �۾� ����
				FString::Printf(TEXT("Player :%s"), *Player->GetName())
			);




			FHitResult HitResult;
			//                                 ������ ,������ ,�������� ,�׳���Ʈ���, �����̻�ȿ��,
			UC_DamageManager::ApplyPointDamage(Player, Boss, Boss->EnemyInfo.Damage, HitResult);


			GEngine->AddOnScreenDebugMessage
			(
				-1,                        // Ű�� (-1�� �ڵ� �Ҵ�)
				5.0f,                      // ȭ�鿡 ǥ�õ� �ð� (��)
				FColor::Red,            // �۾� ����
				FString::Printf(TEXT("PlayerHP : %.1f"), Player->CharacterInfo.Curhp)
			);


		}
	}

}
