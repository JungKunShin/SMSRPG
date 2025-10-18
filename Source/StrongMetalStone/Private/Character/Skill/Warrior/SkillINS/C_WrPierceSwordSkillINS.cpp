// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Skill/Warrior/SkillINS/C_WrPierceSwordSkillINS.h"
#include "Character/C_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/C_WorldPlayerController.h"

AC_WrPierceSwordSkillINS::AC_WrPierceSwordSkillINS()
{
}

void AC_WrPierceSwordSkillINS::StartOnce(AC_SMSCharacter* Character)
{
	if (OnCool)
	{		
		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());

		if (Player->CharacterInfo.Curmp >= DemandedMana)
		{
			OnTriggerCooldown.Broadcast(this);
			bOnStart = true;
			WPC->bOnAttacking = true;

			Character->ServerPlayMontage(SkillAsset->SkillMontage); // ������ ��Ÿ�� ����
			BasicWalkSpeed = Character->GetCharacterMovement()->MaxWalkSpeed; // ���� �ȱ� �ӵ� ����
			Character->GetCharacterMovement()->MaxWalkSpeed = CHARGING_WALK_SPEED; // ��¡ �ӵ����� ��ȯ
			CastWCharacter(Character)->ServerWalk(); // �����ӵ��� ��ȯ

			GetWorld()->GetTimerManager().ClearTimer(ComboTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AC_WrPierceSwordSkillINS::SkillComboReset, FIRST_COMBO_TIME, false);
			GetWorld()->GetTimerManager().ClearTimer(WalkSpeedTH);
			GetWorld()->GetTimerManager().SetTimer(WalkSpeedTH, this, &AC_WrPierceSwordSkillINS::OriginSpeedBack, FIRST_COMBO_TIME, false);

			Player->CharacterInfo.Curmp -= DemandedMana;
			Player->Update();
		}
	}

}

void AC_WrPierceSwordSkillINS::EndHold(AC_SMSCharacter* Character)
{
	if (OnCool&&bOnStart)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Is Bound: %s"), OnStartCooldown.IsBound() ? TEXT("true") : TEXT("false"));
		OnStartCooldown.Broadcast(this);

		if (Character == nullptr)
			Character = CastWCharacter(GetMyCharacter());

		Character->ServerStopMontage(); // ��Ÿ�� ���߱�

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());
		WPC->bOnAttacking = false;
		OnCool = false; 
		bOnStart = false;
		DelayCoolTime();

		Character->ServerPlayMontage(SkillAsset->ExtraSkillMontage, "PierceSword"); // ������ ��ų ��Ÿ�� "PierceSword" ����
		GetWorld()->GetTimerManager().ClearTimer(WalkSpeedTH);
		Character->GetCharacterMovement()->MaxWalkSpeed = BasicWalkSpeed; // �ȴ� �ӵ� ���� �ȱ� �ӵ��� ��ȯ
		CastWCharacter(Character)->ServerRun(); // �����ӵ��� ��ȯ
	}
}

void AC_WrPierceSwordSkillINS::SecondCharge()
{
	GetWorld()->GetTimerManager().ClearTimer(ComboTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(WalkSpeedTH);
	GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AC_WrPierceSwordSkillINS::SkillComboReset, SECOND_COMBO_TIME, false);
	GetWorld()->GetTimerManager().SetTimer(WalkSpeedTH, this, &AC_WrPierceSwordSkillINS::OriginSpeedBack, SECOND_COMBO_TIME, false);
}

void AC_WrPierceSwordSkillINS::ThirdCharge()
{
	GetWorld()->GetTimerManager().ClearTimer(ComboTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(WalkSpeedTH);
	GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &AC_WrPierceSwordSkillINS::SkillComboReset, THIRD_COMBO_TIME, false);
	GetWorld()->GetTimerManager().SetTimer(WalkSpeedTH, this, &AC_WrPierceSwordSkillINS::OriginSpeedBack, THIRD_COMBO_TIME, false);
}

void AC_WrPierceSwordSkillINS::OriginSpeedBack()
{
	CastWCharacter(GetMyCharacter())->GetCharacterMovement()->MaxWalkSpeed = BasicWalkSpeed; // �ȴ� �ӵ� ���� �ȱ� �ӵ��� ��ȯ
	CastWCharacter(GetMyCharacter())->ServerRun(); // �����ӵ��� ��ȯ
	GetWorld()->GetTimerManager().ClearTimer(WalkSpeedTH);
}
