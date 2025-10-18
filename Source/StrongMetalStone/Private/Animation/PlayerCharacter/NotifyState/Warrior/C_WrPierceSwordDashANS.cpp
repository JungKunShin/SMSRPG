// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PlayerCharacter/NotifyState/Warrior/C_WrPierceSwordDashANS.h"
#include "Character/C_Warrior.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_WrPierceSwordDashANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp)return;

	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;
	if (Warrior)
	{
		UCharacterMovementComponent* MovementComp = Warrior->GetCharacterMovement(); // CharacterMovement 저장
		if (!MovementComp) return;

		FVector ForwardVector = Warrior->GetActorForwardVector();

		DashDirection = ForwardVector; //무조건 캐릭터 앞방향으로 대쉬
	
		if (!Warrior->SkillSytemComponent->CurSkill)return;
		Warrior->LaunchCharacter(DashDirection * DashSpeed* Warrior->SkillSytemComponent->CurSkill->SkillCombo, true, true);

	
		//중력,마찰 끄기
		MovementComp->GravityScale = 0.0f;
		Warrior->GetCharacterMovement()->GroundFriction = 0.0f;
		Warrior->GetCharacterMovement()->BrakingFrictionFactor = 0.0f;
		Warrior->GetCharacterMovement()->BrakingFriction = 0.0f;

	}
}

void UC_WrPierceSwordDashANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;
	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC)return;
	if (Warrior)
	{
		//중력,마찰복귀		
		Warrior->GetCharacterMovement()->GravityScale = 2.0f;
		Warrior->GetCharacterMovement()->GroundFriction = 8.0f;
		Warrior->GetCharacterMovement()->BrakingFrictionFactor = 1.0f;
		Warrior->GetCharacterMovement()->BrakingFriction = 8.0f;

		Warrior->GetCharacterMovement()->Velocity = FVector(0, 0, 0);
	}
}

