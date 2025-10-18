
#pragma once

#include "CoreMinimal.h"
#include "C_SMSStruct.h"
                       
#include "Internationalization/Text.h"      

// ENum을 String으로 바꿔주는 매크로 
// Ex) FString JobName = ENUM_TO_STRING(EPlayerJob, EPlayerJob::WARRIOR);
// 이렇게하면 JobName에 WARRIOR가 들어가게 됨.
#define ENUM_TO_STRING(EnumType, Value) StaticEnum<EnumType>()->GetNameStringByValue((int64)Value)

//String을 ENum으로 바꿔주는 탬플릿함수
//Ex) EPlayerJob TempJob;
// StringToEnum("WARRIOR",TempJob);
//TempJob에 원하는 Enum값이 들어가며 Return으로 받아서도 쓸 수있음
template<typename T>
T StringToEnum(const FString& StringValue, T& OutEnum)
{
    int64 Value = StaticEnum<T>()->GetValueByName(FName(*StringValue));

    OutEnum = static_cast<T>(Value);
    return OutEnum;
}


//
TArray<FUserInfo> GetLoadUserInfoFromCSV(); //CSV에 저장된 유저 정보를 리턴받는 함수
void AddUserInfoToCSV(FUserInfo _UserInfo); //CSV에 유저 정보를 추가하는 함수

TArray<FCharacterInfo> GetLoadCharacterInfoFromCSV(); //CSV에 저장된 캐릭터 정보를 리턴받는 함수
void AddCharacterInfoToCSV(FCharacterInfo _CharacterInfo); //CSV에 캐릭터 정보를 추가하는 함수
void DeleteCharacterInfoCSV(FCharacterInfo _CharacterInfo);
void UpdateCharacterInfoCSV(FCharacterInfo _NewCharacterInfo);

TArray<FQuestData> GetLoadQuestFromCSV(AC_PlayerCharacter* _Owner); //CSV에 저장된 퀘스트 정보를 리턴받는 함수
void AddQuestToCSV(FQuestData _QuestInfo); //CSV에 퀘스트 정보를 추가하는 함수
void DeleteQuestCSV(FQuestData _QuestInfo);


FString GetServerIP();

TMap<int32, unsigned int> GetLoadExpData(); //경험치 정보 읽기

FText LimitString(FText NewText, FRegexPattern Pattern, bool IsReverse = false); // 글자 제한 패턴 적용 함수
void MakeServer(const FString& LevelName, int32 portNum); //서버 생성 함수


