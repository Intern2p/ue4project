// Copyright Epic Games, Inc. All Rights Reserved.

#include "TowerDefenseGameMode.h"
#include "TowerDefenseCharacter.h"
#include "UObject/ConstructorHelpers.h"

//1 - ������ ������ ��� � �������
//2 - ������� ����� ����������� ����� projectile ��� trace? ���� trace - �� ��� ������� ��� � ����� � �������� � ����������.
//3 - ������ ������� �������� (�� overlap ������� ����������� ��������� �������, �� ������ f �������� ��������� �������) ������ - ��� �������� ������ ����� ������� �� ������

ATowerDefenseGameMode::ATowerDefenseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
