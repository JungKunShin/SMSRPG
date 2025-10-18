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

//���� ����
USTRUCT(BlueprintType)
struct FUserInfo : public FTableRowBase		// ���� �⺻����
{
	GENERATED_BODY();

	UPROPERTY()
	FString ID = "";

	UPROPERTY()
	FString PassWord = "";

	FGuid GUID;
};

//Ŀ���͸���¡ ����
USTRUCT(BlueprintType)
struct FCustomizingInfo : public FTableRowBase		// ĳ���� �⺻����
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

//ĳ���� ����
USTRUCT(BlueprintType)
struct FCharacterInfo : public FTableRowBase		// ĳ���� �⺻����
{
	GENERATED_BODY()

	//���� ���̵�
	UPROPERTY()
	FString UserID = "";

	//ĳ���� �̸�
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString CharacterName = TEXT("MyName");

	//���� ����
	UPROPERTY()
	int32 Level = 1;

	//���� ����ġ
	UPROPERTY()
	float CurExp = 0;

	//�ִ� ����ġ
	UPROPERTY()
	float MaxExp = 2;

	//�ִ� ü��
	UPROPERTY()
	float Maxhp = 5000.0f;

	//�ִ� ����
	UPROPERTY()
	float Maxmp = 100.0f;

	//�ִ� ����
	UPROPERTY()
	float Curhp = 5000.0f;

	//���� ����
	UPROPERTY()
	float Curmp = 0.0f;

	// ���ݷ�
	UPROPERTY()
	float Damage = 100.0f;

	// ����
	UPROPERTY()
	float Defense = 5.0f;

	//��ų����Ʈ
	UPROPERTY()
	int SkillPoint = 0;

	// ĳ���� ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPlayerJob Job = EPlayerJob::NONE;

	// Ŀ���͸���¡
	UPROPERTY()
	FCustomizingInfo CustomizingInfo;
};

//�� ����
USTRUCT(BlueprintType)
struct FEnemyInfo : public FTableRowBase
{
	GENERATED_BODY()		

	//�̸�
	UPROPERTY()
	FString Name = "�������";

	//�ִ� ü��
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Maxhp = 100.0f;

	// ���� ü��
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Curhp = 100.0f;

	//��ü �׷α� ������
	float MaxGroggy = 100.0f;

	//���� �׷α� ������
	float CurGroggy = 100.0f;

	// ���ݷ�
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Damage = 10.0f;

	// ����
	UPROPERTY()
	float Defense = 5.0f;	

	// �ִ븶��
	UPROPERTY()
	float MaxMp = 1000.0f;

	// ���縶��
	UPROPERTY()
	float CurMp = 0.0f;

	// �÷��̾�� �� EXP
	UPROPERTY()
	unsigned int DropExp = 1;


	// ĳ���� ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EPlayerJob Job = EPlayerJob::NONE;
};

// ������ ����
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	// �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name = "";

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Price = 0.0f;

	// ������ Ÿ��
	UPROPERTY()
	EItemType ItemType = EItemType::NONE;

	// ������ ����
	UPROPERTY()
	UTexture2D* Icon = nullptr;

	// ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

};

// �κ��丮 ���� ����ü
USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UDA_ItemData* ItemData = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ItemQuantity = 0;

	//������ ��ȭ �ܰ�
	UPROPERTY()
	int32 Grade = 0;

	bool IsEmpty() const 
	{ 
		return ItemData == nullptr; 
	}
};

//��Ƽ ����
USTRUCT(BlueprintType)
struct FPartyInfo : public FTableRowBase
{
	GENERATED_BODY()

	//��Ƽ ���� ����
	UPROPERTY()
	bool InParty = false;

	//��Ƽ GUID
	UPROPERTY()
	FGuid PartyGUID;

	//��Ƽ��
	UPROPERTY()
	AC_PlayerCharacter* PartyOwner;

	//��Ƽ����
	UPROPERTY()
	TArray<AC_PlayerCharacter*> PartyPlayers;

};

//��Ƽ ����
USTRUCT(BlueprintType)
struct FPartyData : public FTableRowBase
{
	GENERATED_BODY()
	//��Ƽ ���� ����
	UPROPERTY()
	bool InParty = false;

	//��Ƽ GUID
	UPROPERTY()
	FGuid PartyGUID;

	//��Ƽ�� �̸�
	UPROPERTY()
	FString PartyOwnerName;

	//��Ƽ���� �̸�
	UPROPERTY()
	TArray<FString> PartyPlayersName;
};

USTRUCT(BlueprintType)
struct FQuestData : public FTableRowBase
{
	GENERATED_BODY()

	//����Ʈ ����
	UPROPERTY()
	FText QuestTitle;

	//����Ʈ ����
	UPROPERTY()
	FText QuestInfo;

	//����Ʈ �Ϸ�����
	UPROPERTY()
	FText CompletedCondition;

	//����
	UPROPERTY()
	FText Reward;

	//����Ʈ �Ϸ��ȭ
	UPROPERTY()
	FText FinishConversation;

	//����Ʈ �����ߴ�ȭ
	UPROPERTY()
	FText Questting;

	//����Ʈ ���� ����
	UPROPERTY()
	EQuestState QuestState;

	//����Ʈ���� ĳ����
	UPROPERTY()
	FString OwnerName;

	//����Ʈ ���൵
	UPROPERTY()
	int CurNum = 0;
};

// ��ų ������
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