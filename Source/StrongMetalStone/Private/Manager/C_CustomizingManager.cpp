// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/C_CustomizingManager.h"
#include "Character/C_PlayerCharacter.h"
#include "Character/C_Warrior.h"
#include "Character/C_Mage.h"

void UC_CustomizingManager::SetCustom(AC_PlayerCharacter* _Character,FCustomizingInfo _CustomInfo)
{
	UC_CustomizingManager::SetArmorColor(_Character, _CustomInfo.ArmorColorNum);
	UC_CustomizingManager::SetEyeColor(_Character, _CustomInfo.EyeColorNum);
	UC_CustomizingManager::SetEyeLashColor(_Character, _CustomInfo.EyelashColorNum);
	UC_CustomizingManager::SetFaceColor(_Character, _CustomInfo.FaceColorNum);
	UC_CustomizingManager::SetHairColor(_Character, _CustomInfo.HairColorNum);
	UC_CustomizingManager::SetWeaponColor(_Character, _CustomInfo.WeaponColorNum);
}

void UC_CustomizingManager::SetArmorColor(AC_PlayerCharacter* _Character, int num)
{
	if (Cast<AC_Warrior>(_Character))
	{
		switch (num)
		{
		case 0://오리지날
			UC_CustomizingManager::BasicChest(_Character, FLinearColor::White, FLinearColor::White, FLinearColor::White);
			UC_CustomizingManager::BasicBelly(_Character, FLinearColor::White, FLinearColor::White, FLinearColor::White, FLinearColor::White);
			UC_CustomizingManager::BasicSkirt(_Character, FLinearColor::White, FLinearColor::White, FLinearColor::White, FLinearColor::White, FLinearColor::White);
			UC_CustomizingManager::BasicKnee(_Character, FLinearColor::White, FLinearColor::White, FLinearColor::White);
			break;
		case 1://아이언맨
			UC_CustomizingManager::BasicChest(_Character, FLinearColor::Red, FLinearColor::Red, FLinearColor::Yellow);
			UC_CustomizingManager::BasicBelly(_Character, FLinearColor::Red, FLinearColor::Yellow, FLinearColor::Yellow, FLinearColor(0.0f, 1.0f, 1.0f));
			UC_CustomizingManager::BasicSkirt(_Character, FLinearColor::Red, FLinearColor::Red, FLinearColor::Yellow, FLinearColor::Yellow, FLinearColor::Yellow);
			UC_CustomizingManager::BasicKnee(_Character, FLinearColor::Red, FLinearColor::Red, FLinearColor::Yellow);
			break;
		case 2://메뚜기
			UC_CustomizingManager::BasicChest(_Character, FLinearColor::Green, FLinearColor::Red, FLinearColor::Red);
			UC_CustomizingManager::BasicBelly(_Character, FLinearColor::Green, FLinearColor::Black, FLinearColor::Gray, FLinearColor::Green);
			UC_CustomizingManager::BasicSkirt(_Character, FLinearColor::Green, FLinearColor::Red, FLinearColor::Red, FLinearColor::Red, FLinearColor::Green);
			UC_CustomizingManager::BasicKnee(_Character, FLinearColor::Black, FLinearColor::Red, FLinearColor::Green);
			break;
		case 3://배트맨
			UC_CustomizingManager::BasicChest(_Character, FLinearColor::Black, FLinearColor::Black, FLinearColor::Black);
			UC_CustomizingManager::BasicBelly(_Character, FLinearColor::Black, FLinearColor::Black, FLinearColor::Black, FLinearColor::Yellow);
			UC_CustomizingManager::BasicSkirt(_Character, FLinearColor::Black, FLinearColor::Black, FLinearColor::Black, FLinearColor::Black, FLinearColor::Black);
			UC_CustomizingManager::BasicKnee(_Character, FLinearColor::Black, FLinearColor::Black, FLinearColor::Black);
			break;
		case 4://도라에몽
			UC_CustomizingManager::BasicChest(_Character, FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor::Red, FLinearColor(0.0f, 0.43f, 1.0f));
			UC_CustomizingManager::BasicBelly(_Character, FLinearColor::White, FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor::Yellow);
			UC_CustomizingManager::BasicSkirt(_Character, FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor(0.0f, 0.43f, 1.0f));
			UC_CustomizingManager::BasicKnee(_Character, FLinearColor(0.0f, 0.43f, 1.0f), FLinearColor::White, FLinearColor(0.0f, 0.43f, 1.0f));
			break;
		case 5://디바
			UC_CustomizingManager::BasicChest(_Character, FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f));
			UC_CustomizingManager::BasicBelly(_Character, FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(0.49f, 1.0f, 0.58f));
			UC_CustomizingManager::BasicSkirt(_Character, FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f));
			UC_CustomizingManager::BasicKnee(_Character, FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f), FLinearColor(1.0f, 0.34f, 0.9f));
			break;
		}
	}
	else if (Cast<AC_Mage>(_Character))
	{
		switch (num)
		{
		case 0://오리지날
			UC_CustomizingManager::BasicClothColor(_Character, FLinearColor::White, FLinearColor::White, FLinearColor(0.09765f, 0.160256f, 0.21f), FLinearColor(0.09765f, 0.160256f, 0.21f));
			UC_CustomizingManager::BasicDetailColor(_Character, FLinearColor(0.515f, 0.115875f, 0.397083f), FLinearColor(0.0f, 1.028571f, 2.0f), FLinearColor(0.05375f, 0.0f, 0.645f), FLinearColor::White);
			break;
		case 1://메뚜기마법사
			UC_CustomizingManager::BasicClothColor(_Character, FLinearColor::Green, FLinearColor::Red, FLinearColor::Green,FLinearColor::Green);
			UC_CustomizingManager::BasicDetailColor(_Character, FLinearColor::Red, FLinearColor::Green, FLinearColor::Red, FLinearColor::Red);
			break;
		case 2://태양신 라
			UC_CustomizingManager::BasicClothColor(_Character, FLinearColor(0.028282f,0.0f, 0.53125f), FLinearColor::Red, FLinearColor(1.0f, 0.909597f, 0.15831f), FLinearColor(1.0f, 0.909597f, 0.15831f));
			UC_CustomizingManager::BasicDetailColor(_Character, FLinearColor::Red, FLinearColor::Red, FLinearColor::Red, FLinearColor::Red);
			break;
		case 3://아프로디테
			UC_CustomizingManager::BasicClothColor(_Character, FLinearColor(1.0f, 0.0f, 0.8f), FLinearColor(1.0f, 0.020335f, 0.748049f), FLinearColor(1.0f, 0.380208f, 0.888492f), FLinearColor::White);
			UC_CustomizingManager::BasicDetailColor(_Character, FLinearColor::Yellow, FLinearColor(0.0f, 1.028571f, 2.0f), FLinearColor(0.05375f, 0.0f, 0.645f), FLinearColor::White);
			break;
		case 4://뿡뿡이
			UC_CustomizingManager::BasicClothColor(_Character, FLinearColor(1.0f, 0.430772f, 0.046875f), FLinearColor(1.0f, 0.43035f, 0.0f), FLinearColor(1.0f, 0.584772f, 0.036458f), FLinearColor(1.0f, 0.584772f, 0.036458f));
			UC_CustomizingManager::BasicDetailColor(_Character, FLinearColor::Green, FLinearColor::Yellow, FLinearColor(0.112793f, 0.65625f, 0.112793f), FLinearColor::Red);
			break;
		case 5://보노보노
			UC_CustomizingManager::BasicClothColor(_Character, FLinearColor(0.416667, 1.0f, 1.0f), FLinearColor(0.583333, 1.0f, 1.0f), FLinearColor(0.18085f, 0.9f, 1.0f), FLinearColor(0.18085f, 0.9f, 1.0f));
			UC_CustomizingManager::BasicDetailColor(_Character, FLinearColor(0.515f, 0.115875f, 0.397083f), FLinearColor(0.0f, 1.028571f, 2.0f), FLinearColor::White, FLinearColor::White);
			break;
		}
	}

}

void UC_CustomizingManager::SetEyeColor(AC_PlayerCharacter* _Character, int num)
{
	int MaterialNum = 8;
	if (Cast<AC_Mage>(_Character))
	{
		MaterialNum = 7;
	}

	switch (num)
	{
	case 0:
		_Character->ButtonColor(FLinearColor::Gray, MaterialNum);
		break;	
	case 1:
		_Character->ButtonColor(FLinearColor::Green, MaterialNum);
		break;
	case 2:
		_Character->ButtonColor(FLinearColor::Blue, MaterialNum);
		break;
	case 3:
		_Character->ButtonColor(FLinearColor::Black, MaterialNum);
		break;
	case 4:
		_Character->ButtonColor(FLinearColor::Red, MaterialNum);
		break;
	case 5:
		_Character->ButtonColor(FLinearColor::Yellow, MaterialNum);
		break;
	case 6:
		_Character->ButtonColor(FLinearColor(0.0f, 1.0f, 1.0f), MaterialNum);
		break;
	case 7:
		_Character->ButtonColor(FLinearColor(1.0f, 0.0f, 1.0f), MaterialNum);
		break;
	default:
		_Character->ButtonColor(FLinearColor::Gray, MaterialNum);
		break;
	}
}

void UC_CustomizingManager::SetEyeLashColor(AC_PlayerCharacter* _Character, int num)
{
	int MaterialNum = 10;
	if (Cast<AC_Mage>(_Character))
	{
		MaterialNum = 12;
	}

	switch (num)
	{
	case 0:
		_Character->ButtonColor(FLinearColor(0.001f, 0.001f, 0.001f), MaterialNum);
		break;
	case 1:
		_Character->ButtonColor(FLinearColor::Green, MaterialNum);
		break;
	case 2:
		_Character->ButtonColor(FLinearColor::Red, MaterialNum);
		break;
	case 3:
		_Character->ButtonColor(FLinearColor::White, MaterialNum);
		break;
	case 4:
		_Character->ButtonColor(FLinearColor::Blue, MaterialNum);
		break;
	case 5:
		_Character->ButtonColor(FLinearColor::Yellow, MaterialNum);
		break;
	case 6:
		_Character->ButtonColor(FLinearColor(0.0f, 1.0f, 1.0f), MaterialNum);
		break;
	case 7:
		_Character->ButtonColor(FLinearColor(1.0f, 0.0f, 1.0f), MaterialNum);
		break;
	default:
		_Character->ButtonColor(FLinearColor(0.001f, 0.001f, 0.001f), MaterialNum);
		break;
	}
}

void UC_CustomizingManager::SetFaceColor(AC_PlayerCharacter* _Character, float value)
{
	_Character->NewColor(value);
}

void UC_CustomizingManager::SetHairColor(AC_PlayerCharacter* _Character, int num)
{
	if (Cast<AC_Warrior>(_Character))
	{
		switch (num)
		{
		case 0:
			_Character->ButtonColor(FLinearColor::White, 7);
			break;
		case 1:
			_Character->ButtonColor(FLinearColor::Green, 7);
			break;
		case 2:
			_Character->ButtonColor(FLinearColor::Blue, 7);
			break;
		case 3:
			_Character->ButtonColor(FLinearColor::Black, 7);
			break;
		case 4:
			_Character->ButtonColor(FLinearColor::Red, 7);
			break;
		case 5:
			_Character->ButtonColor(FLinearColor::Yellow, 7);
			break;
		case 6:
			_Character->ButtonColor(FLinearColor(0.0f, 1.0f, 1.0f), 7);
			break;
		case 7:
			_Character->ButtonColor(FLinearColor(1.0f, 0.0f, 1.0f), 7);
			break;
		default:
			_Character->ButtonColor(FLinearColor::White, 7);
			break;
		}
	}
	else if (Cast<AC_Mage>(_Character))
	{
		switch (num)
		{
		case 0:
			_Character->ButtonColor(FLinearColor::Black, 9);
			_Character->ButtonColor(FLinearColor::Black, 13);
			break;
		case 1:
			_Character->ButtonColor(FLinearColor::Green, 9);
			_Character->ButtonColor(FLinearColor::Green, 13);
			break;
		case 2:
			_Character->ButtonColor(FLinearColor::Blue, 9);
			_Character->ButtonColor(FLinearColor::Blue, 13);
			break;
		case 3:
			_Character->ButtonColor(FLinearColor::White, 9);
			_Character->ButtonColor(FLinearColor::White, 13);
			break;
		case 4:
			_Character->ButtonColor(FLinearColor::Red, 9);
			_Character->ButtonColor(FLinearColor::Red, 13);
			break;
		case 5:
			_Character->ButtonColor(FLinearColor::Yellow, 9);
			_Character->ButtonColor(FLinearColor::Yellow, 13);
			break;
		case 6:
			_Character->ButtonColor(FLinearColor(0.0f, 1.0f, 1.0f), 9);
			_Character->ButtonColor(FLinearColor(0.0f, 1.0f, 1.0f), 13);
			break;
		case 7:
			_Character->ButtonColor(FLinearColor(1.0f, 0.0f, 1.0f), 9);
			_Character->ButtonColor(FLinearColor(1.0f, 0.0f, 1.0f), 13);
			break;
		default:
			_Character->ButtonColor(FLinearColor::Black, 9);
			_Character->ButtonColor(FLinearColor::Black, 13);
		}
	}

}

void UC_CustomizingManager::SetWeaponColor(AC_PlayerCharacter* _Character, int num)
{
	if (Cast<AC_Warrior>(_Character))
	{
		switch (num)
		{
		case 0:
			_Character->ButtonColor(FLinearColor::White, 6);
			break;
		case 1:
			_Character->ButtonColor(FLinearColor::Green, 6);
			break;
		case 2:
			_Character->ButtonColor(FLinearColor::Red, 6);
			break;
		default:
			_Character->ButtonColor(FLinearColor::White, 6);
			break;
		}
	}
	else if (Cast<AC_Mage>(_Character))
	{
		switch (num)
		{
		case 0:
			UC_CustomizingManager::BasicBagColor(_Character, FLinearColor(0.33f, 0.1122f, 0.326501f), FLinearColor::White);
			break;
		case 1:
			UC_CustomizingManager::BasicBagColor(_Character, FLinearColor::Blue , FLinearColor(1.0f,0.5f,0.0f));
			break;
		case 2:
			UC_CustomizingManager::BasicBagColor(_Character, FLinearColor::Green, FLinearColor::Red);
			break;
		case 3:
			UC_CustomizingManager::BasicBagColor(_Character, FLinearColor::Red, FLinearColor::Yellow);
			break;
		case 4:
			UC_CustomizingManager::BasicBagColor(_Character, FLinearColor::Yellow, FLinearColor::Black);
			break;
		case 5:
			UC_CustomizingManager::BasicBagColor(_Character, FLinearColor(0.0f, 1.0f, 1.0f), FLinearColor(1.0f,0.0f,1.0f));
			break;
		default:
			UC_CustomizingManager::BasicBagColor(_Character, FLinearColor(0.33f, 0.1122f, 0.326501f), FLinearColor::White);
			break;
		}
	}
}

void UC_CustomizingManager::BasicChest(AC_PlayerCharacter*& _Character, FLinearColor Armor, FLinearColor Neck, FLinearColor Detail)
{
	if (_Character)
	{
		_Character->ButtonColor(Armor, 1);
		_Character->ButtonColor(Neck, 11);
		_Character->ButtonColor(Detail, 12);
	}
}

void UC_CustomizingManager::BasicBelly(AC_PlayerCharacter*& _Character, FLinearColor Armor, FLinearColor Biceps, FLinearColor FormArm, FLinearColor Detail)
{
	if (_Character)
	{
		_Character->ButtonColor(Armor, 2);
		_Character->ButtonColor(Biceps, 21);
		_Character->ButtonColor(FormArm, 22);
		_Character->ButtonColor(Detail, 23);
	}
}

void UC_CustomizingManager::BasicSkirt(AC_PlayerCharacter*& _Character, FLinearColor Armor, FLinearColor DetailUp, FLinearColor DetailDown, FLinearColor Point, FLinearColor Thigh)
{
	if (_Character)
	{
		_Character->ButtonColor(Armor, 3);
		_Character->ButtonColor(DetailUp, 31);
		_Character->ButtonColor(DetailDown, 32);
		_Character->ButtonColor(Point, 33);
		_Character->ButtonColor(Thigh, 34);
	}
}

void UC_CustomizingManager::BasicKnee(AC_PlayerCharacter*& _Character, FLinearColor Armor, FLinearColor Leather, FLinearColor Detail)
{
	if (_Character)
	{
		_Character->ButtonColor(Armor, 5);
		_Character->ButtonColor(Leather, 51);
		_Character->ButtonColor(Detail, 52);
	}
}

void UC_CustomizingManager::BasicClothColor(AC_PlayerCharacter*& _Character, FLinearColor Fabric, FLinearColor Out, FLinearColor Shirt,FLinearColor Skirt)
{
	if (_Character)
	{
		_Character->ButtonColor(Fabric, 10);
		_Character->ButtonColor(Out, 101);
		_Character->ButtonColor(Shirt, 104);
		_Character->ButtonColor(Skirt, 105);
	}
}

void UC_CustomizingManager::BasicDetailColor(AC_PlayerCharacter*& _Character, FLinearColor Silk, FLinearColor Biz1, FLinearColor Biz2, FLinearColor Metal)
{
	if (_Character)
	{
		_Character->ButtonColor(Silk, 102);
		_Character->ButtonColor(Biz1, 3);
		_Character->ButtonColor(Biz2, 31);
		_Character->ButtonColor(Metal, 107);
	}
}

void UC_CustomizingManager::BasicBagColor(AC_PlayerCharacter*& _Character,FLinearColor Bag, FLinearColor Detail)
{
	if (_Character)
	{
		_Character->ButtonColor(Bag, 4);
		_Character->ButtonColor(Detail, 41);
	}
}

