#include "Widget/Ingame/WC_QuestWidget.h"
#include "Widget/WC_SMSButton.h"

#include "HUD/C_WorldHUD.h"
#include "Components/TextBlock.h"
#include "Component/C_InventoryComponent.h"

#include "Character/C_PlayerCharacter.h"
#include "Quest/C_SMSQuest.h"
#include "C_SMSGameInstance.h"
#include "PlayerController/C_WorldPlayerController.h"

void UWC_QuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CastWHUD(GetMyHUD())->SetInputMode(EInputMode::UIOnly, true); // 마우스 보여주고, UIOnlyMode
	CastWPC(GetMyPC())->DisableInput(CastWPC(GetMyPC()));
	// 거절 버튼 초기화
	DenyButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/00_PictoIcons/btn_icon_clear.btn_icon_clear")), FVector3f(1.f, 1.f, 1.f));
	// 거절 버튼에 함수 바인딩
	DenyButton->OnButtonClicked.AddDynamic(this, &UWC_QuestWidget::OnDenyButtonClicked);
	// 수락 버튼 초기화
	AcceptButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/00_PictoIcons/btn_icon_check.btn_icon_check")), FVector3f(1.f, 1.f, 1.f));
	// 수락 버튼에 함수 바인딩
	AcceptButton->OnButtonClicked.AddDynamic(this, &UWC_QuestWidget::OnAcceptButtonClicked);
	// 보상 버튼 초기화
	RewardButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/00_PictoIcons/btn_icon_moneybag.btn_icon_moneybag")), FVector3f(1.f, 1.f, 1.f));
	// 보상 버튼에 함수 바인딩
	RewardButton->OnButtonClicked.AddDynamic(this, &UWC_QuestWidget::OnRewardButtonClicked);
	// 포기 버튼 초기화
	GiveUpButton->Init(LoadObject<UTexture2D>(nullptr, TEXT("/Game/Image/00_PictoIcons/btn_icon_caution.btn_icon_caution")), FVector3f(1.f, 1.f, 1.f));
	// 포기 버튼에 함수 바인딩
	GiveUpButton->OnButtonClicked.AddDynamic(this, &UWC_QuestWidget::OnGiveUpButtonClicked);
	/*SetText();*/ // 처음 문구들 초기화

	AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());
	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (BeginSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, BeginSound, Character->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}
}

void UWC_QuestWidget::OnDenyButtonClicked()
{
	// 퀘스트 거절
	AC_WorldHUD* WorldHUD = Cast<AC_WorldHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());
	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (CancelSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, CancelSound, Character->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}

	if (WorldHUD)
	{
		WorldHUD->SetQuestWidgetVisible(false);
		CastWHUD(GetMyHUD())->SetInputMode(EInputMode::GameOnly, false); // 마우스 끄고, GameOnlyMode
	}
	CastWPC(GetMyPC())->EnableInput(CastWPC(GetMyPC()));
}

void UWC_QuestWidget::OnAcceptButtonClicked()
{	
	// 퀘스트 수락
	AC_WorldHUD* WorldHUD = Cast<AC_WorldHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());
	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (AcceptSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, AcceptSound, Character->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}

	if (WorldHUD)
	{
		WorldHUD->SetQuestWidgetVisible(false);
		CastWHUD(GetMyHUD())->SetInputMode(EInputMode::GameOnly, false); // 마우스 끄고, GameOnlyMode

		if (Character)
		{
			if (Character->QuestArr.IsEmpty())
			{
				WorldHUD->SetQuestingWidgetVisible(true);
			}
			CurQuest->QuestData.QuestState = EQuestState::Questing; // 퀘스트 시작	
			CurQuest->QuestData.OwnerName = CastWCharacter(GetMyCharacter())->CharacterInfo.CharacterName;
			Character->QuestArr.Add(CurQuest);
			CastWPC(GetMyPC())->ServerAddQuestToCSV(CurQuest->QuestData);
			CastWGI(GetMyGI())->QuestDatas.Add(CurQuest);
			/*Character->ServerAcceptQuest(CurQuest);*/
		}
		WorldHUD->AddQuestText(CurQuest);
	}
	CastWPC(GetMyPC())->EnableInput(CastWPC(GetMyPC()));
}

void UWC_QuestWidget::OnRewardButtonClicked()
{
	// 퀘스트 보상획득
	AC_WorldHUD* WorldHUD = Cast<AC_WorldHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());

	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (RewardSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, RewardSound, Character->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}

	if (WorldHUD)
	{
		WorldHUD->SetQuestWidgetVisible(false);
		WorldHUD->SetInputMode(EInputMode::GameOnly, false); // 마우스 끄고, GameOnlyMode

	}
	if (Character)
	{
		for (int i = 0; i < Character->QuestArr.Num(); ++i)
		{
			if (Character->QuestArr[i] == CurQuest)
			{
				Character->QuestArr.Remove(CurQuest); // 퀘스트 종료로 인해, 퀘스트 배열안에서 제거
				CastWGI(GetMyGI())->QuestDatas.Remove(CurQuest);

				WorldHUD->RemoveQuestText(i);
				if (CurQuest->GetClass() == CastWGI(GetMyGI())->QuestManager->PickUp)
				{
					CastWGI(GetMyGI())->QuestManager->OnPickUp = false;
				}
				else if (CurQuest->GetClass() == CastWGI(GetMyGI())->QuestManager->KillMonster)
				{
					CastWGI(GetMyGI())->QuestManager->OnKillMonster = false;
				}
				else if (CurQuest->GetClass() == CastWGI(GetMyGI())->QuestManager->DefeatBoss)
				{
					CastWGI(GetMyGI())->QuestManager->OnDefeatBoss = false;
					Character->InventoryComponent->AddGold(1000);
					Character->InventoryComponent->AddItem(DarkSword,1);
				}
				CurQuest->QuestData.QuestState = EQuestState::End;
				DeleteQuestCSV(CurQuest->QuestData);
				AddQuestToCSV(CurQuest->QuestData);
				break;
			}
		}
	}
	/*WorldHUD->SetQuestingWidgetVisible(true);*/
	CastWPC(GetMyPC())->EnableInput(CastWPC(GetMyPC()));
	// 보상획득 함수 넣어주기
	// bool값 만들어주기
}

void UWC_QuestWidget::OnGiveUpButtonClicked()
{
	// 퀘스트 포기
	AC_WorldHUD* WorldHUD = Cast<AC_WorldHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	AC_PlayerCharacter* Character = CastWCharacter(GetMyCharacter());

	AC_WorldPlayerController* WorldController = CastWPC(GetMyPC());
	if (!WorldController)return;

	if (GiveUpSound)// 인벤토리 소리
	{
		UGameplayStatics::PlaySoundAtLocation(this, GiveUpSound, Character->GetActorLocation(), WorldController->SoundManager->EffectVolume, 1.0f);
	}

	if (WorldHUD)
	{
		WorldHUD->SetQuestWidgetVisible(false);
		WorldHUD->SetInputMode(EInputMode::GameOnly, false); // 마우스 끄고, GameOnlyMode

	}
	if (Character)
	{
		for (int i = 0; i < Character->QuestArr.Num(); ++i)
		{
			if (Character->QuestArr[i] == CurQuest)
			{
				
				Character->QuestArr.Remove(CurQuest); // 퀘스트 종료로 인해, 퀘스트 배열안에서 제거
				WorldHUD->RemoveQuestText(i);				
				DeleteQuestCSV(CurQuest->QuestData);
				break;
			}
		}
	}
	CastWPC(GetMyPC())->EnableInput(CastWPC(GetMyPC()));
}

void UWC_QuestWidget::SetText(AC_SMSQuest* Quest)
{

	if (TEXT_QuestTitle)
	{
		TEXT_QuestTitle->SetText(Quest->QuestData.QuestTitle);
	}
	if (TEXT_QuestReward)
	{
		TEXT_QuestReward->SetText(Quest->QuestData.Reward);
	}
	if (TEXT_QuestCompletedCondition)
	{
		TEXT_QuestCompletedCondition->SetText(Quest->QuestData.CompletedCondition);
	}

	if (Quest->QuestData.QuestState == EQuestState::None)
	{
		if (TEXT_QuestInfo)
		{
			TEXT_QuestInfo->SetText(Quest->QuestData.QuestInfo);
		}
		if (TEXT_Accept)
		{
			TEXT_Accept->SetVisibility(ESlateVisibility::Visible);
		}
		if (AcceptButton)
		{
			AcceptButton->SetVisibility(ESlateVisibility::Visible);
		}
		if (TEXT_Reward)
		{
			TEXT_Reward->SetVisibility(ESlateVisibility::Hidden);
		}
		if (RewardButton)
		{
			RewardButton->SetVisibility(ESlateVisibility::Hidden);
		}
		if (TEXT_GiveUp)
		{
			TEXT_GiveUp->SetVisibility(ESlateVisibility::Hidden);
		}
		if (GiveUpButton)
		{
			GiveUpButton->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else if (Quest->QuestData.QuestState == EQuestState::Questing)
	{
		if (TEXT_QuestInfo)
		{
			TEXT_QuestInfo->SetText(Quest->QuestData.Questting);
		}
		if (TEXT_Accept)
		{
			TEXT_Accept->SetVisibility(ESlateVisibility::Hidden);
		}
		if (AcceptButton)
		{
			AcceptButton->SetVisibility(ESlateVisibility::Hidden);
		}
		if (TEXT_Reward)
		{
			TEXT_Reward->SetVisibility(ESlateVisibility::Hidden);
		}
		if (RewardButton)
		{
			RewardButton->SetVisibility(ESlateVisibility::Hidden);
		}
		if (TEXT_Deny)
		{
			TEXT_Deny->SetText(FText::FromString(TEXT("닫기")));
		}
		if (TEXT_GiveUp)
		{
			TEXT_GiveUp->SetVisibility(ESlateVisibility::Visible);
		}
		if (GiveUpButton)
		{
			GiveUpButton->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else if (Quest->QuestData.QuestState == EQuestState::Completed)
	{
		if (TEXT_QuestInfo)
		{
			TEXT_QuestInfo->SetText(Quest->QuestData.FinishConversation);
		}
		if (TEXT_Reward)
		{
			TEXT_Reward->SetVisibility(ESlateVisibility::Visible);
		}
		if (RewardButton)
		{
			RewardButton->SetVisibility(ESlateVisibility::Visible);
		}
		if (TEXT_Accept)
		{
			TEXT_Accept->SetVisibility(ESlateVisibility::Hidden);
		}
		if (AcceptButton)
		{
			AcceptButton->SetVisibility(ESlateVisibility::Hidden);
		}
		if (TEXT_Deny)
		{
			TEXT_Deny->SetText(FText::FromString(TEXT("닫기")));
		}
		if (TEXT_GiveUp)
		{
			TEXT_GiveUp->SetVisibility(ESlateVisibility::Hidden);
		}
		if (GiveUpButton)
		{
			GiveUpButton->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	CurQuest = Quest;

}
