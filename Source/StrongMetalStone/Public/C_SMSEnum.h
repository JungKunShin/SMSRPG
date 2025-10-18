#pragma once

#include "CoreMinimal.h"
#include "C_SMSEnum.generated.h"

UENUM()
enum class EInputMode : uint8 //�÷��̾� ����
{
	UIOnly UMETA(DisplayName = "UIOnly"),

	GameAndUI    UMETA(DisplayName = "GameAndUI"),

	GameOnly  UMETA(DisplayName = "GameOnly")
};

UENUM()
enum class EPlayerJob : uint8 // ĳ���� Ÿ��
{
	NONE UMETA(DisplayName = "NONE"),

	//����
	WARRIOR UMETA(DisplayName = "WARRIOR"),

	//������
	MAGE    UMETA(DisplayName = "MAGE"),

	//����
	HEALER  UMETA(DisplayName = "HEALER"),

	// ����
	BOSS	UMETA(DisplayName = "BOSS"),
};

UENUM()
enum class EItemType : uint8 // ������ Ÿ��
{
	NONE UMETA(DisplayName = "None"),

	// ����
	WEAPON UMETA(DisplayName = "WEAPON"),

	// Armor ����
	// ����
	HELMET UMETA(DisplayName = "HELMET"),

	// ����
	UPPERARMOR UMETA(DisplayName = "UPPERARMOR"),

	// ����
	LOWERARMOR UMETA(DisplayName = "LOWERARMOR"),

	// �Ź�
	SHOES UMETA(DisplayName = "SHOES"),

	// �Ҹ� ������
	CONSUMABLE UMETA(DisplayName = "CONSUMABLE")
};

UENUM(BlueprintType)
enum class EItemSubType : uint8
{
	NONE,
	POTION
};

// ���� Ÿ��
UENUM(BlueprintType)
enum class ESlotType : uint8
{
	NONE,
	HELMET,
	UPPERARMOR,
	LOWERARMOR,
	SHOES,
	WEAPON,
	Potion1,
	Potion2,
	Equipment
};

UENUM()
enum class ESkillType : uint8 //��ų Ÿ��
{
	ONCE, // �ܹ߼� ��ų
	HOLD  // Ȧ�� ��ų
};

UENUM()
enum class EEffectType : uint8 //�����̻� Ÿ��
{
	POSITIVE,	// ����
	NEGATIVE,	// �����
	NORMAL		// �⺻
};

UENUM()
enum class EProgressBarType : uint8		// ProgressBar Ÿ��
{
	EXP		UMETA(DisplayName = "Exp"),
	HEALTH	UMETA(DisplayName = "Health"),
	MANA	UMETA(DisplayName = "Mana"),
	BOSS	UMETA(DisplayName = "Boss")
};

UENUM()
enum class EOverHeat :uint8
{
	ZERO,
	LOWHEAT,
	MIDDLEHEAT,
	HIGHHEAT
};

UENUM()
enum class EQuestState :uint8
{
	None,
	Questing,
	Completed,
	End
};

// ���� ���
UENUM()
enum class EShopMode :uint8
{
	SELL,	// �Ǹ�
	BUY		// ����
};

// ��ų ��� Ű
UENUM(BlueprintType)
enum class ESkillInput : uint8
{
	NONE,
	SKILL1,  // Ű 1
	SKILL2,
	SKILL3,
	SKILL4,
	SKILLQ,
	SKILLE,
	DASH,
	ATTACK,
	SHIELD,
	HORSE
};

// Ÿ��Ʋ ī�޶� ����
UENUM()
enum class ECameraViewPoint :uint8
{
	Pawn,
	Character,
	Bag
};

UENUM(BlueprintType)
enum class EVolumeType : uint8
{
	Master     UMETA(DisplayName = "Master"),
	BGM        UMETA(DisplayName = "BGM"),
	Effect     UMETA(DisplayName = "Effect"),
	UI         UMETA(DisplayName = "UI")
};