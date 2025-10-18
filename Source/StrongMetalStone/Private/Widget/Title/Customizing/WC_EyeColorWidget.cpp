// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_EyeColorWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_Warrior.h"
#include "Character/C_Mage.h"
#include "HUD/C_TitleHUD.h"
#include "PlayerController/C_TitlePlayerController.h"

void UWC_EyeColorWidget::NativeConstruct()
{
	// ���� ��ư �ʱ�ȭ
	RedButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// ���� ��ư�� �Լ� ���ε�
	RedButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnRedButtonClicked);
	// �ʷ� ��ư �ʱ�ȭ
	GreenButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// �ʷ� ��ư�� �Լ� ���ε�
	GreenButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnGreenButtonClicked);
	// �Ķ� ��ư �ʱ�ȭ
	BlueButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// �Ķ� ��ư�� �Լ� ���ε�
	BlueButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnBlueButtonClicked);
	// ���� ��ư �ʱ�ȭ
	BlackButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// ���� ��ư�� �Լ� ���ε�
	BlackButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnBlackButtonClicked);
	// ȸ�� ��ư �ʱ�ȭ
	GrayButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// ȸ�� ��ư�� �Լ� ���ε�
	GrayButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnGrayButtonClicked);
	// ��� ��ư �ʱ�ȭ
	YellowButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// ��� ��ư�� �Լ� ���ε�
	YellowButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnYellowButtonClicked);
	// û�� ��ư �ʱ�ȭ
	CyanButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// û�� ��ư�� �Լ� ���ε�
	CyanButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnCyanButtonClicked);
	// ����Ÿ ��ư �ʱ�ȭ
	MagentaButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eye.icon_eye")), FVector3f(1.f, 1.f, 1.f));
	// ����Ÿ ��ư�� �Լ� ���ε�
	MagentaButton->OnButtonClicked.AddDynamic(this, &UWC_EyeColorWidget::OnMagentaButtonClicked);
}

void UWC_EyeColorWidget::OnRedButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 4);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 4;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 4);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 4;
	}
}

void UWC_EyeColorWidget::OnGreenButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 1);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 1;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 1);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 1;
	}
}

void UWC_EyeColorWidget::OnBlueButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 2);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 2;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 2);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 2;
	}
}

void UWC_EyeColorWidget::OnBlackButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 3);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 3;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 3);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 3;
	}
}

void UWC_EyeColorWidget::OnGrayButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 0);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 0;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 0);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 0;
	}
}

void UWC_EyeColorWidget::OnYellowButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 5);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 5;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 5);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 5;
	}
}

void UWC_EyeColorWidget::OnCyanButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 6;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 6;
	}
}

void UWC_EyeColorWidget::OnMagentaButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeColor(Warrior, 7);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 7;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeColor(Mage, 7);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyeColorNum = 7;
	}
}

void UWC_EyeColorWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// �κ��丮 �Ҹ�
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
