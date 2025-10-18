// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CameraShake/C_AttackCameraShake.h"
#include "Shakes/PerlinNoiseCameraShakePattern.h"
#include "Camera/CameraShakeBase.h"

UC_AttackCameraShake::UC_AttackCameraShake(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
    PerlinPattern->X.Amplitude = 1.5f;
    PerlinPattern->X.Frequency = 4.f;//littleok
    PerlinPattern->Y.Amplitude = 2.f;
    PerlinPattern->Y.Frequency = 6.f;//ok
    PerlinPattern->Z.Amplitude = 1.5f;
    PerlinPattern->Z.Frequency = 6.f;//ok

    PerlinPattern->Pitch.Amplitude = 1.f; //littelok
    PerlinPattern->Pitch.Frequency = 2.f; //littleok
    PerlinPattern->Yaw.Amplitude = 0.8f;//littleok
    PerlinPattern->Yaw.Frequency = 4.f;//ok
    PerlinPattern->Roll.Amplitude = 0.3f;
    PerlinPattern->Roll.Frequency = 2.f;

    PerlinPattern->FOV.Amplitude = 0.5f;
    PerlinPattern->FOV.Frequency = 2.f;

    PerlinPattern->Duration = 0.5f;

    SetRootShakePattern(PerlinPattern);
}
