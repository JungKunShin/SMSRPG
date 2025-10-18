#include "Animation/PlayerCharacter/NotifyState/Warrior/C_WrPierceSwordChargingANS.h"
#include "Character/C_Warrior.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HUD/C_WorldHUD.h"
#include "Character/Skill/Warrior/SkillINS/C_WrPierceSwordSkillINS.h"

void UC_WrPierceSwordChargingANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (!MeshComp)return;

	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;

	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC)return;

	if (MeshComp->GetOwner()->HasAuthority())
	{
		//UE_LOG(LogTemp, Warning, TEXT("ServerSkillCombo: %d"), Warrior->SkillSytemComponent->CurSkill->SkillCombo);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("ClientSkillCombo: %d"), Warrior->SkillSytemComponent->CurSkill->SkillCombo);
	}

	AC_WrPierceSwordSkillINS* CurSkill = Cast<AC_WrPierceSwordSkillINS>(Warrior->SkillSytemComponent->CurSkill);
	if (!CurSkill)return;

	CurSkill->SkillCombo += 1; // 스킬 콤보 1증가

	if (CurSkill->SkillCombo == 2)
	{
		CurSkill->SecondCharge();
	}
	else if (CurSkill->SkillCombo == 3)
	{
		CurSkill->ThirdCharge();
	}
}

void UC_WrPierceSwordChargingANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float DeltaTime)
{
	if (!MeshComp)return;

	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior)return;
}

void UC_WrPierceSwordChargingANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	AC_Warrior* Warrior = CastWWarrior(MeshComp->GetOwner());
	if (!Warrior) return;

	AC_WorldPlayerController* WPC = Cast<AC_WorldPlayerController>(Warrior->GetController());
	if (!WPC) return;

	if (!Warrior->SkillSytemComponent->CurSkill) return;

	if (Warrior->SkillSytemComponent->CurSkill->SkillCombo == Warrior->SkillSytemComponent->CurSkill->SkillAsset->MaxCombo)
	{
		Warrior->SkillSytemComponent->CurSkill->EndHold(Warrior);
	}
	else if (ADD_DEMANDED_MANA > Warrior->CharacterInfo.Curmp)
	{
		Warrior->SkillSytemComponent->CurSkill->EndHold(Warrior);
		
		if (WPC->IsLocalController())
		{
			AC_WorldHUD* WorldHUD = Cast<AC_WorldHUD>(WPC->GetHUD());
			if (!WorldHUD) return;

			WorldHUD->StartCooldown(Warrior->SkillSytemComponent->CurSkill);
		}
	}
	else
	{
		Warrior->CharacterInfo.Curmp -= ADD_DEMANDED_MANA;
		Warrior->Update();
		Warrior->ClientUpdate();
	}
}
