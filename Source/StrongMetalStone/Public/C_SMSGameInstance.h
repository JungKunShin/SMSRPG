#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Manager/C_EffectManager.h"
#include "Manager/C_QuestManager.h"
#include "FrameWork.h"
#include "C_SMSGameInstance.generated.h"

class UDA_SkillList;
class UDA_ItemDataList;
class AC_DungeonGate;

UCLASS()
class STRONGMETALSTONE_API UC_SMSGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	virtual void Init()override;

#pragma region CSV_ID
public:
	void OpenDungeonLevel(const FString& DungeonName, int32 PortNum, AC_PlayerCharacter* Player, AC_DungeonGate* Gate);

	void OpenLevel(int32 PortNum, FPartyInfo _PartyInfo);

	void CheckID(FUserInfo _UserInfo);

	void SetLoadUserInfoFromCSV();

	void DelayUI();

#pragma endregion
public:
	FUserInfo UserInfo; //개인 유저정보
	FCharacterInfo CharacterInfo; // 개인 캐릭터정보
	FPartyInfo PartyInfo; //개인 파티정보
	FPartyData PartyData;

	TArray<FUserInfo> UserInfoDatas; //유저 정보 모음
	TArray<FCharacterInfo> CharacterInfoDatas; //캐릭터 정보 모음
	TArray<AC_SMSQuest*> QuestDatas; //퀘스트 모음
	TMap<int32,unsigned int> ExpDatas;

	UPROPERTY()
	AC_EffectManager* EffectManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager")
	TSubclassOf<AC_EffectManager> EffectManagerClass;	 

	UPROPERTY()
	AC_QuestManager* QuestManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Manager")
	TSubclassOf<AC_QuestManager> QuestManagerClass;

	UPROPERTY()
	AC_PlayerCharacter* MyCharacter;

	// 전체 스킬 데이터 저장
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UDA_SkillList> AllSkillList;

	// 전체 아이템 데이터 저장
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UDA_ItemDataList> AllItemList;

	// 로딩 위젯 인스턴스
	UPROPERTY(BlueprintReadWrite)
	class UWC_LoadingWidget* LoadingWidget;

	// 로딩 위젯 클래스
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> LoadingWidgetClass;

	FTimerHandle UITH;
};
