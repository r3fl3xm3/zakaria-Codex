#pragma once
#include "Includes.h"
#include "settings.h"
LPCSTR FilePath = "./Settings.ini";


struct view
{
	float v[16];
};
static class Text
{
public:
	std::string text;
	int side;
	int size;
	D3DXCOLOR color;
	Text(std::string text, int side, int size, D3DXCOLOR color) : text(text), side(side), size(size), color(color) {}
};

class MOUSE
{
private:
	// coordinate variable
	POINT point;
public:
	//Mobile class function
	void Move(int x, int y);
	void RelativeMove(int cx, int cy);
	void SavePos();
	void RestorePos();
	//Lock enabled class
	void Lock();
	void Unlock();

};

// Move the mouse to the absolute position(X coordinate, Y coordinate)
void MOUSE::Move(int x, int y)
{
	this->point.x = x;
	this->point.y = y;
	::SetCursorPos(x, y);
}

// Move the mouse to the relative position(X displacement, Y displacement)
void MOUSE::RelativeMove(int cx, int cy)
{
	::ShowCursor(0);
	::GetCursorPos(&this->point);
	this->point.x += cx;
	this->point.y += cy;
	::SetCursorPos(this->point.x, this->point.y);
}

// Save the current location()
void MOUSE::SavePos()
{
	::GetCursorPos(&this->point);
}

// Restore mouse position()
void MOUSE::RestorePos()
{
	::SetCursorPos(this->point.x, this->point.y);
}

// Lock the mouse()
void MOUSE::Lock()
{
	POINT pt;
	RECT rt;
	::GetCursorPos(&pt);
	rt.left = rt.right = pt.x;
	rt.top = rt.bottom = pt.y;
	rt.right++;
	rt.bottom++;
	::ClipCursor(&rt);

}

//Unlock the mouse ()
void MOUSE::Unlock()
{
	::ClipCursor(NULL);
}
class Inputs {
private:
	static DWORD SendScanCode(WORD scan, BOOL up)
	{
		INPUT inp = { 0 };
		inp.type = INPUT_KEYBOARD;
		inp.ki.wScan = scan;
		inp.ki.dwFlags = KEYEVENTF_SCANCODE | (up ? KEYEVENTF_KEYUP : 0);
		return SendInput(1, &inp, sizeof(inp)) ? NO_ERROR : GetLastError();
	}
public:
	static bool mouse_move(int x, int y)
	{
		INPUT input;
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.time = 0;
		input.mi.dx = x;
		input.mi.dy = y;
		input.mi.dwFlags = MOUSEEVENTF_MOVE;
		SendInput(1, &input, sizeof(input));
		return true;
	}
	static void MouseClick(int key)
	{
		INPUT Input = { 0 };
		Input.type = INPUT_MOUSE;
		Input.mi.mouseData = 0;
		Input.mi.time = 0;
		Input.mi.dwFlags = key;
		SendInput(1, &Input, sizeof(INPUT));
	}

	static DWORD SendVirtualKey(UINT vk, BOOL up)
	{
		UINT scan = MapVirtualKey(vk, MAPVK_VK_TO_VSC);
		return scan ? SendScanCode(scan, up) : ERROR_NO_UNICODE_TRANSLATION;
	}
	bool static keydown(int key)
	{
		return (GetAsyncKeyState(key) & 0x8000) != 0;
	}
};
float Distance(D3DXVECTOR3 EntityPos, D3DXVECTOR3 PlayerPos)
{
	float Dist = sqrt((PlayerPos.x - EntityPos.x) * (PlayerPos.x - EntityPos.x)
		+ (PlayerPos.y - EntityPos.y) * (PlayerPos.y - EntityPos.y)
		+ (PlayerPos.z - EntityPos.z) * (PlayerPos.z - EntityPos.z));
	return Dist * 0.01905f;
}
float Distance3D(D3DXVECTOR3  v1, D3DXVECTOR3 v2)
{
	float x_d = (v2.x - v1.x);
	float y_d = (v2.y - v1.y);
	float z_d = (v2.z - v1.z);
	return sqrt((x_d * x_d) + (y_d * y_d) + (z_d * z_d));
}
double GetCrossDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
void AimAtPosV2(int screenwidth,int screenheight, float x, float y, float speed, float lock, bool smooth)
{
	//MOUSE move = MOUSE();
	int ScreenCenterX = screenwidth / 2, ScreenCenterY = screenheight / 2;

	float AimSpeed = (float)speed + 0.2f;
	float TargetX = 0;
	float TargetY = 0;

	//X Axis
	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			TargetX += lock;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			TargetX -= lock;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	//Y Axis

	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			TargetY += lock;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			TargetY -= lock;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}

	if (!smooth)
	{
		Inputs::mouse_move((int)TargetX, (int)(TargetY));
		return;
	}

	TargetX /= 10;
	TargetY /= 10;

	if (abs(TargetX) < 1)
	{
		if (TargetX > 0)
		{
			TargetX = 1;
		}
		if (TargetX < 0)
		{
			TargetX = -1;
		}
	}
	if (abs(TargetY) < 1)
	{
		if (TargetY > 0)
		{
			TargetY = 1;
		}
		if (TargetY < 0)
		{
			TargetY = -1;
		}
	}
	Inputs::mouse_move((int)TargetX, (int)(TargetY));
}
void CoutOffset(LPCSTR name, DWORD offset)
{
	std::cout << "[" << name << "]" << " = 0x" << std::uppercase << std::hex << offset << std::endl;
}
void Coutfloat(LPCSTR name, float option)
{
	std::cout << "[" << name << "]" << " = " << std::dec << option << std::endl;
}

void Coutbool(LPCSTR name, int boolean)
{
	if (boolean == 1)
		std::cout << "[" << name << "]" << " = " << "ON" << std::endl;
	else
		std::cout << "[" << name << "]" << " = " << "OFF" << std::endl;
}
float ReadConfig(LPCSTR Option, bool Float)
{
	if (Float)
	{
		char cfg[10];
		GetPrivateProfileString(TEXT("Config"), Option, TEXT("0"), cfg, 10, FilePath);
		float opt = atof(cfg);
		return opt;
	}
	else
		return GetPrivateProfileInt(TEXT("Config"), Option, NULL, FilePath);
}
DWORD ReadInt(LPCTSTR Offsetname)
{
	DWORD Offset = GetPrivateProfileInt(TEXT("Offsets"), Offsetname, NULL, FilePath);
	CoutOffset(Offsetname, Offset);
	return Offset;
}
void ReadSettings()
{
	settings::aimbot = ReadConfig(TEXT("Active"), false);
	settings::autolock = ReadConfig(TEXT("AutoLock"), false);
	settings::aimknocked = ReadConfig(TEXT("Aimknocked"), false);
	settings::aimbothitbox = ReadConfig(TEXT("HitBox"), true);
	settings::aimspeed = ReadConfig(TEXT("AimSpeed"), true);
	settings::aimbotfov = ReadConfig(TEXT("Fov"), true);
	settings::aimlock = ReadConfig(TEXT("aimlock"), true);
	settings::aimbotdrawfov = ReadConfig(TEXT("DrawFov"), false);
	settings::aimbotdrawhitbox = ReadConfig(TEXT("DrawHitBox"), false);

	settings::teamBoxes = ReadConfig(TEXT("TeamBox"), false);
	settings::teamDistance = ReadConfig(TEXT("TeamDistance"), false);
	settings::teamSnaplines = ReadConfig(TEXT("TeamSnaplines"), false);
	settings::teamHealth = ReadConfig(TEXT("TeamHealth"), false);
	settings::teamShieldHealth = ReadConfig(TEXT("ShieldHealth"), false);
	settings::teamFilledbox = ReadConfig(TEXT("TeamFilledbox"), false);
	settings::teamKnocked = ReadConfig(TEXT("TeamKnocked"), false);

	settings::enemyBoxes = ReadConfig(TEXT("EnemyBoxes"), false);
	settings::enemyDistance = ReadConfig(TEXT("EnemyDistance"), false);
	settings::enemySnaplines = ReadConfig(TEXT("EnemySnaplines"), false);
	settings::enemyHealth = ReadConfig(TEXT("EnemyHealth"), false);
	settings::enemyShieldHealth = ReadConfig(TEXT("EnemyShieldHealth"), false);
	settings::enemyFilledbox = ReadConfig(TEXT("EnemyFilledbox"), false);
	settings::enemyKnocked = ReadConfig(TEXT("EnemyKnocked"), false);

	settings::c_enable = ReadConfig(TEXT("CrosshairEnable"), false);
	settings::crosshair = ReadConfig(TEXT("CrosshairStyle"), true);
	settings::size = ReadConfig(TEXT("Size"), true);
	settings::stroke = ReadConfig(TEXT("Stroke"), true);

	settings::boxtype = ReadConfig(TEXT("BoxType"), true);
	settings::healthbartype = ReadConfig(TEXT("HealthbarType"), true);
	settings::playersdis = ReadConfig(TEXT("PlayersDis"), true);

	settings::menux = ReadConfig(TEXT("MenuX"), true);
	settings::menuy = ReadConfig(TEXT("MenuY"), true);
	
}
