// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CameraShake/C_SMSCameraShake.h"
#include "Shakes/PerlinNoiseCameraShakePattern.h"
#include "Camera/CameraShakeBase.h"

UC_SMSCameraShake::UC_SMSCameraShake(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{// UCameraShakeBase���� �⺻ �����ڰ� ���, UC_SMSCameraShake������ �⺻ �����ڸ� ���� �� ����.
 // �׷���, FObjectInitializer�� �޴� �����ڴ� �־, �� �θ� ������ ȣ��

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
