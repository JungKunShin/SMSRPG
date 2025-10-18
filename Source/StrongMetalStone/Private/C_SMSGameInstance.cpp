#include "C_SMSGameInstance.h"
#include "C_SMSStruct.h"
#include "GameMode/C_WorldGameMode.h"
#include "PlayerController/C_SMSPlayerController.h"
#include "Actor/C_DungeonGate.h"
#include "Character/C_PlayerCharacter.h"
#include "Widget/Ingame/WC_LoadingWidget.h"
#include "PlayerController/C_WorldPlayerController.h"

void UC_SMSGameInstance::Init()
{

	Super::Init();
	
    EffectManager = NewObject<AC_EffectManager>(this, EffectManagerClass);		
	QuestManager = NewObject<AC_QuestManager>(this, QuestManagerClass);

	
	ExpDatas = GetLoadExpData();
	switch (CharacterInfo.Job)
	{
	case EPlayerJob::NONE:
		CharacterInfo.Curmp = 0;
		break;
	case EPlayerJob::WARRIOR:
		CharacterInfo.Curmp = 0;
		break;

	default:
		break;
	}

	GetWorld()->GetTimerManager().ClearTimer(UITH);
	GetWorld()->GetTimerManager().SetTimer(UITH, this, &UC_SMSGameInstance::DelayUI, 1.8f, false);
}

void UC_SMSGameInstance::SetLoadUserInfoFromCSV()
{
	UserInfoDatas = GetLoadUserInfoFromCSV();
}

void UC_SMSGameInstance::DelayUI()
{
	if (LoadingWidgetClass)
	{
	// 다음 프레임에 띄우기
		FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([this](float DeltaTime)
			{
				UWorld* World = GetWorld();
				if (World && World->IsGameWorld())
				{
					LoadingWidget = CreateWidget<UWC_LoadingWidget>(World, LoadingWidgetClass);
					if (LoadingWidget)
					{
						FString FieldName = FString(TEXT("WorldLevel"));
						FString DungeonName = FString(TEXT("OperaHouseLevel1"));
						FString WorldName = World->GetName();
						
						if (WorldName ==FieldName)
						{
							LoadingWidget->AddToViewport(9999);
							LoadingWidget->Init(false);
						}
						else if (WorldName == DungeonName)
						{
							LoadingWidget->AddToViewport(9999);
							LoadingWidget->Init(true);
						}


						GetWorld()->GetTimerManager().ClearTimer(UITH);
					}
				}

				return false; // 한 번만 실행
			}));

	}

}


void UC_SMSGameInstance::OpenDungeonLevel(const FString& DungeonName,int32 PortNum,AC_PlayerCharacter* Player,AC_DungeonGate* Gate)
{	
	//데디서버 생성
	MakeServer(DungeonName, PortNum);

	Gate->PortNum++;

	OpenLevel(PortNum, Player->PartyInfo);
}

void UC_SMSGameInstance::OpenLevel(int32 PortNum, FPartyInfo _PartyInfo)
{
	for (AC_PlayerCharacter* PartyPlayer : _PartyInfo.PartyPlayers)
	{
		Cast<AC_SMSPlayerController>((CastWCharacter(PartyPlayer)->GetController()))->IsExit = false;
		Cast<AC_SMSPlayerController>((CastWCharacter(PartyPlayer)->GetController()))->ClientOpenLevel(PortNum, _PartyInfo);
	}
}

void UC_SMSGameInstance::CheckID(FUserInfo _UserInfo)
{
	bool IsCheck = false;

	//아이디 중복체크
	for (FUserInfo SearchUserInfo : UserInfoDatas)
	{
		if (SearchUserInfo.ID == _UserInfo.ID)
		{
			IsCheck = true;
		}
		
	}

	if (IsCheck) 
	{
		//중복 아이디라고 하는 위젯띄우기
	}
	else
	{
		UserInfoDatas.Add(_UserInfo);
		Cast<AC_SMSPlayerController>(GetMyPC())->MultiLoadUserInfoFromCSV(UserInfoDatas);

		AddUserInfoToCSV(_UserInfo);	
	}
}



