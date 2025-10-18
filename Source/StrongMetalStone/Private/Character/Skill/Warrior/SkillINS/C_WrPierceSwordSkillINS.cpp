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

			Character->ServerPlayMontage(SkillAsset->SkillMontage); // 설정한 몽타주 실행
			BasicWalkSpeed = Character->GetCharacterMovement()->MaxWalkSpeed; // 기존 걷기 속도 저장
			Character->GetCharacterMovement()->MaxWalkSpeed = CHARGING_WALK_SPEED; // 차징 속도으로 변환
			CastWCharacter(Character)->ServerWalk(); // 서버속도도 변환

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

		Character->ServerStopMontage(); // 몽타주 멈추기

		AC_PlayerCharacter* Player = CastWCharacter(GetMyCharacter());
		AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(Player->GetController());
		WPC->bOnAttacking = false;
		OnCool = false; 
		bOnStart = false;
		DelayCoolTime();

		Character->ServerPlayMontage(SkillAsset->ExtraSkillMontage, "PierceSword"); // 별도의 스킬 몽타주 "PierceSword" 실행
		GetWorld()->GetTimerManager().ClearTimer(WalkSpeedTH);
		Character->GetCharacterMovement()->MaxWalkSpeed = BasicWalkSpeed; // 걷는 속도 기존 걷기 속도로 변환
		CastWCharacter(Character)->ServerRun(); // 서버속도도 변환
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
	CastWCharacter(GetMyCharacter())->GetCharacterMovement()->MaxWalkSpeed = BasicWalkSpeed; // 걷는 속도 기존 걷기 속도로 변환
	CastWCharacter(GetMyCharacter())->ServerRun(); // 서버속도도 변환
	GetWorld()->GetTimerManager().ClearTimer(WalkSpeedTH);
}
