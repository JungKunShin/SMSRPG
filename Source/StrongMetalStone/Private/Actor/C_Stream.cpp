// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/C_Stream.h"
#include "PlayerController/C_WorldPlayerController.h"

void AC_Stream::BeginPlay()
{
	Super::BeginPlay();

	AC_WorldPlayerController* WPC = Cast< AC_WorldPlayerController>(GetWorld()->GetFirstPlayerController());
	if (!WPC)return;

	if (BeginSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, BeginSound, GetActorLocation(), WPC->SoundManager->EffectVolume, 1.0f,0.0f, AttenuationSetting);
	}
}
