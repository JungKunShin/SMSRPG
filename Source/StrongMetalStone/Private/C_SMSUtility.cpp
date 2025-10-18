#include "C_SMSUtility.h"
#include "Character/C_PlayerCharacter.h"
TArray<FUserInfo> GetLoadUserInfoFromCSV()
{	
	FString UserInfoCSVPath;
	if (GIsEditor)
	{
		UserInfoCSVPath = FPaths::ProjectSavedDir() + TEXT("CSV/UserInfoCSV.csv");
	}
	else
	{
		UserInfoCSVPath = TEXT("../../../../WindowsServer/StrongMetalStone/Saved/CSV/UserInfoCSV.csv");
	}

	TArray<FString> UserInfoToString;
	TArray<FUserInfo> UserInfos;
	if (FFileHelper::LoadFileToStringArray(UserInfoToString, *UserInfoCSVPath))
	{
		for (int32 i = 0; i < UserInfoToString.Num(); i++)
		{
			FString Line = UserInfoToString[i];

			//쉼표마다 구분하여 배열에 저장
			TArray<FString> Columns;
			Line.ParseIntoArray(Columns, TEXT(","), true);

			if (Columns.Num() == 3)
			{
				FUserInfo UserInfo;
				FGuid OutGuid;

				FGuid::Parse(Columns[2], OutGuid); //String을 GUID로

				UserInfo.ID = Columns[0];
				UserInfo.PassWord = Columns[1];
				UserInfo.GUID = OutGuid;

				UserInfos.Add(UserInfo);
			}
		}
	}
	return UserInfos;
	
}

void AddUserInfoToCSV(FUserInfo _UserInfo)
{
	FString UserInfoCSVPath;
	if (GIsEditor)
	{
		UserInfoCSVPath = FPaths::ProjectSavedDir() + TEXT("CSV/UserInfoCSV.csv");
	}
	else
	{
		UserInfoCSVPath = TEXT("../../../../WindowsServer/StrongMetalStone/Saved/CSV/UserInfoCSV.csv");
	}
	TArray<FString> UserInfoToString;
	FFileHelper::LoadFileToStringArray(UserInfoToString, *UserInfoCSVPath);

	FString RowData = FString::Printf(TEXT("%s,%s,%s"), *_UserInfo.ID, *_UserInfo.PassWord, *(_UserInfo.GUID).ToString());
	UserInfoToString.Add(RowData);


	FFileHelper::SaveStringArrayToFile(UserInfoToString, *UserInfoCSVPath);

}

TArray<FCharacterInfo> GetLoadCharacterInfoFromCSV()
{
	FString CharacterInfoCSVPath;

	if (GIsEditor)
	{
		CharacterInfoCSVPath = FPaths::ProjectSavedDir() + TEXT("CSV/CharacterInfoCSV.csv");
	}
	else
	{
		CharacterInfoCSVPath = TEXT("../../../../WindowsServer/StrongMetalStone/Saved/CSV/CharacterInfoCSV.csv");
	}

	TArray<FString> CharacterInfoToString;
	TArray<FCharacterInfo> CharacterInfos;
	if (FFileHelper::LoadFileToStringArray(CharacterInfoToString, *CharacterInfoCSVPath))
	{
		for (int32 i = 0; i < CharacterInfoToString.Num(); i++)
		{
			FString Line = CharacterInfoToString[i];

			//쉼표마다 구분하여 배열에 저장
			TArray<FString> Columns;
			Line.ParseIntoArray(Columns, TEXT(","), true);

			FCharacterInfo CharacterInfo;
			EPlayerJob PlayerJob;

			CharacterInfo.UserID = Columns[0];
			CharacterInfo.CharacterName = Columns[1];
			CharacterInfo.Job = StringToEnum(Columns[2],PlayerJob);
			CharacterInfo.Level = FCString::Atof(*Columns[3]);
			CharacterInfo.CurExp = FCString::Atof(*Columns[4]);
			CharacterInfo.Maxhp = FCString::Atof(*Columns[5]);
			CharacterInfo.Curhp = FCString::Atof(*Columns[6]);
			CharacterInfo.Maxmp = FCString::Atof(*Columns[7]);
			CharacterInfo.Curmp = FCString::Atof(*Columns[8]);
			CharacterInfo.Damage = FCString::Atof(*Columns[9]);
			CharacterInfo.Defense = FCString::Atof(*Columns[10]);
			CharacterInfo.SkillPoint = FCString::Atof(*Columns[11]);
			CharacterInfo.CustomizingInfo.ArmorColorNum = FCString::Atoi(*Columns[12]);
			CharacterInfo.CustomizingInfo.EyeColorNum = FCString::Atoi(*Columns[13]);
			CharacterInfo.CustomizingInfo.EyelashColorNum = FCString::Atoi(*Columns[14]);
			CharacterInfo.CustomizingInfo.FaceColorNum = FCString::Atof(*Columns[15]);
			CharacterInfo.CustomizingInfo.HairColorNum = FCString::Atoi(*Columns[16]);
			CharacterInfo.CustomizingInfo.WeaponColorNum = FCString::Atoi(*Columns[17]);


			CharacterInfos.Add(CharacterInfo);
		}
	}

	return CharacterInfos;
}

void AddCharacterInfoToCSV(FCharacterInfo _CharacterInfo)
{
	FString CharacterInfoCSVPath;

	if (GIsEditor)
	{
		CharacterInfoCSVPath = FPaths::ProjectSavedDir() + TEXT("CSV/CharacterInfoCSV.csv");
	}
	else
	{
		CharacterInfoCSVPath = TEXT("../../../../WindowsServer/StrongMetalStone/Saved/CSV/CharacterInfoCSV.csv");
	}

	TArray<FString> CharacterInfoToString;
	if (FFileHelper::LoadFileToStringArray(CharacterInfoToString, *CharacterInfoCSVPath))
	{
		FString RowData = FString::Printf(TEXT("%s,%s,%s,%u,%d,%f,%f,%f,%f,%f,%f,%d,%d,%d,%d,%f,%d,%d"), 
			*_CharacterInfo.UserID, *_CharacterInfo.CharacterName, *ENUM_TO_STRING(EPlayerJob, _CharacterInfo.Job),
			_CharacterInfo.Level, _CharacterInfo.CurExp, _CharacterInfo.Maxhp, _CharacterInfo.Curhp, 
			_CharacterInfo.Maxmp, _CharacterInfo.Curmp, _CharacterInfo.Damage, _CharacterInfo.Defense, 
			_CharacterInfo.SkillPoint
			,_CharacterInfo.CustomizingInfo.ArmorColorNum, _CharacterInfo.CustomizingInfo.EyeColorNum
			, _CharacterInfo.CustomizingInfo.EyelashColorNum, _CharacterInfo.CustomizingInfo.FaceColorNum
			, _CharacterInfo.CustomizingInfo.HairColorNum, _CharacterInfo.CustomizingInfo.WeaponColorNum);

		CharacterInfoToString.Add(RowData);
	}


	FFileHelper::SaveStringArrayToFile(CharacterInfoToString, *CharacterInfoCSVPath);
}

void DeleteCharacterInfoCSV(FCharacterInfo _CharacterInfo)
{
	FString CharacterInfoCSVPath;

	if (GIsEditor)
	{
		CharacterInfoCSVPath = FPaths::ProjectSavedDir() + TEXT("CSV/CharacterInfoCSV.csv");
	}
	else
	{
		CharacterInfoCSVPath = TEXT("../../../../WindowsServer/StrongMetalStone/Saved/CSV/CharacterInfoCSV.csv");
	}

	TArray<FString> CharacterInfoToString;
	if (FFileHelper::LoadFileToStringArray(CharacterInfoToString, *CharacterInfoCSVPath))
	{
		TArray<FString> FilteredLines;

		for (const FString& Line : CharacterInfoToString)
		{
			TArray<FString> Columns;
			Line.ParseIntoArray(Columns, TEXT(","), true);


			// 두 번째 열 값이 MatchValue와 다른 경우만 저장
			if (Columns[1] != _CharacterInfo.CharacterName)
			{
				FilteredLines.Add(Line);
			}
		}
		// 필터링된 라인들을 다시 파일로 저장
		FFileHelper::SaveStringArrayToFile(FilteredLines, *CharacterInfoCSVPath);
	}
}



void UpdateCharacterInfoCSV(FCharacterInfo _NewCharacterInfo)
{
	DeleteCharacterInfoCSV(_NewCharacterInfo);
	AddCharacterInfoToCSV(_NewCharacterInfo);
}

TArray<FQuestData> GetLoadQuestFromCSV(AC_PlayerCharacter* _Owner)
{
	FString QuestCSVPath;

	if (GIsEditor)
	{
		QuestCSVPath = FPaths::ProjectSavedDir() + TEXT("CSV/QuestCSV.csv");
	}
	else
	{
		QuestCSVPath = TEXT("../../../../WindowsServer/StrongMetalStone/Saved/CSV/QuestCSV.csv");
	}

	TArray<FString> QuestToString;
	TArray<FQuestData> Quests;
	if (FFileHelper::LoadFileToStringArray(QuestToString, *QuestCSVPath))
	{
		for (int32 i = 0; i < QuestToString.Num(); i++)
		{
			FString Line = QuestToString[i];

			//쉼표마다 구분하여 배열에 저장
			TArray<FString> Columns;
			Line.ParseIntoArray(Columns, TEXT(","), true);

			FQuestData QuestInfo;
			EQuestState QuestState;

			QuestInfo.OwnerName = Columns[0];
			QuestInfo.QuestTitle = FText::FromString(Columns[1]);
			QuestInfo.QuestState = StringToEnum(Columns[2], QuestState);
			QuestInfo.CurNum = FCString::Atoi(*Columns[3]);
			
			Quests.Add(QuestInfo);
		}
	}

	return Quests;
}

void AddQuestToCSV(FQuestData _QuestInfo)
{
	FString QuestCSVPath;

	if (GIsEditor)
	{
		QuestCSVPath = FPaths::ProjectSavedDir() + TEXT("CSV/QuestCSV.csv");
	}
	else
	{
		QuestCSVPath = TEXT("../../../../WindowsServer/StrongMetalStone/Saved/CSV/QuestCSV.csv");
	}

	TArray<FString> QuestToString;
	if (FFileHelper::LoadFileToStringArray(QuestToString, *QuestCSVPath))
	{
		FString RowData = FString::Printf(TEXT("%s,%s,%s,%d"),
			*_QuestInfo.OwnerName, *_QuestInfo.QuestTitle.ToString(), *ENUM_TO_STRING(EQuestState, _QuestInfo.QuestState), _QuestInfo.CurNum);

		QuestToString.Add(RowData);
	}


	FFileHelper::SaveStringArrayToFile(QuestToString, *QuestCSVPath);
}

void DeleteQuestCSV(FQuestData _QuestInfo)
{
	FString QuestCSVPath;

	if (GIsEditor)
	{
		QuestCSVPath = FPaths::ProjectSavedDir() + TEXT("CSV/QuestCSV.csv");
	}
	else
	{
		QuestCSVPath = TEXT("../../../../WindowsServer/StrongMetalStone/Saved/CSV/QuestCSV.csv");
	}

	TArray<FString> QuestToString;
	if (FFileHelper::LoadFileToStringArray(QuestToString, *QuestCSVPath))
	{
		TArray<FString> FilteredLines;

		for (const FString& Line : QuestToString)
		{
			TArray<FString> Columns;
			Line.ParseIntoArray(Columns, TEXT(","), true);

			// 퀘스트의 주인이아니고, 해당퀘스트가 아닌경우 저장
			if (Columns[0] != _QuestInfo.OwnerName || Columns[1] != _QuestInfo.QuestTitle.ToString())
			{
				FilteredLines.Add(Line);
			}
			

		}
		// 필터링된 라인들을 다시 파일로 저장
		FFileHelper::SaveStringArrayToFile(FilteredLines, *QuestCSVPath);
	}
}

FString GetServerIP()
{
	FString ServerIPPath;

	if (GIsEditor)
	{
		ServerIPPath = TEXT("127.0.0.1");
	}
	else
	{
		ServerIPPath = TEXT("../../../ServerIP.txt");
	}


	TArray<FString> IPToString;
	FFileHelper::LoadFileToStringArray(IPToString, *ServerIPPath);

	return IPToString[0];
}

TMap<int32, unsigned int> GetLoadExpData()
{
	FString ExpInfoCSVPath;

	if (GIsEditor)
	{
		ExpInfoCSVPath = FPaths::ProjectSavedDir() + TEXT("CSV/ExpInfoCSV.csv");
	}
	else
	{
		ExpInfoCSVPath = TEXT("../../../../WindowsServer/StrongMetalStone/Saved/CSV/ExpInfoCSV.csv");
	}

	TArray<FString> ExpToString;	
	TMap<int32, unsigned int> Exps;

	if (FFileHelper::LoadFileToStringArray(ExpToString, *ExpInfoCSVPath))
	{
		for (int32 i = 0; i < ExpToString.Num(); i++)
		{
			FString Line = ExpToString[i];

			//쉼표마다 구분하여 배열에 저장
			TArray<FString> Columns;
			Line.ParseIntoArray(Columns, TEXT(","), true);

			Exps.Add(FCString::Atof(*Columns[0]), FCString::Atof(*Columns[1]));
		}
	}

	return Exps;
}

FText LimitString(FText NewText, FRegexPattern Pattern, bool IsReverse)
{
	FString InputString = NewText.ToString();
	if (InputString.Len() <= 0) return NewText;

	FRegexMatcher Matcher(Pattern, InputString.Right(1));

	//금지패턴에 걸리는 문자 제거
	if (Matcher.FindNext() != IsReverse)
	{
		InputString.RemoveAt(InputString.Len() - 1);
	}

	return FText::FromString(InputString);
}

void MakeServer(const FString& LevelName, int32 portNum)
{
	FString ServerCommand = FString::Printf(TEXT("StrongMetalStoneServer.exe"));
	FString ServerArguments = FString::Printf(TEXT("%s -port=%d -log"), *LevelName, portNum);
	FProcHandle ServerHandle = FPlatformProcess::CreateProc(*ServerCommand, *ServerArguments, true, false, false, nullptr, 0, nullptr, nullptr);	
}
