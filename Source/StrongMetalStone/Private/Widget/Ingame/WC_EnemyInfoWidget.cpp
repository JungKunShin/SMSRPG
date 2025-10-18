// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Ingame/WC_EnemyInfoWidget.h"
#include "Widget/WC_SMSProgressBar.h"
#include "Character/C_Enemy.h"
#include "Character/C_PlayerCharacter.h"

void UWC_EnemyInfoWidget::NativeConstruct()
{
    WBPC_SMSProgressBar_Hp->Init(1.0f,HpColor );
    WBPC_SMSProgressBar_Groggy->Init(1.0f, GroggyColor);
}

void UWC_EnemyInfoWidget::OnTarget(AC_SMSCharacter* Character)
{
    SetVisibility(ESlateVisibility::Visible);

    if (AC_Enemy* TargetEnemy = Cast<AC_Enemy>(Character)) //타겟이 몬스터일경우
    {
        GroggyColor = FLinearColor::Yellow;
        TextBlock_Name->SetText(FText::FromString(TargetEnemy->EnemyInfo.Name));
        WBPC_SMSProgressBar_Hp->Update(TargetEnemy->EnemyInfo.Curhp/ TargetEnemy->EnemyInfo.Maxhp);
        WBPC_SMSProgressBar_Groggy->Update(TargetEnemy->EnemyInfo.CurGroggy / TargetEnemy->EnemyInfo.MaxGroggy,GroggyColor);
    }
        
    else if (AC_PlayerCharacter* TargetPlayer = CastWCharacter(Character)) //타겟이 플레이어일 경우
    {
        GroggyColor = FLinearColor::Blue;
        TextBlock_Name->SetText(FText::FromString(TargetPlayer->CharacterInfo.CharacterName));
        WBPC_SMSProgressBar_Hp->Update(TargetPlayer->CharacterInfo.Curhp/ TargetPlayer->CharacterInfo.Maxhp);
        WBPC_SMSProgressBar_Groggy->Update(TargetPlayer->CharacterInfo.Curmp/ TargetPlayer->CharacterInfo.Maxmp, GroggyColor);
    }
        

    
}

void UWC_EnemyInfoWidget::OffTarget()
{
    SetVisibility(ESlateVisibility::Hidden);
}


