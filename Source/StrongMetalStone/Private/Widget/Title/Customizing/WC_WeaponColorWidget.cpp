// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/Customizing/WC_WeaponColorWidget.h"
#include "Widget/WC_SMSButton.h"
#include "Character/C_Warrior.h"
#include "HUD/C_TitleHUD.h"
#include "PlayerController/C_TitlePlayerController.h"

void UWC_WeaponColorWidget::NativeConstruct()
{
	// ���� ��ư �ʱ�ȭ
	RedButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_weapon.icon_weapon")), FVector3f(1.f, 1.f, 1.f));
	// ���� ��ư�� �Լ� ���ε�
	RedButton->OnButtonClicked.AddDynamic(this, &UWC_WeaponColorWidget::OnRedButtonClicked);
	// �ʷ� ��ư �ʱ�ȭ
	GreenButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_weapon.icon_weapon")), FVector3f(1.f, 1.f, 1.f));
	// �ʷ� ��ư�� �Լ� ���ε�
	GreenButton->OnButtonClicked.AddDynamic(this, &UWC_WeaponColorWidget::OnGreenButtonClicked);
	// ������ ��ư �ʱ�ȭ
	OriginalButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/Custom_Icon/icon_weapon.icon_weapon")), FVector3f(1.f, 1.f, 1.f));
	// ������ ��ư�� �Լ� ���ε�
	OriginalButton->OnButtonClicked.AddDynamic(this, &UWC_WeaponColorWidget::OnOriginalButtonClicked);
}

void UWC_WeaponColorWidget::OnRedButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�
	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);

	if (Warrior)
	{
		CustomCharacter->ButtonColor(FLinearColor::Red, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.WeaponColorNum = 2;
	}
}

void UWC_WeaponColorWidget::OnGreenButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�
	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);

	if (Warrior)
	{
		CustomCharacter->ButtonColor(FLinearColor::Green, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.WeaponColorNum = 1;
	}
}

void UWC_WeaponColorWidget::OnOriginalButtonClicked()
{
	OnButtonSound(); //��ư �Ҹ�
	CustomCharacter = Cast<AC_TitleHUD>(GetMyHUD())->CustomChar;
	AC_Warrior* Warrior = Cast<AC_Warrior>(CustomCharacter);

	if (Warrior)
	{
		CustomCharacter->ButtonColor(FLinearColor::White, 6);
		CustomCharacter->CharacterInfo.CustomizingInfo.WeaponColorNum = 0;
	}
}

void UWC_WeaponColorWidget::OnButtonSound()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// �κ��丮 �Ҹ�
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}
