#pragma once

enum class EOBJ_Order
{
	Player,
	Wapon,
	Bullet,
	Monster,
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
	Collision,
	Effect_Back,
	Effect_Mid,
	Effect_Front,
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
};

enum class EColOrder
{
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