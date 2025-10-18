#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "C_DamageManager.generated.h"

class AC_SMSEffectINS;

UCLASS()
class STRONGMETALSTONE_API UC_DamageManager : public UObject
{
	GENERATED_BODY()

public:
	// 정확히 정해진 대상에게 데미지를 적용하는 함수
	UFUNCTION(BlueprintCallable)
	static void ApplyPointDamage(
		AActor* TargetActor, //데미지 받는 사람
		AActor* DamageActor, //데미지를 가하는 엑터
		float Damage, //데미지량
		const FHitResult& Hit, //히트 결과
		TSubclassOf<AC_SMSEffectINS> EffectClass = nullptr, //상태이상
		AController* InstigatedBy =nullptr, //데미지를 준 컨트롤러		
		FVector ShotDirection = FVector(0,0,0) //피격 방향
	);

	// 범위 데미지를 적용하는 함수
	UFUNCTION(BlueprintCallable)
	static void ApplyRadialDamage(	
		AActor* DamageActor, //데미지를 가하는 엑터
		float Damage, //데미지량
		const FVector& Origin, //데미지 중점
		float DamageRadius, //데미지 범위		
		TArray<AActor*> IgnoreActors, //무시할 엑터
		TSubclassOf<AC_SMSEffectINS> EffectClass =nullptr, //상태이상
		AController* InstigatedBy = nullptr, //데미지를 준 컨트롤러
		bool bDoFullDamage = false //거리 기반 데미지를 줄지 여부
	);
};