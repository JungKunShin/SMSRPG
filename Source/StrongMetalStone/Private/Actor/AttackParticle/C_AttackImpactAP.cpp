// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AttackParticle/C_AttackImpactAP.h"

AC_AttackImpactAP::AC_AttackImpactAP()
{
	Damage = 0.0f; // 데미지 0.0
	SphereRadius = 0.1f; // 트레이스 범위 반지름
	DelayTime = 1.0f; // AP 파괴 시간
	ShakeDegree = 2.0f; // 카메라 흔들림 정도
}
