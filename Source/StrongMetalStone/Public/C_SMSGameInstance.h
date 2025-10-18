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
	FUserInfo UserInfo; //���� ��������
	FCharacterInfo CharacterInfo; // ���� ĳ��������
	FPartyInfo PartyInfo; //���� ��Ƽ����
	FPartyData PartyData;

	TArray<FUserInfo> UserInfoDatas; //���� ���� ����
	TArray<FCharacterInfo> CharacterInfoDatas; //ĳ���� ���� ����
	TArray<AC_SMSQuest*> QuestDatas; //����Ʈ ����
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

	// ��ü ��ų ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UDA_SkillList> AllSkillList;

	// ��ü ������ ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TObjectPtr<UDA_ItemDataList> AllItemList;

	// �ε� ���� �ν��Ͻ�
	UPROPERTY(BlueprintReadWrite)
	class UWC_LoadingWidget* LoadingWidget;

	// �ε� ���� Ŭ����
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> LoadingWidgetClass;

	FTimerHandle UITH;
};
