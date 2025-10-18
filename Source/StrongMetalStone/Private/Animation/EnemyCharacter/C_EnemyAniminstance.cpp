// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/C_EnemyAniminstance.h"
#include "Character/C_Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"





void UC_EnemyAniminstance::NativeInitializeAnimation()
{
	// AnimInstance�� �޽ÿ� ������ ����ǰ� ���� �����
	// �� ���� �����	�ִϸ��̼� �ý����� �ڵ����� ����

	Super::NativeInitializeAnimation();

	Enemy = Cast<AC_Enemy>(GetOwningActor());		//PlayerCharacter�� ����ȯ
	if (Enemy)
	{
		Movement = Enemy->GetCharacterMovement();			//Owner�� Movement����
	}
}

void UC_EnemyAniminstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// ���⼭ ��Ÿ�� ����̳� ��Ÿ �ʱ� ���� ����
	if (SpawnAnimation && Montage_IsPlaying(SpawnAnimation) == false)  // "SpawnAnimation�� ��ȿ�ϰ�, �� ��Ÿ�ְ� ���� ����ǰ� ���� �ʴٸ�"
	{
		Montage_Play(SpawnAnimation);
	}


}



void UC_EnemyAniminstance::NativeUpdateAnimation(float DeltaSeconds)
{

	//  �Ź� ƽ���� ������Ʈ ��
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		//Speed = UKismetMathLibrary::VSize(Movement->Velocity); //OwnerSpeed�� Movement�� �ӵ� ��������
		Speed = Movement->Velocity.Length();
	}


	if(Enemy)
	{ 
	FVector Velocity = Enemy->GetVelocity();
	FRotator Rotation = Enemy->GetActorRotation();
    
	Direction = CalculateDirection(Velocity, Rotation);
	}




}
