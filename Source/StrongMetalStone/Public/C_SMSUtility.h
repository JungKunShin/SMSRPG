
#pragma once

#include "CoreMinimal.h"
#include "C_SMSStruct.h"
                       
#include "Internationalization/Text.h"      

// ENum�� String���� �ٲ��ִ� ��ũ�� 
// Ex) FString JobName = ENUM_TO_STRING(EPlayerJob, EPlayerJob::WARRIOR);
// �̷����ϸ� JobName�� WARRIOR�� ���� ��.
#define ENUM_TO_STRING(EnumType, Value) StaticEnum<EnumType>()->GetNameStringByValue((int64)Value)

//String�� ENum���� �ٲ��ִ� ���ø��Լ�
//Ex) EPlayerJob TempJob;
// StringToEnum("WARRIOR",TempJob);
//TempJob�� ���ϴ� Enum���� ���� Return���� �޾Ƽ��� �� ������
template<typename T>
T StringToEnum(const FString& StringValue, T& OutEnum)
{
    int64 Value = StaticEnum<T>()->GetValueByName(FName(*StringValue));

    OutEnum = static_cast<T>(Value);
    return OutEnum;
}


//
TArray<FUserInfo> GetLoadUserInfoFromCSV(); //CSV�� ����� ���� ������ ���Ϲ޴� �Լ�
void AddUserInfoToCSV(FUserInfo _UserInfo); //CSV�� ���� ������ �߰��ϴ� �Լ�

TArray<FCharacterInfo> GetLoadCharacterInfoFromCSV(); //CSV�� ����� ĳ���� ������ ���Ϲ޴� �Լ�
void AddCharacterInfoToCSV(FCharacterInfo _CharacterInfo); //CSV�� ĳ���� ������ �߰��ϴ� �Լ�
void DeleteCharacterInfoCSV(FCharacterInfo _CharacterInfo);
void UpdateCharacterInfoCSV(FCharacterInfo _NewCharacterInfo);

TArray<FQuestData> GetLoadQuestFromCSV(AC_PlayerCharacter* _Owner); //CSV�� ����� ����Ʈ ������ ���Ϲ޴� �Լ�
void AddQuestToCSV(FQuestData _QuestInfo); //CSV�� ����Ʈ ������ �߰��ϴ� �Լ�
void DeleteQuestCSV(FQuestData _QuestInfo);


FString GetServerIP();

TMap<int32, unsigned int> GetLoadExpData(); //����ġ ���� �б�

FText LimitString(FText NewText, FRegexPattern Pattern, bool IsReverse = false); // ���� ���� ���� ���� �Լ�
void MakeServer(const FString& LevelName, int32 portNum); //���� ���� �Լ�


