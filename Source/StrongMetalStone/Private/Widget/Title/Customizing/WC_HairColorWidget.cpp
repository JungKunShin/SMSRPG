// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_HairColorWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_Warrior.h"
#include "Character/C_Mage.h"
#include "HUD/C_TitleHUD.h"
#include "PlayerController/C_TitlePlayerController.h"

void UWC_HairColorWidget::NativeConstruct()
{
	// ���� ��ư �ʱ�ȭ
	RedButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// ���� ��ư�� �Լ� ���ε�
	RedButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnRedButtonClicked);
	// �ʷ� ��ư �ʱ�ȭ
	GreenButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// �ʷ� ��ư�� �Լ� ���ε�
	GreenButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnGreenButtonClicked);
	// �Ķ� ��ư �ʱ�ȭ
	BlueButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// �Ķ� ��ư�� �Լ� ���ε�
	BlueButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnBlueButtonClicked);
	// ���� ��ư �ʱ�ȭ
	BlackButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// ���� ��ư�� �Լ� ���ε�
	BlackButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnBlackButtonClicked);
	// ȸ�� ��ư �ʱ�ȭ
	OriginalButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// ȸ�� ��ư�� �Լ� ���ε�
	OriginalButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnOriginalButtonClicked);
	// ��� ��ư �ʱ�ȭ
	YellowButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// ��� ��ư�� �Լ� ���ε�
	YellowButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnYellowButtonClicked);
	// û�� ��ư �ʱ�ȭ
	CyanButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// û�� ��ư�� �Լ� ���ε�
	CyanButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnCyanButtonClicked);
	// ����Ÿ ��ư �ʱ�ȭ
	MagentaButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_hair.icon_hair")), FVector3f(1.f, 1.f, 1.f));
	// ����Ÿ ��ư�� �Լ� ���ε�
	MagentaButton->OnButtonClicked.AddDynamic(this, &UWC_HairColorWidget::OnMagentaButtonClicked);
}

void UWC_HairColorWidget::OnRedButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 4);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 4;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 4);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 4;
	}
}

void UWC_HairColorWidget::OnGreenButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 1);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 1;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 1);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 1;
	}
}

void UWC_HairColorWidget::OnBlueButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 2);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 2;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 2);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 2;
	}
}

void UWC_HairColorWidget::OnBlackButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 3);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 3;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 0);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 0;
	}
}

void UWC_HairColorWidget::OnOriginalButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 0);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 0;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 3);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 3;
	}
}

void UWC_HairColorWidget::OnYellowButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 5);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 5;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 5);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 5;
	}
}

void UWC_HairColorWidget::OnCyanButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 6;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 6;
	}
}

void UWC_HairColorWidget::OnMagentaButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetHairColor(Warrior, 7);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 7;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetHairColor(Mage, 7);
		CustomCharacter->CharacterInfo.CustomizingInfo.HairColorNum = 7;
	}
}

void UWC_HairColorWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// �κ��丮 �Ҹ�
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
