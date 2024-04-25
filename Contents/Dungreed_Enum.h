#pragma once

enum class EOBJ_Order
{
	Player,
	Wapon,
	Bullet,
	Monster,
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
};

enum class EColOrder
{
	Door,
	Monster_Col,
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