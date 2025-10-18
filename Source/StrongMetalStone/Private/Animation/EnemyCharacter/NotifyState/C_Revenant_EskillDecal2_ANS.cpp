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


	// 서버인지 체크 
	if (!Boss->HasAuthority())
	{
		return;
	}


	// 해당 노티파이의 오너가 피가 1이상인지 체크
	if (Boss->EnemyInfo.Curhp <= 0.0f) return;


	
	
	// 월드에 있는 중앙을 나타내는 씬엑터를 찾아서 위치값을 가져오기
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

	// 보스를 씬 위치로 이동시키기 
	FVector TargetWorldLoc = FVector(WorldLoc.X, WorldLoc.Y, Boss->GetActorLocation().Z);

	FRotator TargetWorldRot = FRotator::ZeroRotator;



	TargetWorldRot = FRotator(WorldRot.Pitch, WorldRot.Yaw + 180, WorldRot.Roll);

	

	if (TargetWorldLoc.IsZero()) return;
	Boss->SetActorLocation(TargetWorldLoc);
	Boss->SetActorRotation(TargetWorldRot);



	// 씬 위치에서 데칼 생성
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
		// 시작/목표 스케일 저장
		StartScale = FVector(550.f, 550.f, 550.f); // 처음은 작게 시작
		TargetScale = FVector(4000.f, 4000.f, 4000.f); // 최종적으로 WarningDecal에 시각적으로 맞춤
		AccumulatedTime = 0.f;
		Duration = TotalDuration > 0.f ? TotalDuration : 3.f;

		// 초기화
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

	// 데칼을 틱 길이만큼 늘리기
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


	// 서버인지 체크 
	if (!Boss->HasAuthority())
	{
		return;
	}


	// 해당 노티파이의 오너가 피가 1이상인지 체크
	if (Boss->EnemyInfo.Curhp <= 0.0f) return;


	// 데칼 삭제 
	if (IsValid(SpawnedDecalActor))
	{
		SpawnedDecalActor->Destroy();
		SpawnedDecalActor = nullptr;
	}

	AccumulatedTime = 0.f;


	// 반원에 대한 플레이어를 감지하고 데미지 처리하기

	FVector BossLocation = Boss->GetActorLocation();
	float Radius = 5000.0f;

	TArray<AActor*> OverlappedActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery9);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Boss);

	// 오버랩 수행
	bool bHit = UKismetSystemLibrary::SphereOverlapActors
	(
		Boss->GetWorld(),
		BossLocation,                 // 중점 위치
		Radius,                      // 범위
		ObjectTypes,                // 오브젝트타입
		ACharacter::StaticClass(), // Actor Class Filter
		ActorsToIgnore,           // 무시할엑터들
		OverlappedActors         // 오버랩된 엑터들
	);

	if (!bHit) return;

	// 방향 비교
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
			// 반원 안에 있는 플레이어입니다.
			GEngine->AddOnScreenDebugMessage
			(
				-1,                        // 키값 (-1은 자동 할당)
				5.0f,                      // 화면에 표시될 시간 (초)
				FColor::Green,            // 글씨 색상
				FString::Printf(TEXT("Player :%s"), *Player->GetName())
			);




			FHitResult HitResult;
			//                                 피해자 ,가해자 ,데미지양 ,그냥히트결과, 상태이상효과,
			UC_DamageManager::ApplyPointDamage(Player, Boss, Boss->EnemyInfo.Damage, HitResult);


			GEngine->AddOnScreenDebugMessage
			(
				-1,                        // 키값 (-1은 자동 할당)
				5.0f,                      // 화면에 표시될 시간 (초)
				FColor::Red,            // 글씨 색상
				FString::Printf(TEXT("PlayerHP : %.1f"), Player->CharacterInfo.Curhp)
			);


		}
	}

}
