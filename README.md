# SMSRPG
언리얼 RPG게임 팀프로젝트

## 🤖 프로젝트 소개
**SMS RPG**는 **4명**의 구성원이 언리얼 C++를 이용하여 개발한 팀프로젝트입니다.<br>
**마비노기 영웅전**을 레퍼런스하여 제작된 ARPG, MMORPG 장르 게임입니다.<br>
필드에서 몬스터를 사냥하여 경험치를 쌓아 레벨업을 하고, 파티를 맺어 던전 레이드를 하는 것이 특징입니다.<br>
또한, 플레이어들끼리 전투를 할 수 있는 PVP모드도 이 게임의 특징입니다.<br>
<br><br>

## 🔗 프로젝트 관련 링크

### 📹 프로젝트 영상 링크<br>

![](https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=youtube&logoColor=white)&nbsp;&nbsp;
[SMS RPG 플레이영상](https://youtu.be/OdHvv5oxNAg "SMS RPG 영상")
<br><br><br>

## 📆 개발기간
+ 2025.04.21 ~ 2025.06.25 (10주) <br><br>

## 🧰 기술 스택 및 환경
![](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white) ![](	https://img.shields.io/badge/unrealengine-%23313131.svg?style=for-the-badge&logo=unrealengine&logoColor=white)
![](https://img.shields.io/badge/Visual_Studio-5C2D91?style=for-the-badge&logo=visual%20studio&logoColor=white)
- Language : C++
- Game Engine : Unreal Engine 5 (C++ / Blueprint 혼합 개발)
- IDE : Visual Studio 2022
- Version Control : SVN (Team Collaboration)
- Gameplay Systems :
  - Skill System(ActorComponent 기반 상호작용)
  - Party System(ActorComponent 기반 상호작용)
  - Skill Data(DataAsset 기반)
  - AI System(NPC / 적 행동 제어)
  - Quest System(DataTable 기반)
- Data Handling : DataTable (CSV)
- VFX / SFX : Sound Wave, Audio Component, Niagara, Particle System
- Tools : Blueprint, Behavior Tree, Material Editor, Sequencer, Material Instance Dynamic etc
<br><br>

## 🔧 담당 업무
1. 💂‍♂️ 캐릭터
   - 액터 컴퍼넌트 'SkillSystemComponent'를 이용하여 캐릭터 코드 과집중 방지
   - 데이터 에셋 'Skill' 스킬관련 정보 사용
   - 'SkillSystemComponent'로부터 'Skill/SkillINS', 'AnimNotify', 'AttackParticle/Projectile'로 이어지는 스킬 흐름<br><br>
   ![전사 스킬](https://github.com/JungKunShin/SMSRPG/blob/main/Image/Skill_Warrior.png)<br>
   ![마법사 스킬](https://github.com/JungKunShin/SMSRPG/blob/main/Image/Skill_Mage.png)<br>
---
2. 👹 퀘스트 시스템
   - 퀘스트 관련 정보 데이터 테이블에서 관리
   - 'SMSQuest'를 상속받은 'Quest'들에서 각자의 퀘스트 정보 관리
   - 현재 플레이어의 진행중인 퀘스트와 완료 퀘스트를 'QuestManager'가 관리<br><br>
   ![퀘스트 전](https://github.com/JungKunShin/SMSRPG/blob/main/Image/Quest_Before.png)<br>
   ![퀘스트 중](https://github.com/JungKunShin/SMSRPG/blob/main/Image/Quest.png)<br>
   ![퀘스트 후](https://github.com/JungKunShin/SMSRPG/blob/main/Image/Quest_After.png)<br>
---
3. 🐎 탑승물
   - 'SMSCharacter'캐릭터에서 'SMSRiding'캐릭터로 Possess 전환
   - Attach를 이용해, 'SMSCharacter'를 'SMSRiding'캐릭터에 부착<br><br>
   ![탑승 전](https://github.com/JungKunShin/SMSRPG/blob/main/Image/Riding_Before.png)<br>
   ![탑승 후](https://github.com/JungKunShin/SMSRPG/blob/main/Image/Riding_After.png)<br>
---
4. 💇 커스터마이징
   - MaterialInstanceDynamic을 이용하여 캐릭터의 머티리얼을 동적으로 변경
   - 커스터마이징은 슬라이더 값을 통한 변경과 프리셋 적용 버튼을 통한 변경 두가지로 구분
   - 플레이어의 커스터마이징 선택정보를 'CustomizingManager'가 적용 후 데이터 테이블에서 저장 및 관리<br><br>
   ![커스터마이징 전](https://github.com/JungKunShin/SMSRPG/blob/main/Image/Cutomizing_Before.png)<br>
   ![커스터마이징 후](https://github.com/JungKunShin/SMSRPG/blob/main/Image/Cutomizing_After.png)<br>
---
5. 📊 결과창
   - 캐릭터의 직업에 따라 다른 결과창 이미지 출력
   - 모든 플레이어들의 정보를 AddChild하여 스크롤박스에 부착
   - 닉네임, 레벨, 데미지량 등을 표기<br><br>
   ![결과창](https://github.com/JungKunShin/SMSRPG/blob/main/Image/Result.png)<br>
