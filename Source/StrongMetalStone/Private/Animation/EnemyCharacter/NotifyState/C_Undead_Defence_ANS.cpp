// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/EnemyCharacter/NotifyState/C_Undead_Defence_ANS.h"
#include "Character/C_Undead.h"



void UC_Undead_Defence_ANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{

    if (AC_Undead* Undead = Cast<AC_Undead>(MeshComp->GetOwner()))
    {
        Undead->bIsBlocking = true;
    }

}

void UC_Undead_Defence_ANS::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

    if (AC_Undead* Undead = Cast<AC_Undead>(MeshComp->GetOwner()))
    {
        Undead->bIsBlocking = false;

        Undead->bParryFinishedClean = true;
    }

}
