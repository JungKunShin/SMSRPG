#pragma once

#include "CoreMinimal.h"
#include "C_SMSEnum.generated.h"

UENUM()
enum class EInputMode : uint8 //플레이어 직업
{
	UIOnly UMETA(DisplayName = "UIOnly"),

	GameAndUI    UMETA(DisplayName = "GameAndUI"),

	GameOnly  UMETA(DisplayName = "GameOnly")
};

UENUM()
enum class EPlayerJob : uint8 // 캐릭터 타입
{
	NONE UMETA(DisplayName = "NONE"),

	//전사
	WARRIOR UMETA(DisplayName = "WARRIOR"),

	//마법사
	MAGE    UMETA(DisplayName = "MAGE"),

	//힐러
	HEALER  UMETA(DisplayName = "HEALER"),

	// 보스
	BOSS	UMETA(DisplayName = "BOSS"),
};

UENUM()
enum class EItemType : uint8 // 아이템 타입
{
	NONE UMETA(DisplayName = "None"),

	// 무기
	WEAPON UMETA(DisplayName = "WEAPON"),

	// Armor 종류
	// 투구
	HELMET UMETA(DisplayName = "HELMET"),

	// 상의
	UPPERARMOR UMETA(DisplayName = "UPPERARMOR"),

	// 하의
	LOWERARMOR UMETA(DisplayName = "LOWERARMOR"),

	// 신발
	SHOES UMETA(DisplayName = "SHOES"),

	// 소모 아이템
	CONSUMABLE UMETA(DisplayName = "CONSUMABLE")
};

UENUM(BlueprintType)
enum class EItemSubType : uint8
{
	NONE,
	POTION
};

// 슬롯 타입
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
enum class ESkillType : uint8 //스킬 타입
{
	ONCE, // 단발성 스킬
	HOLD  // 홀드 스킬
};

UENUM()
enum class EEffectType : uint8 //상태이상 타입
{
	POSITIVE,	// 버프
	NEGATIVE,	// 디버프
	NORMAL		// 기본
};

UENUM()
enum class EProgressBarType : uint8		// ProgressBar 타입
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

// 상점 모드
UENUM()
enum class EShopMode :uint8
{
	SELL,	// 판매
	BUY		// 구매
};

// 스킬 사용 키
UENUM(BlueprintType)
enum class ESkillInput : uint8
{
	NONE,
	SKILL1,  // 키 1
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

// 타이틀 카메라 시점
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