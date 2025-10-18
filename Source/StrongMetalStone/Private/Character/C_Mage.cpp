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
	UMaterialInterface* BaseMatFace = GetMesh()->GetMaterial(1); // ���� 1 ����(�󱼻�)
	DynMaterialFace = UMaterialInstanceDynamic::Create(BaseMatFace, this);
	GetMesh()->SetMaterial(1, DynMaterialFace);
	UMaterialInterface* BaseMatEye = GetMesh()->GetMaterial(7); // ���� 7 ����(������)
	DynMaterialEye = UMaterialInstanceDynamic::Create(BaseMatEye, this);
	GetMesh()->SetMaterial(7, DynMaterialEye);

	UMaterialInterface* BaseMatHair = GetMesh()->GetMaterial(9); // ���� 9 ����(�Ӹ�����)
	DynMaterialHair1 = UMaterialInstanceDynamic::Create(BaseMatHair, this);
	GetMesh()->SetMaterial(9, DynMaterialHair1);
	DynMaterialHair2 = UMaterialInstanceDynamic::Create(BaseMatHair, this);
	GetMesh()->SetMaterial(13, DynMaterialHair2);

	UMaterialInterface* BaseMatEyeLash = GetMesh()->GetMaterial(12); // ���� 12 ����(�Ӵ������)
	DynMaterialEyeLash = UMaterialInstanceDynamic::Create(BaseMatEyeLash, this);
	GetMesh()->SetMaterial(12, DynMaterialEyeLash);

	UMaterialInterface* BaseMatJacket = GetMesh()->GetMaterial(0); // ���� 0 ����(���ϻ���)
	DynMaterialJacket1 = UMaterialInstanceDynamic::Create(BaseMatJacket, this);
	GetMesh()->SetMaterial(0, DynMaterialJacket1);
	DynMaterialJacket2 = UMaterialInstanceDynamic::Create(BaseMatJacket, this);
	GetMesh()->SetMaterial(10, DynMaterialJacket2);

	UMaterialInterface* BaseMatSkirt = GetMesh()->GetMaterial(2); // ���� 0 ����(���ϻ���)
	DynMaterialSkirt1 = UMaterialInstanceDynamic::Create(BaseMatSkirt, this);
	GetMesh()->SetMaterial(2, DynMaterialSkirt1);
	DynMaterialSkirt2 = UMaterialInstanceDynamic::Create(BaseMatSkirt, this);
	GetMesh()->SetMaterial(5, DynMaterialSkirt2);

	UMaterialInterface* BaseMatJewelery = GetMesh()->GetMaterial(3); // ���� 3 ����(��ű�����)
	DynMaterialJewelery = UMaterialInstanceDynamic::Create(BaseMatJewelery, this);
	GetMesh()->SetMaterial(3, DynMaterialJewelery);

	UMaterialInterface* BaseMatBag = GetMesh()->GetMaterial(4); // ���� 4 ����(�������)
	DynMaterialBag = UMaterialInstanceDynamic::Create(BaseMatBag, this);
	GetMesh()->SetMaterial(4, DynMaterialBag);
}

void AC_Mage::NewColor(float Value)
{
	if (DynMaterialFace)
	{
		FLinearColor Color = FLinearColor::LerpUsingHSV(
			FLinearColor::White,          // ���� ����
			FLinearColor::Black,          // �� ����
			Value                   // 0.0 ~ 1.0
		);

		DynMaterialFace->SetVectorParameterValue("SkinColor", Color);
	}
}

void AC_Mage::ButtonColor(FLinearColor Color, int32 Index)
{
	if (DynMaterialEye && Index == 7) // ������
	{
		DynMaterialEye->SetVectorParameterValue("EyeColor", Color);
	}
	if (DynMaterialHair1 && Index == 9) // �Ӹ�ī��1����
	{
		DynMaterialHair1->SetVectorParameterValue("RootColor", Color);
	}
	if (DynMaterialHair2 && Index == 13) // �Ӹ�ī��2����
	{
		DynMaterialHair2->SetVectorParameterValue("TipColor", Color);
	}
	if (DynMaterialEyeLash && Index == 12) // �Ӵ������
	{
		DynMaterialEyeLash->SetVectorParameterValue("EyeLash Color", Color);
	}
	if (DynMaterialJacket1&& DynMaterialJacket2 && Index == 10) // ������ �ʻ���
	{
		DynMaterialJacket1->SetVectorParameterValue("FabricColor", Color);
		DynMaterialJacket2->SetVectorParameterValue("FabricColor", Color);
	}
	if (DynMaterialJacket1 && DynMaterialJacket2 && Index == 101) // ���� �ٱ��� �ʻ���
	{
		DynMaterialJacket1->SetVectorParameterValue("OutColor", Color);
		DynMaterialJacket2->SetVectorParameterValue("OutColor", Color);
	}
	if (DynMaterialJacket1 && DynMaterialJacket2 && Index == 102) // ���� ĳ���� ����
	{
		DynMaterialJacket1->SetVectorParameterValue("Silk Base Tint", Color);
		DynMaterialJacket2->SetVectorParameterValue("Silk Base Tint", Color);
		DynMaterialJacket1->SetVectorParameterValue("Silk T Scattering Tint", Color);
		DynMaterialJacket2->SetVectorParameterValue("Silk T Scattering Tint", Color);
	}
	if (DynMaterialJacket1 && DynMaterialJacket2 && Index == 104) // ��ü ����
	{
		DynMaterialJacket1->SetVectorParameterValue("Leather Color", Color);
		DynMaterialJacket2->SetVectorParameterValue("Leather Color", Color);
	}
	if (DynMaterialSkirt1 && DynMaterialSkirt2 && Index == 105) // ��ü ����
	{
		DynMaterialSkirt1->SetVectorParameterValue("Leather Color", Color);
		DynMaterialSkirt2->SetVectorParameterValue("Leather Color", Color);
	}
	if (DynMaterialJewelery&& Index == 107) // ���� ��Ż ����
	{
		DynMaterialJewelery->SetVectorParameterValue("MetalColor", Color);
	}
	if (DynMaterialJewelery && Index == 3) // ���� ����̺���1 ����
	{
		DynMaterialJewelery->SetVectorParameterValue("Phase Gem Deep Color", Color);
	}
	if (DynMaterialJewelery&& Index == 31) // ���� ����̺���2 ����
	{
		DynMaterialJewelery->SetVectorParameterValue("Phase Gem Shallow Color", Color);
	}
	if (DynMaterialBag && Index == 4) // ����
	{
		DynMaterialBag->SetVectorParameterValue("Silk Base Tint", Color);
		DynMaterialBag->SetVectorParameterValue("Silk T Scattering Tint", Color); //��ü���� ��
	}
	if (DynMaterialBag && Index == 41) // ���� ������
	{
		DynMaterialBag->SetVectorParameterValue("MetalColor", Color); //����, ��Ŭ, �� ��
	}

}
