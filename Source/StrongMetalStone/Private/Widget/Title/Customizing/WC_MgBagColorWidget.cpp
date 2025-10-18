// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_MgBagColorWidget.h"
#include "Character/C_Mage.h"
#include "Widget/WC_SMSButton.h"
#include "HUD/C_TitleHUD.h"
#include "Manager/C_CustomizingManager.h"
#include "PlayerController/C_TitlePlayerController.h"

void UWC_MgBagColorWidget::NativeConstruct()
{
	// �������� ��ư �ʱ�ȭ
	OriginalButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_bag.icon_bag")), FVector3f(1.f, 1.f, 1.f));
	// �������� ��ư�� �Լ� ���ε�
	OriginalButton->OnButtonClicked.AddDynamic(this, &UWC_MgBagColorWidget::OnOriginalButtonClicked);
	// �Ķ� ��ư �ʱ�ȭ
	BlueButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_bag.icon_bag")), FVector3f(1.f, 1.f, 1.f));
	// �Ķ� ��ư�� �Լ� ���ε�
	BlueButton->OnButtonClicked.AddDynamic(this, &UWC_MgBagColorWidget::OnBlueButtonClicked);
	// �ʷ� ��ư �ʱ�ȭ
	GreenButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_bag.icon_bag")), FVector3f(1.f, 1.f, 1.f));
	// �ʷ� ��ư�� �Լ� ���ε�
	GreenButton->OnButtonClicked.AddDynamic(this, &UWC_MgBagColorWidget::OnGreenButtonClicked);
	// ���� ��ư �ʱ�ȭ
	RedButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_bag.icon_bag")), FVector3f(1.f, 1.f, 1.f));
	// ���� ��ư�� �Լ� ���ε�
	RedButton->OnButtonClicked.AddDynamic(this, &UWC_MgBagColorWidget::OnRedButtonClicked);
	// ��� ��ư �ʱ�ȭ
	YellowButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_bag.icon_bag")), FVector3f(1.f, 1.f, 1.f));
	// ��� ��ư�� �Լ� ���ε�
	YellowButton->OnButtonClicked.AddDynamic(this, &UWC_MgBagColorWidget::OnYellowButtonClicked);
	// û�� ��ư �ʱ�ȭ
	CyanButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_bag.icon_bag")), FVector3f(1.f, 1.f, 1.f));
	// û�� ��ư�� �Լ� ���ε�
	CyanButton->OnButtonClicked.AddDynamic(this, &UWC_MgBagColorWidget::OnCyanButtonClicked);
}

void UWC_MgBagColorWidget::OnOriginalButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetWeaponColor(Mage, 0);
		Mage->CharacterInfo.CustomizingInfo.WeaponColorNum = 0;
	}
}

void UWC_MgBagColorWidget::OnBlueButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetWeaponColor(Mage, 1);
		Mage->CharacterInfo.CustomizingInfo.WeaponColorNum = 1;
	}
}

void UWC_MgBagColorWidget::OnGreenButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetWeaponColor(Mage, 2);
		Mage->CharacterInfo.CustomizingInfo.WeaponColorNum = 2;
	}
}

void UWC_MgBagColorWidget::OnRedButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetWeaponColor(Mage, 3);
		Mage->CharacterInfo.CustomizingInfo.WeaponColorNum = 3;
	}
}

void UWC_MgBagColorWidget::OnYellowButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetWeaponColor(Mage, 4);
		Mage->CharacterInfo.CustomizingInfo.WeaponColorNum = 4;
	}
}

void UWC_MgBagColorWidget::OnCyanButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	AC_Mage* Mage = Cast<AC_Mage>(Cast<AC_TitleHUD>(GetMyHUD())->CustomChar);

	if (Mage)
	{
		UC_CustomizingManager::SetWeaponColor(Mage, 5);
		Mage->CharacterInfo.CustomizingInfo.WeaponColorNum = 5;
	}
}

void UWC_MgBagColorWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// �κ��丮 �Ҹ�
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
