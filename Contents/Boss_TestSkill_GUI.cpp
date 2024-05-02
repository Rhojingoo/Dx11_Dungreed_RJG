#include "PreCompile.h"
#include "Boss.h"
#include "Boss_TestSkill_GUI.h"

UBoss_TestSkill_GUI::UBoss_TestSkill_GUI()
{
}

UBoss_TestSkill_GUI::~UBoss_TestSkill_GUI()
{
}


void UBoss_TestSkill_GUI::Init()
{
	int a = 0;
}

void UBoss_TestSkill_GUI::OnGui(ULevel* Level, float _Delta)
{
	if (true == ImGui::Button("TestMode_On"))
	{
		ABoss::TestAttack = true;
	}

	if (true == ImGui::Button("TestMode_Off"))
	{
		ABoss::TestAttack = false;
	}


	if (true == ImGui::Button("First_Skill"))
	{
		if (ABoss::TestAttack_Second == true || ABoss::TestAttack_Third == true || ABoss::TestAttack_Fourth == true || ABoss::TestAttack_Fifth == true || ABoss::TestAttack_Sixth == true)
		{
			return;
		}
		ABoss::TestAttack_First = true;
	}
	if (true == ImGui::Button("Second_Skill"))
	{
		if (ABoss::TestAttack_First == true || ABoss::TestAttack_Third == true || ABoss::TestAttack_Fourth == true || ABoss::TestAttack_Fifth == true || ABoss::TestAttack_Sixth == true)
		{
			return;
		}
		ABoss::TestAttack_Second = true;
	}
	if (true == ImGui::Button("Third_Skill"))
	{
		if (ABoss::TestAttack_First == true || ABoss::TestAttack_Second == true || ABoss::TestAttack_Fourth == true || ABoss::TestAttack_Fifth == true || ABoss::TestAttack_Sixth == true)
		{
			return;
		}
		ABoss::TestAttack_Third = true;
	}

	if (true == ImGui::Button("Fourth_Skill"))
	{
		if (ABoss::TestAttack_First == true || ABoss::TestAttack_Second == true || ABoss::TestAttack_Third == true || ABoss::TestAttack_Fifth == true || ABoss::TestAttack_Sixth == true)
		{
			return;
		}
		ABoss::TestAttack_Fourth = true;
	}

	if (true == ImGui::Button("Fiftg_Skill"))
	{
		if (ABoss::TestAttack_First == true || ABoss::TestAttack_Second == true || ABoss::TestAttack_Third == true || ABoss::TestAttack_Fourth == true || ABoss::TestAttack_Sixth == true)
		{
			return;
		}
		ABoss::TestAttack_Fifth = true;
	}

	if (true == ImGui::Button("Sixth_Skill"))
	{
		if (ABoss::TestAttack_First == true || ABoss::TestAttack_Second == true || ABoss::TestAttack_Third == true || ABoss::TestAttack_Fourth == true || ABoss::TestAttack_Fifth == true)
		{
			return;
		}
		ABoss::TestAttack_Sixth = true;
	}
}

