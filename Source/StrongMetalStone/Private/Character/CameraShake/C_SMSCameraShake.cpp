// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CameraShake/C_SMSCameraShake.h"
#include "Shakes/PerlinNoiseCameraShakePattern.h"
#include "Camera/CameraShakeBase.h"

UC_SMSCameraShake::UC_SMSCameraShake(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{// UCameraShakeBase에는 기본 생성자가 없어서, UC_SMSCameraShake에서는 기본 생성자를 만들 수 없다.
 // 그러나, FObjectInitializer를 받는 생성자는 있어서, 그 부모 생성자 호출

    PerlinPattern = CreateDefaultSubobject<UPerlinNoiseCameraShakePattern>(TEXT("PerlinNoisePattern"));
    PerlinPattern->X.Amplitude = 0.f;
    PerlinPattern->X.Frequency = 0.f;//littleok
    PerlinPattern->Y.Amplitude = 0.f;
    PerlinPattern->Y.Frequency = 0.f;//ok
    PerlinPattern->Z.Amplitude = 0.f;
    PerlinPattern->Z.Frequency = 0.f;//ok
   
    PerlinPattern->Pitch.Amplitude = 0.f; //littelok
    PerlinPattern->Pitch.Frequency = 0.f; //littleok
    PerlinPattern->Yaw.Amplitude = 0.f;//littleok
    PerlinPattern->Yaw.Frequency = 0.f;//ok
    PerlinPattern->Roll.Amplitude = 0.f;
    PerlinPattern->Roll.Frequency = 0.f;

    PerlinPattern->FOV.Amplitude = 0.f;
    PerlinPattern->FOV.Frequency = 0.f;

    PerlinPattern->Duration = 0.5f;

    SetRootShakePattern(PerlinPattern);
}
