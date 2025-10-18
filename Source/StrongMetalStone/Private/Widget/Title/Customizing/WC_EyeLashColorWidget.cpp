// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_EyeLashColorWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_Warrior.h"
#include "Character/C_Mage.h"
#include "HUD/C_TitleHUD.h"
#include "PlayerController/C_TitlePlayerController.h"

void UWC_EyeLashColorWidget::NativeConstruct()
{
	// ���� ��ư �ʱ�ȭ
	RedButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// ���� ��ư�� �Լ� ���ε�
	RedButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnRedButtonClicked);
	// �ʷ� ��ư �ʱ�ȭ
	GreenButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// �ʷ� ��ư�� �Լ� ���ε�
	GreenButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnGreenButtonClicked);
	// ������ ��ư �ʱ�ȭ
	OriginalButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// ������ ��ư�� �Լ� ���ε�
	OriginalButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnOriginalButtonClicked);
	// ��� ��ư �ʱ�ȭ
	WhiteButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// ��� ��ư�� �Լ� ���ε�
	WhiteButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnWhiteButtonClicked);
	// �Ķ��� ��ư �ʱ�ȭ
	BlueButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// �Ķ��� ��ư�� �Լ� ���ε�
	BlueButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnBlueButtonClicked);
	// ����� ��ư �ʱ�ȭ
	YellowButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// ����� ��ư�� �Լ� ���ε�
	YellowButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnYellowButtonClicked);
	// û�ϻ� ��ư �ʱ�ȭ
	CyanButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// û�ϻ� ��ư�� �Լ� ���ε�
	CyanButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnCyanButtonClicked);
	// ����Ÿ�� ��ư �ʱ�ȭ
	MagentaButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_eyelash.icon_eyelash")), FVector3f(1.f, 1.f, 1.f));
	// ����Ÿ�� ��ư�� �Լ� ���ε�
	MagentaButton->OnButtonClicked.AddDynamic(this, &UWC_EyeLashColorWidget::OnMagentaButtonClicked);

}

void UWC_EyeLashColorWidget::OnRedButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 2);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 2;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 2);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 2;
	}
}

void UWC_EyeLashColorWidget::OnGreenButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 1);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 1;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 1);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 1;
	}
}

void UWC_EyeLashColorWidget::OnOriginalButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 0);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 0;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 0);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 0;
	}
}

void UWC_EyeLashColorWidget::OnWhiteButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 3);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 3;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 3);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 3;
	}
}

void UWC_EyeLashColorWidget::OnBlueButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 4);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 4;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 4);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 4;
	}
}

void UWC_EyeLashColorWidget::OnYellowButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 5);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 5;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 5);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 5;
	}
}

void UWC_EyeLashColorWidget::OnCyanButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 6;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 6;
	}
}

void UWC_EyeLashColorWidget::OnMagentaButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�

	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);
	AC_Mage* Mage = Cast<AC_Mage>(CustomCharacter);

	if (Warrior)
	{
		UC_CustomizingManager::SetEyeLashColor(Warrior, 7);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 7;
	}
	else if (Mage)
	{
		UC_CustomizingManager::SetEyeLashColor(Mage, 7);
		CustomCharacter->CharacterInfo.CustomizingInfo.EyelashColorNum = 7;
	}
}

void UWC_EyeLashColorWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// �κ��丮 �Ҹ�
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
