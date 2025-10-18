// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/C_EnemyAniminstance.h"
#include "Character/C_Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"





void UC_EnemyAniminstance::NativeInitializeAnimation()
{
	// AnimInstance가 메시에 완전히 연결되고 나서 실행됨
	// 한 번만 실행됨	애니메이션 시스템이 자동으로 보장

	Super::NativeInitializeAnimation();

	Enemy = Cast<AC_Enemy>(GetOwningActor());		//PlayerCharacter로 형변환
	if (Enemy)
	{
		Movement = Enemy->GetCharacterMovement();			//Owner의 Movement저장
	}
}

void UC_EnemyAniminstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// 여기서 몽타주 재생이나 기타 초기 로직 가능
	if (SpawnAnimation && Montage_IsPlaying(SpawnAnimation) == false)  // "SpawnAnimation이 유효하고, 그 몽타주가 현재 재생되고 있지 않다면"
	{
		Montage_Play(SpawnAnimation);
	}


}



void UC_EnemyAniminstance::NativeUpdateAnimation(float DeltaSeconds)
{

	//  매번 틱으로 업데이트 함
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		//Speed = UKismetMathLibrary::VSize(Movement->Velocity); //OwnerSpeed는 Movement의 속도 가져오기
		Speed = Movement->Velocity.Length();
	}


	if(Enemy)
	{ 
	FVector Velocity = Enemy->GetVelocity();
	FRotator Rotation = Enemy->GetActorRotation();
    
	Direction = CalculateDirection(Velocity, Rotation);
	}




}
