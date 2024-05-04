#include "PreCompile.h"
#include "Skeleton_ATKCOL.h"
#include <EngineCore/DefaultSceneComponent.h>

ASkeleton_ATKCOL::ASkeleton_ATKCOL()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	SetRoot(Root);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(Root);
	Collision->SetCollisionGroup(EColOrder::Monster_AttackCol);
	Collision->SetCollisionType(ECollisionType::RotRect);
	Collision->SetScale(FVector(200.0f,300.0f,1.f));


}

ASkeleton_ATKCOL::~ASkeleton_ATKCOL()
{
}

float ASkeleton_ATKCOL::Getdamage()
{
	Damage = UContentsHelper::Random(MinDamage, MaxDamage);
	return Damage;
}

void ASkeleton_ATKCOL::BeginPlay()
{
	Super::BeginPlay();

	//Collision->SetCollisionGroup(EColOrder::Monster_AttackCol);
	//Collision->SetCollisionType(ECollisionType::RotRect);
	//Collision->SetScale(FVector(120.0f, 80.0f));
}

void ASkeleton_ATKCOL::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
