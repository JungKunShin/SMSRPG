// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Setting/WC_SettingSoundWidget.h"
#include "PlayerController/C_WorldPlayerController.h"
#include "Character/C_PlayerCharacter.h"
#include "Components/ComboBoxString.h"

void UWC_SettingSoundWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AudioVolumeSlider_Master->OnValueChanged.AddDynamic(this, &UWC_SettingSoundWidget::OnMasterVolumeChanged);
    AudioVolumeSlider_BackGround->OnValueChanged.AddDynamic(this, &UWC_SettingSoundWidget::OnBGMVolumeChanged);
    AudioVolumeSlider_Effect->OnValueChanged.AddDynamic(this, &UWC_SettingSoundWidget::OnEffectVolumeChanged);
    AudioVolumeSlider_UI->OnValueChanged.AddDynamic(this, &UWC_SettingSoundWidget::OnUIVolumeChanged);

    ComboBox_BGM->AddOption(TEXT("배경음악1"));
    ComboBox_BGM->AddOption(TEXT("배경음악2"));
    ComboBox_BGM->AddOption(TEXT("배경음악3"));
    ComboBox_BGM->SetSelectedOption(TEXT("배경음악1"));
    ComboBox_BGM->OnSelectionChanged.AddDynamic(this, &UWC_SettingSoundWidget::OnBGMSelected);

    //if (CastWPS(GetMyPS())->SoundManager->MasterVolume)
    {
        AudioVolumeSlider_Master->SetValue(Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->MasterVolume);
        AudioVolumeSlider_BackGround->SetValue(Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->BGMVolume);
        AudioVolumeSlider_Effect->SetValue(Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->EffectVolume);
        AudioVolumeSlider_UI->SetValue(Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->UIVolume);
    }
    AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());
    AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
    if (!WorldController)return;

    if (ButtonSound)// 인벤토리 소리
    {
        UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, Character->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
    }

}

void UWC_SettingSoundWidget::OnBGMSelected(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    if (SelectedItem == TEXT("배경음악1"))
    {       
        Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->PlayBGM(Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->BGM_Maple);
    }
    else if (SelectedItem == TEXT("배경음악2"))
    {
        Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->PlayBGM(Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->BGM_JULU);
    }
    else if (SelectedItem == TEXT("배경음악3"))
    {
        Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->PlayBGM(Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->BGM_MAORI);
    }
    AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());
    AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
    if (!WorldController)return;

    if (ButtonSound)// 인벤토리 소리
    {
        UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, Character->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
    }
    
}

void UWC_SettingSoundWidget::OnMasterVolumeChanged(float NewValue)
{
    if (Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->MasterVolume)
    {
        Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->SetMasterVolume(NewValue);
    }
}

void UWC_SettingSoundWidget::OnBGMVolumeChanged(float NewValue)
{
    if (Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->BGMVolume)
    {
        Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->SetBGMVolume(NewValue);
    }
}

void UWC_SettingSoundWidget::OnEffectVolumeChanged(float NewValue)
{
    if (Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->EffectVolume)
    {
        Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->SetEffectVolume(NewValue);
    }
}

void UWC_SettingSoundWidget::OnUIVolumeChanged(float NewValue)
{
    if (Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->UIVolume)
    {
        Cast<AC_SMSPlayerController>(GetMyPC())->SoundManager->SetUIVolume(NewValue);
    }
}
