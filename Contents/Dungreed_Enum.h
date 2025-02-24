#pragma once

enum class EOBJ_Order
{
	Damage_Screen,
	Player,
	Wapon,
	Bullet,
	Monster,
	Cursor,
	Door,
	BackGround,
	PixelGround,
};

enum class ERenderOrder
{
	BackGround,
	MidGround,
	ForeGround,
	PixelMap,
	TileMap,
	Effect_Back,
	Effect_Mid,
	Effect_Front,
	Door,
	AfterImage,
	Monster_Bullet,
	Monster,
	Monster_HpBack,
	Monster_Hp,
	Boss_Bullet,
	Boss_IceBullet_Effect,
	Boss_IceBullet,
	Boss,
	Attack_Effect,
	Wapon,
	Player,
	Cursor,
	Collision,
	Damage_Screen,
};

enum class EColOrder
{
	BossDoor,
	DungeonDoor,
	TonwDoor,
	GameStart_UI,
	GameEnd_UI,
	Monter_Bullet,
	Monster_AttackCol,
	Monster_SearchCol,
	Monster,
	Boss_Col,
	Boss_IceSpear,
	Boss_IceBullet,
	Boss_Icicle_Bullet,
	Boss_IcePillar,
	Boss,
	Wapon,
	Player,
	Cursor,
};