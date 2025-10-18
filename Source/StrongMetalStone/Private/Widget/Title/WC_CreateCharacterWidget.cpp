// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/Title/WC_CreateCharacterWidget.h"
#include "Widget/WC_SMSButton.h"
#include "HUD/C_TitleHUD.h"
#include "GameMode/C_TitleGameMode.h"
#include "Character/C_Warrior.h"
#include "Character/C_Mage.h"
#include "C_SMSGameInstance.h"

#include "PlayerController/C_TitlePlayerController.h"

void UWC_CreateCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//전사
	if (Button_Warrior)
	{
		// 버튼 초기화
		Button_Warrior->Init(FText::FromString(TEXT("전사")), 20);

		// 함수 이벤트 바인딩
		Button_Warrior->OnButtonClicked.AddDynamic(this, &UWC_CreateCharacterWidget::OnButtonWarrior);
	}

	//마법사
	if (Button_Mage)
	{
		// 버튼 초기화
		Button_Mage->Init(FText::FromString(TEXT("마법사")), 20);

		// 함수 이벤트 바인딩
		Button_Mage->OnButtonClicked.AddDynamic(this, &UWC_CreateCharacterWidget::OnButtonMage);
	}

	//결정
	if (Button_Select)
	{
		// 버튼 초기화
		Button_Select->Init(FText::FromString(TEXT("결정")), 20);

		// 함수 이벤트 바인딩
		Button_Select->OnButtonClicked.AddDynamic(this, &UWC_CreateCharacterWidget::OnButtonSelect);
	}

	//뒤로
	if (Button_Back)
	{
		// 버튼 초기화
		Button_Back->Init(FText::FromString(TEXT("뒤로")), 20);

		// 함수 이벤트 바인딩
		Button_Back->OnButtonClicked.AddDynamic(this, &UWC_CreateCharacterWidget::OnButtonBack);
	}
}

//워리어버튼
void UWC_CreateCharacterWidget::OnButtonWarrior()
{
	CharacterSpawn(EPlayerJob::WARRIOR);

	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}

//마법사버튼
void UWC_CreateCharacterWidget::OnButtonMage()
{
	CharacterSpawn(EPlayerJob::MAGE);

	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}

//결정버튼
void UWC_CreateCharacterWidget::OnButtonSelect()
{
	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}

	if (!SpawnCharacter)
	{
		//캐릭터 직업을 선택해달라는 경고메세지
		Cast<AC_TitleHUD>(GetMyHUD())->SetWarningMessage(ERROR_JOB);
		return;
	}
	SpawnCharacter->CharacterInfo.UserID = CastWGI(GetMyGI())->UserInfo.ID;

	Cast<AC_TitleHUD>(GetMyHUD())->CustomChar = SpawnCharacter;
	Cast<AC_TitleHUD>(GetMyHUD())->SetTitleWidgetSwitcherIndex(3);
}

//뒤로버튼
void UWC_CreateCharacterWidget::OnButtonBack()
{
	Cast<AC_TitleHUD>(GetMyHUD())->SetTitleWidgetSwitcherIndex(1);

	AC_TitlePlayerController* TitleController = Cast< AC_TitlePlayerController>(GetWorld()->GetFirstPlayerController());
	if (!TitleController)return;

	if (ButtonSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, ButtonSound, TitleController->GetPawn()->GetActorLocation(), TitleController->SoundManager->EffectVolume, 1.0f);
	}
}

void UWC_CreateCharacterWidget::CharacterSpawn(EPlayerJob Job)
{
	if (SpawnCharacter)GetWorld()->DestroyActor(SpawnCharacter);

	CurSelectJob = Job;
	TSubclassOf SpawnCharacterClass = WarriorClass;	


	switch (Job)
	{
	case EPlayerJob::NONE:
		break;
	case EPlayerJob::WARRIOR:
		SpawnCharacterClass = WarriorClass;
		break;
	case EPlayerJob::MAGE:
		SpawnCharacterClass = MageClass;
		break;
	default:
		break;
	}
	SpawnCharacter = GetWorld()->SpawnActor<AC_PlayerCharacter>(SpawnCharacterClass);

	if (!SpawnCharacter) return;
	SpawnCharacter->SetActorLocation(FVector(-3600.0f, -1300.0f, 620.0f));
	SpawnCharacter->SetActorRotation(FRotator(0.0f, -70.0f, 0.0f));
}

