#pragma once

enum class EOBJ_Order
{
	Damage_Screen,
	Player,
	Wapon,
	Bullet,
	Monster,
	Door,
	Cursor,
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
	AfterImage,
	Monster_Bullet,
	Monster,
	Monster_HpBack,
	Monster_Hp,
	Door,
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
	Door,
	GameStart_UI,
	GameEnd_UI,
	Monter_Bullet,
	Monster_AttackCol,
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