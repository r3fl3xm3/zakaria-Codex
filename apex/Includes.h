#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <vector>
#include <d3dx9math.h>
#pragma comment(lib, "d3dx9.lib")
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
#include <time.h>
#include <thread>
#include <map>

#define checkSetting(teamval, enemyval) (((gm.LocalPlayer.Team == player.Team) && teamval) || ((gm.LocalPlayer.Team != player.Team) && enemyval))
#define pasteColor(x) x.r, x.g, x.b
#define pasteColorA(x) x.r, x.g, x.b, x.a
