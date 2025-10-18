// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "C_SMSEnum.h"
#include "C_SMSStruct.generated.h"

class AC_PlayerCharacter;
class UDA_ItemData;
class UC_SMSSkill;
class AC_SMSSkillINS;

//유저 정보
USTRUCT(BlueprintType)
struct FUserInfo : public FTableRowBase		// 유저 기본정보
{
	GENERATED_BODY();

	UPROPERTY()
	FString ID = "";

	UPROPERTY()
	FString PassWord = "";

	FGuid GUID;
};

//커스터마이징 정보
USTRUCT(BlueprintType)
struct FCustomizingInfo : public FTableRowBase		// 캐릭터 기본정보
{
	GENERATED_BODY()

	UPROPERTY()
	int ArmorColorNum = 0;

	UPROPERTY()
	int EyeColorNum = 0;

	UPROPERTY()
	int EyelashColorNum = 0;

	UPROPERTY()
	float FaceColorNum = 0.0f;

	UPROPERTY()
	int HairColorNum = 0;

	UPROPERTY()
	int WeaponColorNum = 0;
};

//캐릭터 정보
USTRUCT(BlueprintType)
struct FCharacterInfo : public FTableRowBase		// 캐릭터 기본정보
{
	GENERATED_BODY()

	//유저 아이디
	UPROPERTY()
	FString UserID = "";

	//캐릭터 이름
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString CharacterName = TEXT("MyName");

	//현재 레벨
	UPROPERTY()
	int32 Level = 1;

	//현재 경험치
	UPROPERTY()
	float CurExp = 0;

	//최대 경험치
	UPROPERTY()
	float MaxExp = 2;

	//최대 체력
	UPROPERTY()
	float Maxhp = 5000.0f;

	//최대 마나
	UPROPERTY()
	float Maxmp = 100.0f;

	//최대 마나
	UPROPERTY()
	float Curhp = 5000.0f;

	//현재 마나
	UPROPERTY()
	float Curmp = 0.0f;

	// 공격력
	UPROPERTY()
	float Damage = 100.0f;

	// 방어력
	UPROPERTY()
	float Defense = 5.0f;

	//스킬포인트
	UPROPERTY()
	int SkillPoint = 0;

	// 캐릭터 종류
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPlayerJob Job = EPlayerJob::NONE;

	// 커스터마이징
	UPROPERTY()
	FCustomizingInfo CustomizingInfo;
};

//적 정보
USTRUCT(BlueprintType)
struct FEnemyInfo : public FTableRowBase
{
	GENERATED_BODY()		

	//이름
	UPROPERTY()
	FString Name = "비어있음";

	//최대 체력
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Maxhp = 100.0f;

	// 현재 체력
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Curhp = 100.0f;

	//전체 그로기 게이지
	float MaxGroggy = 100.0f;

	//현재 그로기 게이지
	float CurGroggy = 100.0f;

	// 공격력
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage = 10.0f;

	// 방어력
	UPROPERTY()
	float Defense = 5.0f;	

	// 최대마나
	UPROPERTY()
	float MaxMp = 1000.0f;

	// 현재마나
	UPROPERTY()
	float CurMp = 0.0f;

	// 플레이어에게 줄 EXP
	UPROPERTY()
	unsigned int DropExp = 1;


	// 캐릭터 종류
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPlayerJob Job = EPlayerJob::NONE;
};

// 아이템 정보
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	// 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name = "";

	// 가격
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Price = 0.0f;

	// 아이템 타입
	UPROPERTY()
	EItemType ItemType = EItemType::NONE;

	// 아이템 사진
	UPROPERTY()
	UTexture2D* Icon = nullptr;

	// 아이템 설명
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

};

// 인벤토리 슬롯 구조체
USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDA_ItemData* ItemData = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ItemQuantity = 0;

	//아이템 강화 단계
	UPROPERTY()
	int32 Grade = 0;

	bool IsEmpty() const 
	{ 
		return ItemData == nullptr; 
	}
};

//파티 정보
USTRUCT(BlueprintType)
struct FPartyInfo : public FTableRowBase
{
	GENERATED_BODY()

	//파티 가입 여부
	UPROPERTY()
	bool InParty = false;

	//파티 GUID
	UPROPERTY()
	FGuid PartyGUID;

	//파티장
	UPROPERTY()
	AC_PlayerCharacter* PartyOwner;

	//파티원들
	UPROPERTY()
	TArray<AC_PlayerCharacter*> PartyPlayers;

};

//파티 정보
USTRUCT(BlueprintType)
struct FPartyData : public FTableRowBase
{
	GENERATED_BODY()
	//파티 가입 여부
	UPROPERTY()
	bool InParty = false;

	//파티 GUID
	UPROPERTY()
	FGuid PartyGUID;

	//파티장 이름
	UPROPERTY()
	FString PartyOwnerName;

	//파티원들 이름
	UPROPERTY()
	TArray<FString> PartyPlayersName;
};

USTRUCT(BlueprintType)
struct FQuestData : public FTableRowBase
{
	GENERATED_BODY()

	//퀘스트 제목
	UPROPERTY()
	FText QuestTitle;

	//퀘스트 내용
	UPROPERTY()
	FText QuestInfo;

	//퀘스트 완료조건
	UPROPERTY()
	FText CompletedCondition;

	//보상
	UPROPERTY()
	FText Reward;

	//퀘스트 완료대화
	UPROPERTY()
	FText FinishConversation;

	//퀘스트 진행중대화
	UPROPERTY()
	FText Questting;

	//퀘스트 진행 상태
	UPROPERTY()
	EQuestState QuestState;

	//퀘스트받은 캐릭터
	UPROPERTY()
	FString OwnerName;

	//퀘스트 진행도
	UPROPERTY()
	int CurNum = 0;
};

// 스킬 데이터
USTRUCT(BlueprintType)
struct FSkillData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UC_SMSSkill> SkillData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AC_SMSSkillINS> SkillInstanceClass = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AC_SMSSkillINS> SkillInstance = nullptr;
};

USTRUCT(BlueprintType)
struct FSkillList
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSkillData> Skills;
};