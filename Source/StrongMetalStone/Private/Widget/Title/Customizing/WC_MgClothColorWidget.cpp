// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_MgClothColorWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_Mage.h"
#include "HUD/C_TitleHUD.h"
#include "Manager/C_CustomizingManager.h"
#include "PlayerController/C_TitlePlayerController.h"

void UWC_MgClothColorWidget::NativeConstruct()
{
	// �������� ��ư �ʱ�ȭ
	OriginalButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_cloth.icon_cloth")), FVector3f(1.f, 1.f, 1.f));
	// �������� ��ư�� �Լ� ���ε�
	OriginalButton->OnButtonClicked.AddDynamic(this, &UWC_MgClothColorWidget::OnOriginalButtonClicked);
	// �޶ѱ� ��ư �ʱ�ȭ
	GrassHopherButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_cloth.icon_cloth")), FVector3f(1.f, 1.f, 1.f));
	// �޶ѱ� ��ư�� �Լ� ���ε�
	GrassHopherButton->OnButtonClicked.AddDynamic(this, &UWC_MgClothColorWidget::OnGrassHopherButtonClicked);
	// �¾�� �� ��ư �ʱ�ȭ
	GodLaButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_cloth.icon_cloth")), FVector3f(1.f, 1.f, 1.f));
	// �¾�� �� ��ư�� �Լ� ���ε�
	GodLaButton->OnButtonClicked.AddDynamic(this, &UWC_MgClothColorWidget::OnGodLaButtonClicked);
	// �����ε��� ��ư �ʱ�ȭ
	AphroditeButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_cloth.icon_cloth")), FVector3f(1.f, 1.f, 1.f));
	// �����ε��� ��ư�� �Լ� ���ε�
	AphroditeButton->OnButtonClicked.AddDynamic(this, &UWC_MgClothColorWidget::OnAphroditeButtonClicked);
	// �׻��� ��ư �ʱ�ȭ
	PoopGuyButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_cloth.icon_cloth")), FVector3f(1.f, 1.f, 1.f));
	// �׻��� ��ư�� �Լ� ���ε�
	PoopGuyButton->OnButtonClicked.AddDynamic(this, &UWC_MgClothColorWidget::OnPoopGuyButtonClicked);
	// ���뺸�� ��ư �ʱ�ȭ
	BonoBonoButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_cloth.icon_cloth")), FVector3f(1.f, 1.f, 1.f));
	// ���뺸�� ��ư�� �Լ� ���ε�
	BonoBonoButton->OnButtonClicked.AddDynamic(this, &UWC_MgClothColorWidget::OnBonoBonoButtonClicked);
}

void UWC_MgClothColorWidget::OnOriginalButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�
	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetArmorColor(Mage, 0);
		Mage->CharacterInfo.CustomizingInfo.ArmorColorNum = 0;
	}
}

void UWC_MgClothColorWidget::OnGrassHopherButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�
	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetArmorColor(Mage, 1);
		Mage->CharacterInfo.CustomizingInfo.ArmorColorNum = 1;
	}
}

void UWC_MgClothColorWidget::OnGodLaButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�
	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetArmorColor(Mage, 2);
		Mage->CharacterInfo.CustomizingInfo.ArmorColorNum = 2;
	}
}

void UWC_MgClothColorWidget::OnAphroditeButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�
	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetArmorColor(Mage, 3);
		Mage->CharacterInfo.CustomizingInfo.ArmorColorNum = 3;
	}
}

void UWC_MgClothColorWidget::OnPoopGuyButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�
	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetArmorColor(Mage, 4);
		Mage->CharacterInfo.CustomizingInfo.ArmorColorNum = 4;
	}
}

void UWC_MgClothColorWidget::OnBonoBonoButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�
	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetArmorColor(Mage, 5);
		Mage->CharacterInfo.CustomizingInfo.ArmorColorNum = 5;
	}
}

void UWC_MgClothColorWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// �κ��丮 �Ҹ�
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
