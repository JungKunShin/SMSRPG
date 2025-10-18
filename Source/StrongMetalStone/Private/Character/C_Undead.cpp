// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_Undead.h"
#include "Character/C_PlayerCharacter.h"
#include "GameFramework/DamageType.h"
#include "Engine/DamageEvents.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Component/C_SkillSystemComponent.h"


AC_Undead::AC_Undead()
{
    EnemyInfo.Name = TEXT("테스");
}

float AC_Undead::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

    


    // 공격자가 스킬을 썼는지 확인
    AC_PlayerCharacter* Player = Cast<AC_PlayerCharacter>(DamageCauser);
    if (!Player) return 0.0f;

    UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
    if (!AnimInstance) return 0.0f;

    UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();

    // 플레이어가 데미지를 입히고있는 몽타주가  해당 스킬 몽타주와 같다면 
    UAnimMontage* SkillMontage = Player->SkillSytemComponent->Skill1->SkillAsset->SkillMontage;
    if (bIsBlocking)
    {

        // 방어 중일 땐 데미지를 누적
        BlockAccumulatedDamage += DamageAmount;
    

        if (CurrentMontage == SkillMontage)
         {
          
         this->MultiPlayMontage(this->ParryingMontage);
         bIsBlocking = false;
         bParryFinishedClean = false; // 깨짐 = 실패


         }


        else
        {
      
        return 0.0f;

        }
        
    }

    return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);



}
