// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/C_Mage.h"

void AC_Mage::BeginPlay()
{
	Super::BeginPlay();
}

AC_Mage::AC_Mage()
{
	CharacterJob = EPlayerJob::MAGE;
	CharacterInfo.Job = EPlayerJob::MAGE;
	CharacterJob= EPlayerJob::MAGE;
}

void AC_Mage::Death(AC_SMSCharacter* Killer)
{
	Super::Death(Killer);

	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
}

void AC_Mage::SetColor()
{
	UMaterialInterface* BaseMatFace = GetMesh()->GetMaterial(1); // 슬롯 1 기준(얼굴색)
	DynMaterialFace = UMaterialInstanceDynamic::Create(BaseMatFace, this);
	GetMesh()->SetMaterial(1, DynMaterialFace);
	UMaterialInterface* BaseMatEye = GetMesh()->GetMaterial(7); // 슬롯 7 기준(눈색깔)
	DynMaterialEye = UMaterialInstanceDynamic::Create(BaseMatEye, this);
	GetMesh()->SetMaterial(7, DynMaterialEye);

	UMaterialInterface* BaseMatHair = GetMesh()->GetMaterial(9); // 슬롯 9 기준(머리색깔)
	DynMaterialHair1 = UMaterialInstanceDynamic::Create(BaseMatHair, this);
	GetMesh()->SetMaterial(9, DynMaterialHair1);
	DynMaterialHair2 = UMaterialInstanceDynamic::Create(BaseMatHair, this);
	GetMesh()->SetMaterial(13, DynMaterialHair2);

	UMaterialInterface* BaseMatEyeLash = GetMesh()->GetMaterial(12); // 슬롯 12 기준(속눈썹색깔)
	DynMaterialEyeLash = UMaterialInstanceDynamic::Create(BaseMatEyeLash, this);
	GetMesh()->SetMaterial(12, DynMaterialEyeLash);

	UMaterialInterface* BaseMatJacket = GetMesh()->GetMaterial(0); // 슬롯 0 기준(자켓색깔)
	DynMaterialJacket1 = UMaterialInstanceDynamic::Create(BaseMatJacket, this);
	GetMesh()->SetMaterial(0, DynMaterialJacket1);
	DynMaterialJacket2 = UMaterialInstanceDynamic::Create(BaseMatJacket, this);
	GetMesh()->SetMaterial(10, DynMaterialJacket2);

	UMaterialInterface* BaseMatSkirt = GetMesh()->GetMaterial(2); // 슬롯 0 기준(자켓색깔)
	DynMaterialSkirt1 = UMaterialInstanceDynamic::Create(BaseMatSkirt, this);
	GetMesh()->SetMaterial(2, DynMaterialSkirt1);
	DynMaterialSkirt2 = UMaterialInstanceDynamic::Create(BaseMatSkirt, this);
	GetMesh()->SetMaterial(5, DynMaterialSkirt2);

	UMaterialInterface* BaseMatJewelery = GetMesh()->GetMaterial(3); // 슬롯 3 기준(장신구색깔)
	DynMaterialJewelery = UMaterialInstanceDynamic::Create(BaseMatJewelery, this);
	GetMesh()->SetMaterial(3, DynMaterialJewelery);

	UMaterialInterface* BaseMatBag = GetMesh()->GetMaterial(4); // 슬롯 4 기준(가방색깔)
	DynMaterialBag = UMaterialInstanceDynamic::Create(BaseMatBag, this);
	GetMesh()->SetMaterial(4, DynMaterialBag);
}

void AC_Mage::NewColor(float Value)
{
	if (DynMaterialFace)
	{
		FLinearColor Color = FLinearColor::LerpUsingHSV(
			FLinearColor::White,          // 시작 색상
			FLinearColor::Black,          // 끝 색상
			Value                   // 0.0 ~ 1.0
		);

		DynMaterialFace->SetVectorParameterValue("SkinColor", Color);
	}
}

void AC_Mage::ButtonColor(FLinearColor Color, int32 Index)
{
	if (DynMaterialEye && Index == 7) // 눈색깔
	{
		DynMaterialEye->SetVectorParameterValue("EyeColor", Color);
	}
	if (DynMaterialHair1 && Index == 9) // 머리카락1색깔
	{
		DynMaterialHair1->SetVectorParameterValue("RootColor", Color);
	}
	if (DynMaterialHair2 && Index == 13) // 머리카락2색깔
	{
		DynMaterialHair2->SetVectorParameterValue("TipColor", Color);
	}
	if (DynMaterialEyeLash && Index == 12) // 속눈썹색깔
	{
		DynMaterialEyeLash->SetVectorParameterValue("EyeLash Color", Color);
	}
	if (DynMaterialJacket1&& DynMaterialJacket2 && Index == 10) // 면재질 옷색깔
	{
		DynMaterialJacket1->SetVectorParameterValue("FabricColor", Color);
		DynMaterialJacket2->SetVectorParameterValue("FabricColor", Color);
	}
	if (DynMaterialJacket1 && DynMaterialJacket2 && Index == 101) // 자켓 바깥쪽 옷색깔
	{
		DynMaterialJacket1->SetVectorParameterValue("OutColor", Color);
		DynMaterialJacket2->SetVectorParameterValue("OutColor", Color);
	}
	if (DynMaterialJacket1 && DynMaterialJacket2 && Index == 102) // 자켓 캐릭터 색깔
	{
		DynMaterialJacket1->SetVectorParameterValue("Silk Base Tint", Color);
		DynMaterialJacket2->SetVectorParameterValue("Silk Base Tint", Color);
		DynMaterialJacket1->SetVectorParameterValue("Silk T Scattering Tint", Color);
		DynMaterialJacket2->SetVectorParameterValue("Silk T Scattering Tint", Color);
	}
	if (DynMaterialJacket1 && DynMaterialJacket2 && Index == 104) // 상체 색깔
	{
		DynMaterialJacket1->SetVectorParameterValue("Leather Color", Color);
		DynMaterialJacket2->SetVectorParameterValue("Leather Color", Color);
	}
	if (DynMaterialSkirt1 && DynMaterialSkirt2 && Index == 105) // 하체 색깔
	{
		DynMaterialSkirt1->SetVectorParameterValue("Leather Color", Color);
		DynMaterialSkirt2->SetVectorParameterValue("Leather Color", Color);
	}
	if (DynMaterialJewelery&& Index == 107) // 자켓 메탈 색깔
	{
		DynMaterialJewelery->SetVectorParameterValue("MetalColor", Color);
	}
	if (DynMaterialJewelery && Index == 3) // 자켓 목걸이비즈1 색깔
	{
		DynMaterialJewelery->SetVectorParameterValue("Phase Gem Deep Color", Color);
	}
	if (DynMaterialJewelery&& Index == 31) // 자켓 목걸이비즈2 색깔
	{
		DynMaterialJewelery->SetVectorParameterValue("Phase Gem Shallow Color", Color);
	}
	if (DynMaterialBag && Index == 4) // 가방
	{
		DynMaterialBag->SetVectorParameterValue("Silk Base Tint", Color);
		DynMaterialBag->SetVectorParameterValue("Silk T Scattering Tint", Color); //전체적인 색
	}
	if (DynMaterialBag && Index == 41) // 가방 디테일
	{
		DynMaterialBag->SetVectorParameterValue("MetalColor", Color); //지퍼, 버클, 찡 색
	}

}
