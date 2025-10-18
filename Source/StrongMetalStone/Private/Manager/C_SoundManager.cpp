// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/C_SoundManager.h"


AC_SoundManager::AC_SoundManager()
{
    BGMComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BGMComponent"));    
    
    BGMComponent->bIsUISound = true;
    BGMComponent->bAutoDestroy = false;
}

void AC_SoundManager::BeginPlay()
{
    Super::BeginPlay();
}

void AC_SoundManager::Init()
{
    SetMasterVolume(MasterVolume);
    SetBGMVolume(BGMVolume);
    SetEffectVolume(EffectVolume);
    SetUIVolume(UIVolume);
}

void AC_SoundManager::PlayBGM(USoundBase* BGM)
{
    UE_LOG(LogTemp, Warning, TEXT("PlayBGM() called!"));
    if (BGMComponent && BGM)
    {
        BGMComponent->SetSound(BGM);
        BGMComponent->Play();
        CurBGM = BGM;
    }
}

void AC_SoundManager::StopBGM()
{
    if (BGMComponent)
    {
        BGMComponent->Stop();
    }
}

void AC_SoundManager::SetMasterVolume(float Volume)
{
    MasterVolume = Volume;
    SetBGMVolume(BGMVolume);
    SetEffectVolume(EffectVolume);
    SetUIVolume(UIVolume);
}

void AC_SoundManager::SetBGMVolume(float Volume)
{   
    if (BGMComponent)
    {
        BGMVolume = Volume;
        float ResultVolume = (MasterVolume * BGMVolume) / 2;
        BGMComponent->SetVolumeMultiplier(FMath::Clamp(ResultVolume, 0.0f, 1.0f));      
        
    }
}

void AC_SoundManager::SetEffectVolume(float Volume)
{
    EffectVolume = Volume;
}

void AC_SoundManager::SetUIVolume(float Volume)
{
    UIVolume = Volume;
}
