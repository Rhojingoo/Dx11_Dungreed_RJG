#include "PreCompile.h"
#include "ContentsGUI.h"

ContentsGUI::ContentsGUI() 
{
}

ContentsGUI::~ContentsGUI() 
{
}

void ContentsGUI::Init() 
{
}

void ContentsGUI::OnGui(ULevel* _Level, float _Delta)
{
	if (true == ImGui::Button("TitleLevel"))
	{
		GEngine->ChangeLevel("TitleLevel");
	}

	if (true == ImGui::Button("TownLevel"))
	{
		GEngine->ChangeLevel("TownLevel");
	}

	if (true == ImGui::Button("Mon01_Level"))
	{
		GEngine->ChangeLevel("Mon01_Level");
	}
	if (true == ImGui::Button("Mon02_Level"))
	{
		GEngine->ChangeLevel("Mon02_Level");
	}
	if (true == ImGui::Button("Mon03_Level"))
	{
		GEngine->ChangeLevel("Mon03_Level");
	}

	if (true == ImGui::Button("BossLevel"))
	{
		GEngine->ChangeLevel("BossLevel");
	}

}