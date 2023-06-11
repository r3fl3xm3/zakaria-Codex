#pragma once
#include "Includes.h"
namespace settings {
	D3DXCOLOR FriendBox = D3DXCOLOR(0, 0, 1, 1);
	D3DXCOLOR EnemyBOX = D3DXCOLOR(1, 0, 0, 1);

	D3DXCOLOR FriendLine = D3DXCOLOR(0, 0, 1, 1);
	D3DXCOLOR EnemyLine = D3DXCOLOR(1, 0, 0, 1);

	D3DXCOLOR FriendFillbox = D3DXCOLOR(0, 0, 1, 1);
	D3DXCOLOR EnemyFillbox = D3DXCOLOR(1, 0, 0, 1);

	D3DXCOLOR FriendKnocked = D3DXCOLOR(0, 1, 1, 1);
	D3DXCOLOR EnemyKnocked = D3DXCOLOR(1, 1, 1, 1);

	D3DXCOLOR Closed = D3DXCOLOR(1, 1, 0, 1);

	bool aimbot = true;
	bool autolock = false;
	bool aimknocked = false;
	int aimbothitbox = 2;
	float aimspeed = 23;
	float aimbotfov = 14;
	float aimlock = 0.5;
	bool aimbotdrawfov = true;
	bool aimbotdrawhitbox = true;

	bool teamBoxes = false;
	bool enemyBoxes = true;
	bool teamDistance = false;
	bool enemyDistance = true;
	bool teamWeaponName = false;
	bool enemyWeaponName = true;
	bool teamSnaplines = false;
	bool enemySnaplines = true;
	bool teamHealth = false;
	bool enemyHealth = true;
	bool teamShieldHealth = false;
	bool enemyShieldHealth = true;
	bool teamFilledbox = false;
	bool enemyFilledbox = false;
	bool teamKnocked = false;
	bool enemyKnocked = true;

	bool lootdeathbox = true;
	bool lootweapon = true;
	bool lootammo = false;
	bool loothealing = false;
	bool loothemmet= true;
	bool lootbodyshild = true;
	bool lootbackpack = true;
	bool lootshild = false;
	bool lootgrenades = false;
	bool lootscops = false;
	bool lootattachments = false;

	
	int boxtype = 0;
	int healthbartype = 0;
	int shildbartype = 0;
	int PlayerWeapontype = 0;
	float playersdis = 250;
	bool esp_Outline = 1;

	bool c_enable = true;
	int crosshair = 6;
	float size = 0;
	float stroke = 0;

	float menux = 0;
	float menuy = 400;
}