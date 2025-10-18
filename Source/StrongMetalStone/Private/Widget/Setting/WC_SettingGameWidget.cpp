// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Setting/WC_SettingGameWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "Character/C_PlayerCharacter.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "GameFramework/GameUserSettings.h"

void UWC_SettingGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

    // 해상도 목록 추가
    if (ComboBoxScreenSize)
    {
        ComboBoxScreenSize->AddOption("1920x1080");
        ComboBoxScreenSize->AddOption("1280x720");
        ComboBoxScreenSize->AddOption("2560x1440");
        ComboBoxScreenSize->SetSelectedOption("1920x1080");
        ComboBoxScreenSize->OnSelectionChanged.AddDynamic(this, &UWC_SettingGameWidget::OnScreenSizeSelected);
    }

    // 슬라이더 바인딩
    if (Slider_MouseSpeed)
    {
        Slider_MouseSpeed->OnValueChanged.AddDynamic(this, &UWC_SettingGameWidget::OnMouseSpeedChanged);
    }

    // 기본값 초기화
    SelectedScreenSize = FVector2D(1920, 1080);

}

void UWC_SettingGameWidget::OnMouseSpeedChanged(float Value)
{
    CastWPC(GetMyPC())->MouseSpeed = Value;
}


void UWC_SettingGameWidget::OnScreenSizeSelected(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());
    AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
    if (!WorldController)return;

    if (BeginSound)// 인벤토리 소리
    {
        UGameplayStatics::PlaySoundAtLocation(this, BeginSound, Character->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
    }

    FString XStr, YStr;
    if (SelectedItem.Split("x", &XStr, &YStr))
    {
        SelectedScreenSize.X = FCString::Atoi(*XStr);
        SelectedScreenSize.Y = FCString::Atoi(*YStr);
    }
    GEngine->GetGameUserSettings()->SetScreenResolution(FIntPoint(SelectedScreenSize.X, SelectedScreenSize.Y));
    SaveSetting();
}

void UWC_SettingGameWidget::SaveSetting()
{   
   GEngine->GetGameUserSettings()->ApplySettings(false);

   GEngine->GetGameUserSettings()->SaveSettings();
   GEngine->GetGameUserSettings()->LoadSettings();
}


