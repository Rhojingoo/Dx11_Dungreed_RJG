#pragma once
#include <EngineCore/EngineEditorWindow.h>


// ���� : ���� ����� ���� ���ݿ��� ����� �����
class ABoss;
class UBoss_TestSkill_GUI : public UEngineEditorWindow
{
	friend ABoss;
public:
	// constrcuter destructer
	UBoss_TestSkill_GUI();
	~UBoss_TestSkill_GUI();

	// delete Function
	UBoss_TestSkill_GUI(const UBoss_TestSkill_GUI& _Other) = delete;
	UBoss_TestSkill_GUI(UBoss_TestSkill_GUI&& _Other) noexcept = delete;
	UBoss_TestSkill_GUI& operator=(const UBoss_TestSkill_GUI& _Other) = delete;
	UBoss_TestSkill_GUI& operator=(UBoss_TestSkill_GUI&& _Other) noexcept = delete;

protected:
	virtual void Init();
	virtual void OnGui(ULevel* Level, float _Delta);

private:
};

