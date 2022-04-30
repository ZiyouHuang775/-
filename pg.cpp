//代码-WenChris所有
//由于有保密协议，弄乱了大部分代码，并且全数往左缩排
#include "esp.h"
#include "dry.h"
#include "mem.h"
#include "Struct.h"
#include "HookEngine.h"


ULONG64 g_decObj;
ULONG64 g_decGname1;
ULONG64 g_decGname2;
ULONG64 g_decuworld;
ULONG64 g_declevel;
ULONG64 g_decactorlist;
ULONG64 g_declocalplayer;
ULONG64 g_decplayercontroller;
ULONG64 g_decprop;
ULONG64 g_decgameinst;
DWORD_PTR ByPass20;
DWORD_PTR ByPass2;
DWORD_PTR VectorHook;
vector<CrcRecord*>* globalCrcUpdateHook = nullptr;

uint64_t UCanvas_offset = 0;

list<int> upper_part = { Bones::neck_01, Bones::Head, Bones::forehead };
list<int> right_arm = { Bones::neck_01, Bones::upperarm_r, Bones::lowerarm_r, Bones::hand_r };
list<int> left_arm = { Bones::neck_01, Bones::upperarm_l, Bones::lowerarm_l, Bones::hand_l };
list<int> spine = { Bones::neck_01, Bones::spine_02, Bones::spine_01, Bones::pelvis };

list<int> lower_right = { Bones::pelvis, Bones::thigh_r, Bones::calf_r, Bones::foot_r };
list<int> lower_left = { Bones::pelvis, Bones::thigh_l, Bones::calf_l, Bones::foot_l };
list<list<int>> skeleton = { upper_part, right_arm, left_arm, spine, lower_right, lower_left };

DWORD_PTR PhysX3_VectorX;
DWORD_PTR PhysX3_VectorY;
DWORD_PTR PhysX3_VectorZ;
DWORD_PTR pAimMemoryAddress;
DWORD_PTR pAimMemoryButton;

DWORD_PTR pAimMemoryAddressA;
DWORD_PTR pAimMemoryAddressB;
DWORD_PTR pAimMemoryButtonA;
FVector CameraLocationA{};
uint64_t aim_entity = 0;
float Dot = 0.0f;

//代码-WenChris所有
wstring item_name[] = {
XorStringW(L"AWM"), 
XorStringW(L"AKM"),
XorStringW(L"AUG"),
XorStringW(L"DBS"),
XorStringW(L"DP-28"),
XorStringW(L"G36C"),
XorStringW(L"GROZA"),
    XorStringW(L"Kar98K"),
XorStringW(L"M416"),
XorStringW(L"M16A4"),//代码-WenChris所有
XorStringW(L"M762"),
XorStringW(L"MK47"),
XorStringW(L"MP5K"),
//代码-WenChris所有
XorStringW(L"M249"),
XorStringW(L"M24"),
XorStringW(L"Mini14"),
XorStringW(L"P92"),
XorStringW(L"P1911"),
XorStringW(L"P18C"),
XorStringW(L"QBZ"),
XorStringW(L"QBU"),
XorS    tringW(L"R1895"),
    XorStringW(L"R45"),
XorStringW(L"SCAR-L"),
XorStringW(L"SLR"),
XorStringW(L"S686"),
XorS    tringW(L"S1897"),
XorStringW(L"S12K"),
XorStri ngW(L"UZI"),
XorStringW(L"UMP45"),
XorStringW(L"VSS"),
    XorStringW(L"Vector"),
    //代码-WenChris所有
    XorStringW(L"Win94"),
    XorStringW(L"野牛"),
    XorStringW(L"汤姆逊"),
    XorStringW(L"沙漠之鹰"),
    //代码-WenChris所有
    XorStringW(L"短管霰弹"),    
    XorStringW(L"信号枪"),
    XorStringW(L""),
          XorStringW(L"砍刀"),
    XorStringW(L"撬棍"),
    XorSt   ringW(L"镰刀"),
    XorStringW(L"平底锅"),
    XorStringW(L"破片手榴弹"),
    XorStringW(L"十字弩"),
XorStringW(L"5.56MM"),
XorStringW(L"7.62MM"),
XorStri ngW(L"9MM"),
XorStringW(L".45CP"),
XorStringW(L"12MM"),
XorStringW(L".300马格南"),
    XorStringW(L"信号弹"),
XorStringW(L"步枪快扩"),
XorStringW(L"步槍扩容"),
XorStringW(L"狙击快扩"),
XorString   W(L"轻型握把"),
XorStringW(L"拇指握把"),
XorStri ngW(L"狙击消音"),
XorStringW(L"直角握把"),
XorStringW(L"轻型握把"),
XorStringW(L"半截握把"),
XorStringW(L"垂直握把"),
Xor StringW(L"步枪补偿"),
XorStringW(L"狙击补偿"),
XorStringW(L"步枪消音"),
XorStringW(L"子弹袋"),
XorStri ngW(L"托腮板"),
XorStringW(L"战术枪托"),
XorStringW(L"激光瞄准"),
    XorStringW(L"狙击消音"),
XorStringW(L"急救包"),
XorStringW(L"医疗箱"),
XorStringW(L"止痛药"),
XorStringW(L"能量饮料"),
XorStringW(L"肾上腺素"),
XorStringW(L"红点"),
XorStringW(L"全息"),
XorStri         ngW(L"2x倍镜"),
XorStringW(L"3x倍镜"),
X   orStr  ingW(L"4x倍镜"),
XorStringW(L"6x倍镜"),
XorStr      ingW(L"8x倍镜"),
XorStringW(L"15x倍镜"), 
XorStringW(L"一级包"), 
         XorStringW(L"二级包"),
XorStringW(L"三级包"),
     XorStringW(L"一级頭"),
         XorStringW(L"二级頭"),
XorStringW(L"三级頭"),
    Xo  rStringW(L"一级甲"), 
XorStringW(L"二级甲"),
XorStringW(L"三级甲"),
XorStr  ingW(L"吉利服") 
};

// float GetDotDistance(int Xx, int Yy, int xX, int yY)
{
return (float)sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
// }

// uint32_t FilterID(uint32_t id)
// {
// for (uint32_t i = 0; i < G::ObjectCount; i++)
// {
if (G::ObjectInternalIndex[i] == id)
return G::ObjectType[i];
}
return 0;
}

bool FilterDeathItem(uint32_t id, float x, float y, uint32_t distance)//Death
{
for (uint32_t i = 0; i < G::ItemCounts; i++)
{
if (G::ItemInternalIndex[i] == id)
{
if ((G::ItemType2[i] == weapon_bq && G::IsShowWeapon_bq) ||
(G::ItemType2[i] == weapon_cf && G::IsShowWeapon_cf) ||
(G::ItemType2[i] == weapon_jj && G::IsShowWeapon_jj) ||
(G::ItemType2[i] == scope && G::IsShowScope) ||
(G::ItemType2[i] == medical && G::IsShowMedical) ||
(G::ItemType2[i] == ammo && G::IsShowAmmo) ||
(G::ItemType2[i] == hujia && G::IsShowHujia) ||
(G::ItemType2[i] == peijian && G::IsShowPeijian))
{
FLinearColor ItemColor;
if (G::ItemType2[i] == weapon_bq) {
ItemColor = { 1,0.5f,0,0.8f };
}
else if (G::ItemType2[i] == weapon_cf) {
ItemColor = { 1,0.5f,0.3f,0.8f };
}
else if (G::ItemType2[i] == weapon_jj) {
ItemColor = { 1, 0.27f, 0, 0.8f };
}
else if (G::ItemType2[i] == scope) {
ItemColor = { 0.97f,0.8f,0.678f,0.8f };
}
else if (G::ItemType2[i] == medical) {
ItemColor = { 0.27f,0.9f,0.178f,0.8f };
}
else if (G::ItemType2[i] == ammo) {
ItemColor = { 0.635f, 0.803f,0.35f,0.8f };
}
else if (G::ItemType2[i] == hujia) {
ItemColor = { 0.2f,0.5f,0.8f,0.8f };
}
else if (G::ItemType2[i] == peijian) {
ItemColor = { 0.635f, 0.803f,0.35f,0.8f };
}
if (G::ItemType[i] < 73)
{
if (item_name[G::ItemType[i]].c_str())
{
G::Draw->jzText(x, y, ItemColor, G::Draw->Roboto, XorStringW(L"%ws [%dM]"), item_name[G::ItemType[i]].c_str(), distance);
return true;
}
}
}
}
}
return false;
}
bool FilterDeathItemT(uint32_t id, float x, float y, uint32_t distance)//Death
{
for (uint32_t i = 0; i < G::ItemCounts; i++)
{
if (G::ItemInternalIndex[i] == id)
{
if ((G::ItemType2[i] == weapon_bq && G::IsShowWeapon_bq) ||
(G::ItemType2[i] == weapon_cf && G::IsShowWeapon_cf) ||
(G::ItemType2[i] == weapon_jj && G::IsShowWeapon_jj) ||
(G::ItemType2[i] == scope && G::IsShowScope) ||
(G::ItemType2[i] == medical && G::IsShowMedical) ||
(G::ItemType2[i] == ammo && G::IsShowAmmo) ||
// (G::ItemType2[i] == hujia && G::IsShowHujia) ||
// (G::ItemType2[i] == peijian && G::IsShowPeijian))
// {
// FLinearColor ItemColor;
// if (G::ItemType2[i] == weapon_bq) {
// ItemColor = { 1,0.5f,0,0.8f };
// }
// else if (G::ItemType2[i] == weapon_cf) {
// ItemColor = { 1,0.5f,0.3f,0.8f };
// }
// else if (G::ItemType2[i] == weapon_jj) {
// ItemColor = { 1, 0.27f, 0, 0.8f };
// }
// else if (G::ItemType2[i] == scope) {
// ItemColor = { 0.97f,0.8f,0.678f,0.8f };
// }
// else if (G::ItemType2[i] == medical) {
// ItemColor = { 0.27f,0.9f,0.178f,0.8f };
// }
// else if (G::ItemType2[i] == ammo) {
// ItemColor = { 0.635f, 0.803f,0.35f,0.8f };
// }
// else if (G::ItemType2[i] == hujia) {
// ItemColor = { 0.2f,0.5f,0.8f,0.8f };
// }
// else if (G::ItemType2[i] == peijian) {
// ItemColor = { 0.635f, 0.803f,0.35f,0.8f };
}
if (G::ItemType[i] < 73)
{
if (item_name[G::ItemType[i]].c_str())
{
G::Draw->jzText(x, y, ItemColor, G::Draw->Roboto, XorStringW(L"%ws"), item_name[G::ItemType[i]].c_str());
return true;
}
}
}
}
}
return false;
}

Vector3 WorldToScreen(Vector3 WorldLocation, DWORD_PTR CameraCacheL)
{
Vector3 Screenlocation = Vector3(0, 0, 0);
FRotator Rotation = RPM<FRotator>(CameraCacheL + OFFSET_RAROTION);
Vector3 vAxisX, vAxisY, vAxisZ;
D3DMATRIX tempMatrix = Rotation.GetAxesS();
vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
Vector3 vDelta = WorldLocation - RPM<Vector3>(CameraCacheL + OFFSET_LOCATION);
Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

if (vTransformed.z < 1.f)
vTransformed.z = 1.f;
float FovAngle = RPM<float>(CameraCacheL + OFFSET_FOV);
Screenlocation.x = G::ScreenCenterX + vTransformed.x * (G::ScreenCenterX / tanf(FovAngle * (float)PI / 360.f)) / vTransformed.z;
Screenlocation.y = G::ScreenCenterY - vTransformed.y * (G::ScreenCenterX / tanf(FovAngle * (float)PI / 360.f)) / vTransformed.z;
return Screenlocation;
}


FTransform GetBoneIndex(DWORD_PTR mesh, int index)
{
DWORD_PTR bonearray = RPM<uint64_t>(mesh + OFFSET_BONEARRY);
if (bonearray)
{
return  RPM<FTransform>(bonearray + (index * 0x30));
}
}

D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
D3DMATRIX pOut;
pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
// pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
// pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
// pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
// pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
// pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
// pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
// pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
// pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;
return pOut;
}

Vector3 GetBoneWithRotation(uint64_t mesh, int ID)
{
FTransform bone = GetBoneIndex(mesh, ID);
FTransform ComponentToWorld = RPM<FTransform>(mesh + OFFSET_COMPTOWOLRD);
D3DMATRIX Matrix;
Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
return Vector3(Matrix._41, Matrix._42, Matrix._43);
}

VOID HookJmp(ULONG64 GameAddress, ULONG64 MyAddress)
{
BYTE Jmp[] = { 0xFF,0x25,0x00,0x00,0x00,0x00 ,0x00,0x00 ,0x00,0x00 ,0x00,0x00 ,0x00,0x00 };
*(PULONG64)(Jmp + 6) = MyAddress;
WriteVirtual((uint64_t)GameAddress, (uint64_t)Jmp, sizeof(Jmp));
}

void LineTaceToHook()
{
BYTE shellcode[] = {
0xC7, 0x44, 0x24, 0x30, 0x00, 0x00, 0x00, 0x00,
0xC7, 0x44, 0x24, 0x34, 0x00, 0x00, 0x00, 0x00,
0xC7, 0x44, 0x24, 0x38, 0x00, 0x00, 0x00, 0x00 };
PCHAR HookBase = g_shellcode + 0x500;
VectorHook = G::Tslgame + OFFSET_LineHookTo;
// PhysX3_VectorX = (DWORD_PTR)HookBase + 4;
// PhysX3_VectorY = (DWORD_PTR)HookBase + 4 + 8;
// PhysX3_VectorZ = (DWORD_PTR)HookBase + 4 + 8 + 8;

WBT((DWORD_PTR)HookBase, (DWORD_PTR)shellcode, sizeof(shellcode));
HookJmp((DWORD_PTR)HookBase + sizeof(shellcode), VectorHook + 18);
HookJmp(VectorHook, (DWORD_PTR)HookBase);
}

bool LineTrace(DWORD_PTR APlayerControl, DWORD_PTR pEntity, Vector3 StartPos, Vector3 EndPos)
{
DWORD_PTR wr;
SIZE_T ls;
WPM<FLOAT>(PhysX3_VectorX, EndPos.x);
WPM<FLOAT>(PhysX3_VectorY, EndPos.y);
WPM<FLOAT>(PhysX3_VectorZ, EndPos.z);
// DWORD64 pPlayerController = APlayerControl;
// Vector3 pViewPoint = StartPos;
// Syscall(G::NtReadMemory_Index, (HANDLE)-1, (PVOID)(G::Tslgame + OFFSET_LineSightTo), &wr, sizeof(wr), &ls);
// if (ls > 0)
// {
// bool isVisible = reinterpret_cast<bool(__fastcall*)(DWORD_PTR pPlayerController, DWORD_PTR Entity, Vector3 * ViewPoint)> (G::Tslgame + OFFSET_LineSightTo)(pPlayerController, pEntity, &pViewPoint);
// return isVisible;
}
return false;
}
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有



//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有
string GetNames(uint64_t gnames, DWORD ID)
{
char Name[64] = { 0 };
ULONG IdDiv = ID / OFFSET_IDCALC;
ULONG Idtemp = ID % OFFSET_IDCALC;
ULONG64 Serial = RPM<uint64_t>(gnames + IdDiv * 0x8);
if (!Serial)
return "";
ULONG64 pName = RPM<uint64_t>(Serial + 0x8 * Idtemp);
if (!pName)
return "";
StringA names;
names = RPM<StringA>(pName + 0x10);
std::string str(names.buffer);
return str;
}

double __stdcall GetBulletDrop(double step, FWeaponTrajectoryConfig CurrentWeaponConfig)
{
double TGZ = 9.8;
double SST = CurrentWeaponConfig.SimulationSubstepTime;
double VDC = CurrentWeaponConfig.VDragCoefficient;
double BDS = CurrentWeaponConfig.BDS;
double STS = 100.f;
if (BDS <= 0.0 || SST <= 0.0 || VDC <= 0.0)
{
BDS = 1.0;
VDC = 0.75;
SST = 0.016;
}
double DP = 0;
for (double x = 0; x < step; x += SST)
{
DP = ((((TGZ * SST) * STS) * VDC) * BDS) + DP;
}
return DP;
}

Vector3 __stdcall GetPrediction(Vector3 TargetPos, uint64_t TargetActor, int Distance, FWeaponTrajectoryConfig CurrentWeaponConfig)//坐标 玩家指针 距离
{
Vector3 PredictedPos = { 0,0,0 };
FLOAT BulletSpeed = 0.0f, TimeScale = 0.0f;
BulletSpeed = CurrentWeaponConfig.InitialSpeed;
TimeScale = CurrentWeaponConfig.VDragCoefficient;
CurrentWeaponConfig.InitialSpeed, CurrentWeaponConfig.HitDamage, CurrentWeaponConfig.LowerClampDamage, C/////；//；sd000000isticCurve, CurrentWeaponConfig.RangeModifier, CurrentWeaponConfig.ReferenceDistance, CurrentWeaponConfig.TravelDistanceMax, CurrentWeaponConfig.bUseMaxDamageDistance, CurrentWeaponConfig.SimulationSubstepTime, CurrentWeaponConfig.VDragCoefficient, CurrentWeaponConfig.BDS, CurrentWeaponConfig.bUseAdvancedBallistics, CurrentWeaponConfig.IsPenetrable, CurrentWeaponConfig.DamageType);
Vector3 TargetActorS = RPM<Vector3>(TargetActor + OFFSET_Veloctity);
double flyTime = Distance / BulletSpeed;
PredictedPos = TargetPos + TargetActorS * flyTime;
// flyTime /= TimeScale;
// PredictedPos.z = PredictedPos.z + (GetBulletDrop(flyTime / 10.0, CurrentWeaponConfig) - (Distance >= 320.0f ? 0 : 15.6f) + (TargetActorS.z * flyTime * 0.0360f));
// return PredictedPos;
}

FVector ToFRotator(FVector Ver)
{
FVector Rot;
// float RADPI;
// RADPI = (float)(180.f / PI);
// Rot.Y = (float)atan2f(Ver.Y, Ver.X) * RADPI;
// Rot.X = (flo第三方身份后，at)atan2f(Ver.Z, sqrtf(powf(Ver.X, 2.0) + powf(Ver.Y, 2.0))) * RADPI;
// Rot.Z = 0;
// return(Rot);
}

FVector Clamp(FVector Ver)
{
// FVector Result;
// Result = Ver;
// if (Result.X > 180)
// {
// Result.X -= 360;
// }
// else if (Result.X < -180)
// {
// Result.X sgfmyaguVdw+= 360;
// }
// if (Result.Y > 180)
// {
// Result.Y -=fgiysgfusf 360;
// }
// else if (Result.Y < -180)
// {
// Result.Y += 360;
// }
// if (Result.X < -89.)
// {
// Result.X = -89;
}
if (Result.X > 89)
{
Result.X = 89;
}
while (Result.Y < 180.f)
{
Result.Y += 360.f;
}
while (Result.Y > 180.f)
{
Result.Y -= 360.f;
}
Result.Z = 0;
return(Result);
}
void ZZHook()
{
PCHAR uAddnull = g_shellcode + 0x700;
ULONG64 ZZcall = G::Tslgame + OFFSET_BulletTrack;
ULONG64 JMP = G::Tslgame + OFFSET_BulletTrackJmp;
pAimMemoryButtonA = (DWORD_PTR)uAddnull;
pAimMemoryAddressA = (DWORD_PTR)uAddnull + 0x10;//x
pAimMemoryAddressB = (DWORD_PTR)uAddnull + 0x20;//x
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有
//代码-WenChris所有//代码-WenChris所有//代码-WenChris所有//代码-WenChris所有//代码-WenChris所有//代码-WenChris所有
BYTE Aimbot[] = { 0x49, 0x8B, 0xCF, 0x53, 0x52, 0x48, 0xBA, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x3A, 0x00, 0x74, 0x15,
//  0x48, 0x8B, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x18,
//  0x48, 0x8B, 0x1D, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x58,
 0x04, 0x0F, 0xB6, 0x81, 0x81, 0x0C, 0x00, 0x00, 0x5A, 0x5B,
 0x0F, 0xB6, 0xD0, 0x49, 0x8B, 0xCF, 0xFF, 0x25, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
ULONG64 HookAddress = (ULONG64)g_shellcode + 0x800;
ULONG64 PASSPASS = G::Tslgame + OFFSET_BulletTrackJe;
*(PULONG)(Aimbot + 7) = pAimMemoryButtonA;
*(PULONG)(Aimbot + 23) = (ULONG64)pAimMemoryAddressA - (HookAddress + 27);
*(PULONG)(Aimbot + 33) = (ULONG64)pAimMemoryAddressB - (HookAddress + 37);
*(PULONG64)(Aimbot + 62) = JMP;
WriteVirtual(HookAddress, (ULONG64)Aimbot, sizeof(Aimbot));
HookJmp(ZZcall, HookAddress);
}

void BulletTrack(uint64_t local, uint64_t entity, int Distance, uint64_t playercontroller, Vector3 localpos, uint64_t carema)
{
Vector3 FixBreathPos = Vector3(0.0f, 0.0f, 0.0f);
FWeaponTrajectoryConfig CurrentWeaponConfig;
uint64_t pWeapon;
uint32_t WeaponBj = 0;
if (!entity)
return;
// uint64_t pWeaponProcessor = RPM<uint64_t>(local + OFFSET_WEAPONfjdytfiaPROCESSOR);
// uint64_t pEquippedWeapons = RPM<uint64_t>(pWeaponfhiusgfhjabsfhProcessor + OFFSET_EQUIPPEDWEAPON);
// byte pCurrentWeaponIndex = RPM<byte>(pWsfhitfisdbeaponProcessor + OFFSET_CURRENTWEAPONINDEX);
// if (pCurrentWeaponIndefesgkufgiwagefcisx >= 0 && pCurrentWeaponIndex < 3)
// {
// pWeapon = RPM<uint64_t>(pEquippedWeapons + pCurrentWeaponIndex * 8);
// if (pWeapon)
// {szgfiayfuy
// CurrentWeaf,sjgiugfiagponConfig = RPM<FWeaponTrajectoryConfig>(RPM<DWORD_PTR>(pWeapon + OFFSET_WeaponTraj) + OFFSET_TrajConfig);
// }
// }
// else
{
return;
}

Vector3 current;
if (MyGetAsyncKeyState2(VK_SHIFT) != 0 && (G::BoneArry.size() > 3 && G::BoneArry.at(3).show == true)) {
current = G::BoneArry.at(3).pos;
}
else
{
for (size_t i = 0; i < G::BoneArry.size(); i++)
{
if (G::BoneArry.at(i).show == true)
{
current = G::BoneArry.at(i).pos;
break;
}
}
}
if (current.x == 0.0f && current.y == 0.0f && current.z == 0.0f && G::BoneArry.size() > 3)
{
if (MyGetAsyncKeyState2(VK_SHIFT) != 0)
{
current = G::BoneArry.at(3).pos;
}
else
{
for (size_t i = 0; i < G::BoneArry.size(); i++)
{
if (G::BoneArry.at(i).show == true)
{
current = G::BoneArry.at(i).pos;
break;
}
}
}
}
if (current.x != 0.0f && current.y != 0.0f && current.z != 0.0f) {
current = GetPrediction(current, entity, Distance, CurrentWeaponConfig);

Vector3 localeye = GetBoneWithRotation(RPM<uint64_t>(local + OFFSET_MESH), Bones::eye_r);
bool currentvis = LineTrace(playercontroller, entity, localeye, current);
if (!currentvis)
{
return;
}
Vector3 PlayerPos = current;

FLOAT RADPI = 180 / PI;
Vector3 BUpos = current - localpos;
FLOAT BTx = atan2(BUpos.y, BUpos.x) * RADPI;
FLOAT BTy = atan2(BUpos.z, sqrt(BUpos.x * BUpos.x + BUpos.y * BUpos.y)) * RADPI;

WPM<float>(pAimMemoryAddressA, BTy);
WPM<float>(pAimMemoryAddressB, BTx);


if (RPM<float>(pAimMemoryAddressA) != 0.f && RPM<float>(pAimMemoryAddressB) != 0.f)
{
WPM<int>(pAimMemoryButtonA, 1);
}
}
else
{
WPM<int>(pAimMemoryButtonA, 0);
}
}

void AimHook()
{
PCHAR uAddnull = g_shellcode + 0x600;
pAimMemoryButton = (DWORD_PTR)uAddnull;
pAimMemoryAddress = (DWORD_PTR)uAddnull + 0x10;
// BYTE Aimbot[] = { 0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//  0x83, 0x38, 0x00, 0x58, 0x74, 0x12, 0x48, 0xBA, 0x89, 0x67,
//  0x45, 0x23, 0x01, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x12, 0x48,
//  0x89, 0x54, 0x24, 0x30, 0xEB, 0x9A
// };
// ULONG64 HookAddress = (ULONG64)(G::Tslgame + OFFSET_AimBotCall);
// *(PULONG64)(Aimbot + 2) = pAimMemoryButton;
// *(PULONG64)(Aimbot + 18) = pAimMemoryAddress;
// WriteVirtual(HookAddress, (ULONG64)Aimbot, sizeof(Aimbot));
// BYTE HOOK[] = { 0x50,0x31,0xc0,0x74,0x45 };
// WriteVirtual(vdgkuyelrgbv,dkfhghsg(ULONG64)G::Tslgame + OFFSET_AIMHOOK, (ULONG64)HOOK, sizeof(HOOK));
// }fdsgs

// void AgdsfgimBot(uint64_t local, uint64_t entity, int Distance, uint64_t playercontroller, Vector3 localpos, uint64_t carema)
// {dfgsd
// Vectorg3 FixBreathPos = Vector3(0.0f, 0.0f, 0.0f);
// FWeapondfgTrajectoryConfig CurrentWeaponConfig;
// uint64_t psWeapon;
// uint32_t WedgaponBj = 0;
// if (!entity)dg
// return;sg
// uint64_t gpWeaponProcessor = RPM<uint64_t>(local + OFFSET_WEAPONPROCESSOR);
// uint64_t psdEquippedWeapons = RPM<uint64_t>(pWeaponProcessor + OFFSET_EQUIPPEDWEAPON);
// byte pCurrengtWeaponIndex = RPM<byte>(pWeaponProcessor + OFFSET_CURRENTWEAPONINDEX);
// if (pCurrentWsdgeaponIndex >= 0 && pCurrentWeaponIndex < 3)
// {fg
// pWedapon = RPM<uint64_t>(pEquippedWeapons + pCurrentWeaponIndex * 8);
// if (gpWeapon)
// {sg
// CursfrentWeaponConfig = RPM<FWeaponTrajectoryConfig>(RPM<DWORD_PTR>(pWeapon + OFFSET_WeaponTraj) + OFFSET_TrajConfig);
gsdfh
// if (RPM<float>(pWeapon + OFFSET_ISSCOPE) == 1.0f)
// {hh
// uindht64_t localbreath = RPM<uint64_t>(local + OFFSET_ScopeCarmera);
// floatdh BreathRotX = RPM<FLOAT>(localbreath + OFFSET_BREATH);
// float BreathRotY = RPM<FLOAT>(localbreath + OFFSET_BREATH + 4);
// if (BrehdathRotY > -10.f && BreathRotY < 10.f && BreathRotX > -10.f && BreathRotX < 10.f)
// FixBreathdgfhPos = Vector3(BreathRotX, BreathRotY, 0);
// }hgf
// // }hgf
// }gfhh
// elsedfg
// {dhfgh
// returnfdhg;
// }ffg
// Vecthor3 current;
// if (MfhgdhyGetAsyncKeyState2(VK_SHIFT) != 0 && (G::BoneArry.size() > 3 && G::BoneArry.at(3).show == true)) {
// current = fghgfG::BoneArry.at(3).pos;
// }hg
// elsfhgfe
// {hfg
// for (size_t i = 0; i < G::BoneArry.size(); i++)
// {hgf
// if (hgG::BoneArry.at(i).show == true)
// {fhgh
// curregfnt = G::BoneArry.at(i).pos;
// break;hfd
// }hfd
// }fhg
// }hfg
// if (hfgcurrent.x == 0.0f && current.y == 0.0f && current.z == 0.0f && G::BoneArry.size() > 3)
// {hfg
// if (hfgMyGetAsyncKeyState2(VK_SHIFT) != 0)
// {hgf
// currhgent = G::BoneArry.at(3).pos;
// }ghf
// elsefhgf
// {hgf
for (size_t i = 0; i < G::BoneArry.size(); i++)
{
if (G::BoneArry.at(i).show == true)
{
current = G::BoneArry.at(i).pos;
break;
}
}
}
}
if (current.x != 0.0f && current.y != 0.0f && current.z != 0.0f) {
current = GetPrediction(current, entity, Distance, CurrentWeaponConfig);

// Vector3 mzPoint = WorldToScreen(current, carema);
// if (G::IsShowPrePos) //預苗顯示
// {
// G::Draw->AHudDrawRect(G::Draw->AHUDuobject, FLinearColor(1, 0.5, 0.2, 1), mzPoint.x, mzPoint.y, 6, 6);
// }
// Vector3 localeye = GetBoneWithRotation(RPM<uint64_t>(local + OFFSET_MESH), Bones::eye_r);
// bool currentvis = LineTrace(playercontroller, entity, localeye, current);
// if (!currentvis)
// {
// return;
// }
// Vector3 PlayerPos = current;
// Vector3 AngLocalAngles = { 0.f,0.f,0.f };

// Vector3 Delta = RPM<Vector3>(carema + OFFSET_LOCATION);
// Delta = (PlayerPos - Delta).ToFRotator();
// Vector3 AngDelta = (Delta - AngLocalAngles);
// FRotator FAngDelta = FRotator(AngDelta.x, AngDelta.y, AngDelta.z);
// FAngDelta.Clamp();
// AngDelta = Vector3(FAngDelta.Pitch, FAngDelta.Yaw, FAngDelta.Roll);
// AngLocalAngles = AngLocalAngles + AngDelta;


// AngLocalAngles.x = AngLocalAngles.x + FixBreathPos.x;
// AngLocalAngles.y = AngLocalAngles.y + FixBreathPos.y;



// WPM<float>(pAimMemoryAddress, AngLocalAngles.x);
// WPM<float>(pAimMemoryAddress + 4, AngLocalAngles.y);

// if (RPM<float>(pAimMemoryAddress) != 0.f && RPM<float>(pAimMemoryAddress + 4) != 0.f)
// {
// WPM<int>(pAimMemoryButton, 1);
// }
// }
// else
// {
// WPM<int>(pAimMemoryButton, 0);
// }
// }

// int iiii = 0;
// void AimBotA(uint64_t local, uint64_t entity, int Distance, uint64_t playercontroller, Vector3 localpos, uint64_t carema)
// {
// bool stShift = false;
// Vector3 FixBreathPos = Vector3(0.0f, 0.0f, 0.0f);
// FWeaponTrajectoryConfig CurrentWeaponConfig;
// uint64_t pWeapon;
// uint32_t WeaponBj = 0;
// if (!entity)
// return;
// uint64_t pWeaponProcessor = RPM<uint64_t>(local + OFFSET_WEAPONPROCESSOR);
// uint64_t pEquippedWeapons = RPM<uint64_t>(pWeaponProcessor + OFFSET_EQUIPPEDWEAPON);
// BYTE pCurrentWeaponIndex = RPM<BYTE>(pWeaponProcessor + OFFSET_CURRENTWEAPONINDEX);
// if (pCurrentWeaponIndex >= 0 && pCurrentWeaponIndex < 3)
// {
// pWeapon = RPM<uint64_t>(pEquippedWeapons + pCurrentWeaponIndex * 8);
// if (pWeapon)
// {
// CurrentWeaponConfig = RPM<FWeaponTrajectoryConfig>(RPM<DWORD_PTR>(pWeapon + OFFSET_WeaponTraj) + OFFSET_TrajConfig);

// if (RPM<float>(pWeapon + OFFSET_ISSCOPE) == 1.0f)
// {
// uint64_t localbreath = RPM<uint64_t>(local + OFFSET_ScopeCarmera);
// float BreathRotX = RPM<FLOAT>(localbreath + OFFSET_BREATH);
// float BreathRotY = RPM<FLOAT>(localbreath + OFFSET_BREATH + 4);
// if (BreathRotY > -10.f && BreathRotY < 10.f && BreathRotX > -10.f && BreathRotX < 10.f)
// FixBreathPos = Vector3(BreathRotX, BreathRotY, 0);
}
}
}
else
{
return;
}

Vector3 current;
if (MyGetAsyncKeyState2(VK_SHIFT) & 0x8000 && (G::BoneArry.size() > 3 && G::BoneArry.at(3).show == true)) {
current = G::BoneArry.at(3).pos;
stShift = true;
}
else
{
if (G::BoneArry.size() > 10)
{
for (size_t i = 0; i < G::BoneArry.size(); i++)
{
// if (G::BoneArry.at(i).show == true)
// {
// current = G::BoneArry.at(i).pos;
// break;
// }
// }
// }
// }
// if (current.x == 0.0f && current.y == 0.0f && current.z == 0.0f && G::BoneArry.size() > 3)
// {
// if (MyGetAsyncKeyState2(VK_SHIFT) & 0x8000)
// {
// current = G::BoneArry.at(3).pos;
// }
// else
// {
// current = G::BoneArry.at(1).pos;
// }
// }
// if (current.x != 0.0f && current.y != 0.0f && current.z != 0.0f) {
// current = GetPrediction(current, entity, Distance, CurrentWeaponConfig);

// Vector3 mzPoint = WorldToScreen(current, carema);
// G::Draw->Line(mzPoint.x - 4, mzPoint.y - 4, mzPoint.x + 4, mzPoint.y + 4, FLinearColor(1, 0.2, 0.2, 1), 1);
// G::Draw->Line(mzPoint.x - 4, mzPoint.y + 4, mzPoint.x + 4, mzPoint.y - 4, FLinearColor(1, 0.2, 0.2, 1), 1);

// //Vector3 localeye = RPM<Vector3>(carema + OFFSET_LOCATION);
// Vector3 localeye = GetBoneWithRotation(RPM<uint64_t>(local + OFFSET_MESH), Bones::eye_r);
bool currentvis = LineTrace(playercontroller, entity, localeye, current);
if (!currentvis)
{
WPM<int>(pAimMemoryButton, 0);
return;
}
Vector3 PlayerPos = current;
Vector3 AngLocalAngles = { 0.f,0.f,0.f };

Vector3 Delta = RPM<Vector3>(carema + OFFSET_LOCATION);
Delta = (PlayerPos - Delta).ToFRotator();
Vector3 AngDelta = (Delta - AngLocalAngles);
FRotator FAngDelta = FRotator(AngDelta.x, AngDelta.y, AngDelta.z);
FAngDelta.Clamp();
AngDelta = Vector3(FAngDelta.Pitch, FAngDelta.Yaw, FAngDelta.Roll);
AngLocalAngles = AngLocalAngles + AngDelta;

if (stShift == false)
{
AngLocalAngles.x = AngLocalAngles.x + FixBreathPos.x;
AngLocalAngles.y = AngLocalAngles.y + FixBreathPos.y;
iiii = 0;
}
else
{
if (MyGetAsyncKeyState2(VK_LBUTTON) & 0x8000)
{
if (iiii >= 10)
{
iiii = 2;
}

AngLocalAngles.x = AngLocalAngles.x + (FixBreathPos.x * (1.f - 0.099f * iiii));
AngLocalAngles.y = AngLocalAngles.y + (FixBreathPos.y * (1.f - 0.099f * iiii));

iiii++;
}
else
{
AngLocalAngles.x = AngLocalAngles.x + FixBreathPos.x;
AngLocalAngles.y = AngLocalAngles.y + FixBreathPos.y;
iiii = 1;
}
}

WPM<float>(pAimMemoryAddress, AngLocalAngles.x);
WPM<float>(pAimMemoryAddress + 4, AngLocalAngles.y);

if (RPM<float>(pAimMemoryAddress) != 0.f/* && RPM<float>(pAimMemoryAddress + 4) != 0.f*/)
{
WPM<int>(pAimMemoryButton, 1);
}
}
else
{
WPM<int>(pAimMemoryButton, 0);
}
}
void DrawBone(uint64_t local, uint64_t entity, uint64_t playercontroller, uint64_t CameraManager, bool aimmm)
{
uint64_t mesh = RPM<uint64_t>(entity + OFFSET_MESH);
Vector3 localeye = GetBoneWithRotation(RPM<uint64_t>(local + OFFSET_MESH), Bones::eye_r);
Vector3 neckpos = GetBoneWithRotation(mesh, Bones::neck_01);
Vector3 pelvispos = GetBoneWithRotation(mesh, Bones::pelvis);
Vector3 previous(0, 0, 0);
Vector3 current, p1, c1;
bool previousvis = false, currentvis = false;

for (auto a : skeleton)
{
previous = Vector3(0, 0, 0);
for (int bone : a)
// {
// current = bone == Bones::neck_01 ? neckpos : (bone == Bones::pelvis ? pelvispos : GetBoneWithRotation(mesh, bone));
// curregssntvis = LineTrace(playercontroller, entgfdlocaleye, current);
// if (aimmm)
// {gsfg
// BoneLigfsst bn;
// if gfs(bone == Bones::spine_02 || bone == Bones::spine_03)
// {df
// bn.show = cugsrrentvis;
// bn.bone = gsbone;
// bn.pos =gf current;
// G::BogsfneArry.insert(G::BoneArry.begin(), bn);
// }
// elssfe
// {sg
// bn.show = cfgurrentvis;
// bn.bone =fs bone;
// bn.pos gd= current;
// G::BgsdoneArry.push_back(bn);
// }gfd
// }
// if (previetrous.x == 0.f)
// {
// previoutrsvis = currentvis;
// previerous = current;
// continue;
// }esrg
// p1 = WorldtToScreen(previous, CameraManager);
// c1 = WorrsldToScreen(current, CameraManager);
// if (pgsereviousvis && currentvis) {
// G::sdDraw->AHudDrawLine(G::Draw->AHUDuobject, p1.x, p1.y, c1.x, c1.y, FLinearColor(1, 1, 0, 1), 1.5f);
// }df
// else {
// G::Draw->AHudDrawLine(G::Draw->AHUDuobject, p1.x, p1.y, c1.x, c1.y, FLinearColor(1, 1, 1, 1), 1.5f);
// }
// previous = current;
// previousvis = currentvis;
}
}
}

ULONG RtlHashString_ImulMagicA(IN CONST PCHAR s, BOOLEAN bIsBadReadPtr)
{
DWORD_PTR write;
SIZE_T ls;
if (bIsBadReadPtr == TRUE)
{
Syscall(G::NtReadMemory_Index, (HANDLE)-1, (PVOID)s, &write, sizeof(write), &ls);
if (ls <= 0)
{
return 0;
}
}

ULONG Reuslt = 0;
SIZE_T i = -1;
while (TRUE)
{
i += 1;
if (i > 64)
return 0;
if (s[i] == 0x00)
{
break;
}
else
{
Reuslt *= 0x1003f;
Reuslt += s[i];
}
}
return Reuslt;
}

uint64_t FindFonts(uint64_t GName, char* Foot) {
uint64_t GObjects = G::Tslgame + OBJECT;
uint64_t GObjectsTArray = decrypt_object(GObjects);
for (int i = 40000; i < 100000; i++) {
uint64_t GObjects = RPM<uint64_t>(GObjectsTArray + 0x18 * i);
int32_t FName = dectypt_id(RPM<int32_t>(GObjects + OFFSET_ID));
if (GetNames(GName, FName) == Foot)
{
return GObjects;
break;
}
}
}

void Key()
{
if (MyGetAsyncKeyState2(VK_HOME) & 1)
{
G::IsShowEMenu = !G::IsShowEMenu;
if (G::IsShowEMenu)
{
G::IsShowCMenu = false;
}
}
if (MyGetAsyncKeyState2(VK_INSERT) & 1)
{
G::IsShowCMenu = !G::IsShowCMenu;
if (G::IsShowCMenu)
{
G::IsShowEMenu = false;
}
}
if (MyGetAsyncKeyState2(VK_F1) & 1)
{
G::IsShowPlayer = !G::IsShowPlayer;
}
if (MyGetAsyncKeyState2(VK_F2) & 1)
{
G::Is3DPlayer = !G::Is3DPlayer;
}
if (MyGetAsyncKeyState2(VK_F3) & 1)
{
G::IsShowPrePos = !G::IsShowPrePos;//育苗顯示
}
if (MyGetAsyncKeyState2(VK_F4) & 1)
{
G::IsMinimap = !G::IsMinimap;
}
if (MyGetAsyncKeyState2(VK_F5) & 1)
{
G::IsShowItem = !G::IsShowItem;
}
if (MyGetAsyncKeyState2(VK_F6) & 1)
{
G::IsShowVehicle = !G::IsShowVehicle;
}
if (MyGetAsyncKeyState2(VK_F7) & 1)
{
G::IsShowAir = !G::IsShowAir;
}
if (MyGetAsyncKeyState2(VK_F8) & 1)
{
G::IsShowDeath = !G::IsShowDeath;
}
if (MyGetAsyncKeyState2(VK_F9) & 1)
{
G::IsAimBot = !G::IsAimBot;
if (G::IsAimBot)
{
G::BulletTrack = false;
}
}
if (MyGetAsyncKeyState2(VK_F10) & 1)
{
G::BulletTrack = !G::BulletTrack;
if (G::BulletTrack)
{
G::IsAimBot = false;
}
}
if (MyGetAsyncKeyState2(VK_F11) & 1)
{
G::IsSoecPos = !G::IsSoecPos;
}
if (MyGetAsyncKeyState2(VK_F12) & 1)
{
G::PlayerWeapon = !G::PlayerWeapon;
}
if (MyGetAsyncKeyState2(VK_CAPITAL) & 1)
{
G::KillTeam = !G::KillTeam;
}
if ((MyGetAsyncKeyState2(VK_LCONTROL) & 0x8000 && MyGetAsyncKeyState2(49) & 1))
{
G::IsPlay = !G::IsPlay;
}
if ((MyGetAsyncKeyState2(VK_LCONTROL) & 0x8000 && MyGetAsyncKeyState2(50) & 1))
{
G::IsPeroptions = !G::IsPeroptions;
}
if ((MyGetAsyncKeyState2(VK_LCONTROL) & 0x8000 && MyGetAsyncKeyState2(51) & 1))
{
G::IsAimMuen = !G::IsAimMuen;
}
}

void ShowMenu()
{
float Top = 70;
float Lift = G::ScreenCenterX * 2.f - 570;
FLinearColor MemuColor = { 1,1,1,1 }, onColor = { 1,1,0,1 }, offColor = { 1,1,1,1 };
int RectA;
if (G::IsShowEMenu)
{
Top += 35;
Lift += 5;

G::Draw->AHudDrawRect(G::Draw->AHUDuobject, FLinearColor(0, 0, 0, 0.6f), Lift, Top + 5, 550, 35);
G::Draw->Text(Lift, Top, FLinearColor(1, 1, 1, 1), G::Draw->TSLFont, XorStringW(L"  Home Display/Hide - Engine Initialization.....")); //US

Top += 40;

if (G::IsPeroptions || G::IsPlay || G::IsAimMuen)
// {
// RectA = 130;
// }
// else
// {
// RectA = 50;
// }

// G::Draw->AHudDrawRect(G::Draw->AHUDuobject, FLinearColor(0, 0, 0, 0.5f), Lift, Top, 550, RectA);
// Top += 3;
// float Top2 = Top;
// float Top3 = Top;

// G::IsPlay ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift, Top, MemuColor, G::Draw->Roboto, XorStringW(L"    Player-SETTING-C+1  [%s]"), G::IsPlay ? XorStringW(L"-") : XorStringW(L"+"));
// Top += 22;
// G::Draw->AHudDrawLine(G::Draw->AHUDuobject, Lift, Top, Lift + 550, Top, MemuColor, 0);
// Top += 4;
// G::IsPeroptions ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift + 190, Top2, MemuColor, G::Draw->Roboto, XorStringW(L"    Esp-SETTING-C+2  [%s]"), G::IsPeroptions ? XorStringW(L"-") : XorStringW(L"+"));
// Top2 += 26;

// G::IsAimMuen ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift + 355, Top3, MemuColor, G::Draw->Roboto, XorStringW(L"    Aimbot-SETTING-C+3  [%s]"), G::IsAimMuen ? XorStringW(L"-") : XorStringW(L"+"));
// Top3 += 26;

// G::Draw->AHudDrawText(G::Draw->AHUDuobject, XorStringW(L"    PS-A: [Alt]-C: [Ctrl] - China[INSERT] | English[Home]                              Copyright(c) Xdrv Inc."), FLinearColor(1, 0.647f, 0, 1), Lift, Top + 77, G::Draw->Roboto, 1.06f, false);
// if (G::IsPlay)
// {
// G::IsShowPlayer ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift, Top, MemuColor, G::Draw->Roboto, XorStringW(L"    Skeleton      F1           [%s]"), G::IsShowPlayer ? XorStringW(L"√") : XorStringW(L"×"));
// Top += 18;

// G::Is3DPlayer ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift, Top, MemuColor, G::Draw->Roboto, XorStringW(L"    Box              F2           [%s]"), G::Is3DPlayer ? XorStringW(L"√") : XorStringW(L"×"));
// Top += 18;

// G::IsShowPrePos ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift, Top, MemuColor, G::Draw->Roboto, XorStringW(L"    Showpos     F3           [%s]"), G::IsShowPrePos ? XorStringW(L"√") : XorStringW(L"×"));
// Top += 18;

// G::IsMinimap ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift, Top, MemuColor, G::Draw->Roboto, XorStringW(L"    Minimap      F4           [%s]"), G::IsMinimap ? XorStringW(L"√") : XorStringW(L"×"));
// Top += 18;
// }
// if (G::IsPeroptions)
// {
// G::IsShowItem ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift + 190, Top2, MemuColor, G::Draw->Roboto, XorStringW(L"    Items           F5       [%s]"), G::IsShowItem ? XorStringW(L"√") : XorStringW(L"×"));
// Top2 += 18;

// G::IsShowVehicle ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift + 190, Top2, MemuColor, G::Draw->Roboto, XorStringW(L"    Vehicle        F6       [%s]"), G::IsShowVehicle ? XorStringW(L"√") : XorStringW(L"×"));
// Top2 += 18;

// G::IsShowAir ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift + 190, Top2, MemuColor, G::Draw->Roboto, XorStringW(L"    Airdrop        F7       [%s]"), G::IsShowAir ? XorStringW(L"√") : XorStringW(L"×"));
// Top2 += 18;

// G::IsShowDeath ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift + 190, Top2, MemuColor, G::Draw->Roboto, XorStringW(L"    Lootbox       F8       [%s]"), G::IsShowDeath ? XorStringW(L"√") : XorStringW(L"×"));
Top2 += 18;
}
if (G::IsAimMuen)
{
G::IsAimBot ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift + 355, Top3, MemuColor, G::Draw->Roboto, XorStringW(L"    AimBot            F9          [%s] "), G::IsAimBot ? XorStringW(L"√") : XorStringW(L"×"));
Top3 += 18;

G::BulletTrack ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift + 355, Top3, MemuColor, G::Draw->Roboto, XorStringW(L"    Bllult               F10         [%s]"), G::BulletTrack ? XorStringW(L"√") : XorStringW(L"×"));
Top3 += 18;

G::IsSoecPos ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift + 355, Top3, MemuColor, G::Draw->Roboto, XorStringW(L"    recoil               F11         [%s]"), G::IsSoecPos ? XorStringW(L"√") : XorStringW(L"×"));
// Top3 += 18;

// G::PlayerWeapon ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift + 355, Top3, MemuColor, G::Draw->Roboto, XorStringW(L"    Display            F12        [%s]"), G::PlayerWeapon ? XorStringW(L"√") : XorStringW(L"×"));
Top3 += 18;
}
}

if (G::IsShowCMenu)
{

Top += 35;
Lift += 5;

G::Draw->AHudDrawRect(G::Draw->AHUDuobject, FLinearColor(0, 0, 0, 0.6f), Lift, Top + 5, 550, 35);
// G::Draw->Text(Lift, Top, FLinearColor(1, 1, 1, 1), G::Draw->TSLFont, XorStringW(L"  Insert 顯示/隱藏 - 引擎初始化成功....."));

// Top += 40;

// if (G::IsPeroptions || G::IsPlay || G::IsAimMuen)
// {
// RectA = 130;
// }
// else
// {
// RectA = 50;
// }

// G::Draw->AHudDrawRect(G::Draw->AHUDuobject, FLinearColor(0, 0, 0, 0.5f), Lift, Top, 550, RectA);
// Top += 3;dhugfdkb x
// float Top2 = Top;
// float Top3 = Top;

// G::IsPlay ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift, Top, MemuColor, G::Draw->Roboto, XorStringW(L"    玩 家 設 置-C+1    [%s]"), G::IsPlay ? XorStringW(L"-") : XorStringW(L"+"));
// Top += 22;
// G::Draw->AHudDrawLine(G::Draw->AHUDuobject, Lift, Top, Lift + 550, Top, MemuColor, 0);
// Top += 4;
// G::IsPeroptions ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift + 190, Top2, MemuColor, G::Draw->Roboto, XorStringW(L"    透 視 設 置-C+2    [%s]"), G::IsPeroptions ? XorStringW(L"-") : XorStringW(L"+"));
// Top2 += 26;

// G::IsAimMuen ? MemuColor = onColor : MemuColor = offColor;
// G::Draw->Text(Lift + 355, Top3, MemuColor, G::Draw->Roboto, XorStringW(L"         自 瞄 設 置-C+3      [%s]"), G::IsAimMuen ? XorStringW(L"-") : XorStringW(L"+"));
// Top3 += 26;

// G::Draw->AHudDrawText(G::Draw->AHUDuobject, XorStringW(L"    PS-A: [Alt]-C: [Ctrl] - 中文[INSERT] | 英文[Home]                              Copyright(c) Xdrv Inc."), FLinearColor(1, 0.647f, 0, 1), Lift, Top + 77, G::Draw->Roboto, 1.06f, false);
// if (G::IsPlay)
// {
G::IsShowPlayer ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift, Top, MemuColor, G::Draw->Roboto, XorStringW(L"    骨骼透視    F1      [%s]"), G::IsShowPlayer ? XorStringW(L"開") : XorStringW(L"關"));
Top += 18;

G::Is3DPlayer ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift, Top, MemuColor, G::Draw->Roboto, XorStringW(L"    方框透視    F2      [%s]"), G::Is3DPlayer ? XorStringW(L"開") : XorStringW(L"關"));
Top += 18;

G::IsShowPrePos ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift, Top, MemuColor, G::Draw->Roboto, XorStringW(L"    預苗顯示    F3      [%s]"), G::IsShowPrePos ? XorStringW(L"開") : XorStringW(L"關"));
Top += 18;

G::IsMinimap ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift, Top, MemuColor, G::Draw->Roboto, XorStringW(L"    迷你地圖    F4      [%s]"), G::IsMinimap ? XorStringW(L"開") : XorStringW(L"關"));
Top += 18;
}
if (G::IsPeroptions)
{
G::IsShowItem ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift + 190, Top2, MemuColor, G::Draw->Roboto, XorStringW(L"    物品透透視   F5      [%s]"), G::IsShowItem ? XorStringW(L"開") : XorStringW(L"關"));
Top2 += 18;

G::IsShowVehicle ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift + 190, Top2, MemuColor, G::Draw->Roboto, XorStringW(L"    載具透視    F6      [%s]"), G::IsShowVehicle ? XorStringW(L"開") : XorStringW(L"關"));
Top2 += 18;

G::IsShowAir ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift + 190, Top2, MemuColor, G::Draw->Roboto, XorStringW(L"    空投透視    F7      [%s]"), G::IsShowAir ? XorStringW(L"開") : XorStringW(L"關"));
Top2 += 18;

G::IsShowDeath ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift + 190, Top2, MemuColor, G::Draw->Roboto, XorStringW(L"    死亡箱子    F8      [%s]"), G::IsShowDeath ? XorStringW(L"開") : XorStringW(L"關"));
Top2 += 18;
}
if (G::IsAimMuen)
{
G::IsAimBot ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift + 355, Top3, MemuColor, G::Draw->Roboto, XorStringW(L"         自動瞄準    F9        [%s] "), G::IsAimBot ? XorStringW(L"開") : XorStringW(L"關"));
Top3 += 18;

G::BulletTrack ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift + 355, Top3, MemuColor, G::Draw->Roboto, XorStringW(L"         魔術子彈    F10      [%s]"), G::BulletTrack ? XorStringW(L"開") : XorStringW(L"關"));
Top3 += 18;

G::IsSoecPos ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift + 355, Top3, MemuColor, G::Draw->Roboto, XorStringW(L"         极限壓槍    F11      [%s]"), G::IsSoecPos ? XorStringW(L"開") : XorStringW(L"關"));
Top3 += 18;

G::PlayerWeapon ? MemuColor = onColor : MemuColor = offColor;
G::Draw->Text(Lift + 355, Top3, MemuColor, G::Draw->Roboto, XorStringW(L"         武器顯示    F12      [%s]"), G::PlayerWeapon ? XorStringW(L"開") : XorStringW(L"關"));
Top3 += 18;
}
}
}

ULONG64 __stdcall callback(Hook* hook, PRegisterContext pRegisterContext)
{
vector<Hook*>* hooks = HookEngine::GetInstance()->GetHooks();

ULONG calc = pRegisterContext->rsi - 1 ? (pRegisterContext->rsi - 1) * 4 : 0;
ULONG64 crcAddr = pRegisterContext->r14 + calc;
if (hooks)
{
for (int i = 0; i < hooks->size(); i++)
{
Hook* mhook = hooks->at(i);
ULONG64 startAddress = mhook->getCmpAddr();
ULONG64 endAddress = mhook->getCmpEndAddr();
char* code = mhook->getCmpCode();
if (crcAddr >= startAddress && crcAddr <= endAddress)
{
char* temp = code + (crcAddr - startAddress);
pRegisterContext->r15 &= ~0xffffffff;
pRegisterContext->r15 |= *(DWORD*)temp;
return 0;
}
}
}

if (!globalCrcUpdateHook) return 0;

for (int i = 0; i < globalCrcUpdateHook->size(); i++)
{
Hook* mhook = globalCrcUpdateHook->at(i);
ULONG64 startAddress = mhook->getCmpAddr();
ULONG64 endAddress = mhook->getCmpEndAddr();
char* code = mhook->getCmpCode();
if (crcAddr >= startAddress && crcAddr <= endAddress)
{
char* temp = code + (crcAddr - startAddress);
pRegisterContext->r15 &= ~0xffffffff;
pRegisterContext->r15 |= *(DWORD*)temp;
return 0;
}
}
return 0;
}

uint64_t hookProcessEvent(uint64_t uobject, uint64_t ufunction, void* uparams)
{
auto func_name = GetNames(G::gnames, dectypt_id(RPM<int>(ufunction + OFFSET_ID)));
if (func_name == "ReceiveDrawHUD")
{
AHUD_ReceiveDrawHUD_Params* Params = (AHUD_ReceiveDrawHUD_Params*)uparams;
G::ScreenCenterX = (float)Params->SizeX / 2.0f;
G::ScreenCenterY = (float)Params->SizeY / 2.0f;
uint64_t AHUD = uobject;
G::Draw->AHUDuobject = AHUD;
if (UCanvas_offset == 0)
{
for (size_t i = 0x350; i < 0x600; i++)
{
uint64_t ucn = RPM<uint64_t>(AHUD + i);
int id = dectypt_id(RPM<int>(ucn + OFFSET_ID));
string ucn_name = GetNames(G::gnames, id);
if (ucn_name == XorString("CanvasObject"))
{
UCanvas_offset = i;
break;
}
}
// }
// if (UCanvas_offset)
// {
// G::Draw->UCanvas = RPM<uint64_t>(AHUD + UCanvas_offset);
// G::Draw->UCanvas2 = RPM<uint64_t>(AHUD + UCanvas_offset + 0x8);
// ShowMenu();
// ESP::RenderEsp();
// }
// }
// return G::Draw->fnProcessEvent(uobject, ufunction, uparams);
// }

// namespace ESP
// {
// void InitializationObjectInternalIndex()
// {
// BYTE jMP[] = { 0xEB };
// BYTE Ret[] = { 0xC3 };
// BYTE C3[] = { 0x33,0xC0,0xC3 };
// PCHAR ZwReadVirtualMemory = (PCHAR)GetProcAddress(GetModuleHandle(XorStringW(L"ntdll.dll")), XorString("ZwReadVirtualMemory"));
// G::NtReadMemory_Index = ZwReadVirtualMemory[4];
// ULONG64 pCreateDCW = (ULONG64)GetProcAddress(GetModuleHandle(XorStringW(L"Gdi32.dll")), XorString("CreateDCW"));
// WriteVirtual(pCreateDCW, (ULONG64)C3, sizeof(C3));
// G::Tslgame = (uint64_t)GetModuleHandle(L"TslGame.exe");
// g_decObj = *(PULONG64)(G::Tslgame + 0x4FDD728);
// g_decGname1 = *(PULONG64)(G::Tslgame + 0x4FDD728);
// g_decGname2 = *(PULONG64)(G::Tslgame + 0x4FDD728);
// g_decuworld = *(PULONG64)(G::Tslgame + 0x4FDD728);
// g_declevel = *(PULONG64)(G::Tslgame + 0x4FDD728);
// g_decactorlist = *(PULONG64)(G::Tslgame + 0x4FDD728);
// g_declocalplayer = *(PULONG64)(G::Tslgame + 0x4FDD728);
// g_decplayercontroller = *(PULONG64)(G::Tslgame + 0x4FDD728);
// g_decprop = *(PULONG64)(G::Tslgame + 0x4FDD728);
// g_decgameinst = *(PULONG64)(G::Tslgame + 0x4FDD728);
// G::gnames = decrypt_gnames(G::Tslgame + GGNAME);


// G::Draw->fnProcessEvent = (ProcessEvent_t)(G::Tslgame + OFFSET_PROCESSEVENT);
// G::Draw->fnK2_DrawLine = (K2_DrawLine_t)(G::Tslgame + OFFSET_DRAWLINE);
// G::Draw->fnK2_DrawText = (K2_DrawText_t)(G::Tslgame + OFFSET_DRAWTEXT);

// G::Draw->AHudDrawLine = (AHud_DrawLine)(G::Tslgame + OFFSET_AHUD_DRAWLINE);
// G::Draw->AHudDrawText = (AHud_DrawText)(G::Tslgame + OFFSET_AHUD_DRAWTEXT);
// G::Draw->AHudDrawRect = (AHud_DrawRect)(G::Tslgame + OFFSET_AHUD_DRAWRECT);
// globalCrcUpdateHook = new vector<CrcRecord*>();

// ULONG64 HookCrc = G::Tslgame + OFFSET_XECRC;//CRC
// Hook* hook = new Hook(HookCrc, callback, 13, HookCrc + 13, HookType::HOOK_E9);
// HookEngine::GetInstance()->AddHook(hook);


// //ULONG64 HookCallProcess = G::Tslgame + 0xA5BCC9;//回溯
// //CrcRecord* xxxHook = new CrcRecord(HookCallProcess, NULL, 8, HookCallProcess + 8);
// //xxxHook->CodeCopy();
//globalCrcUpdateHook->push_back(xxxHook);
//WriteVirtual(HookCallProcess, (ULONG64)jMP, sizeof(jMP));

//ULONG64 HookCallProcessA = G::Tslgame + 0x1B31CFD;//回溯
//CrcRecord* xxHook = new CrcRecord(HookCallProcessA, NULL, 8, HookCallProcessA + 8);
//xxHook->CodeCopy();
//globalCrcUpdateHook->push_back(xxHook);
//WriteVirtual(HookCallProcessA, (ULONG64)jMP, sizeof(jMP));

//ULONG64 HookCallProcessB = G::Tslgame + 0xB2A705;//回溯
//CrcRecord* xxxxHook = new CrcRecord(HookCallProcessB, NULL, 8, HookCallProcessB + 8);
//xxxxHook->CodeCopy();
//globalCrcUpdateHook->push_back(xxxxHook);
//WriteVirtual(HookCallProcessB, (ULONG64)jMP, sizeof(jMP));

ULONG64 HookPROCESSEVENT = (uint64_t)G::Tslgame + OFFSET_PROCESSEVENT;
CrcRecord* EVENTHook = new CrcRecord(HookPROCESSEVENT, NULL, 0x30, HookPROCESSEVENT + 0x30);
EVENTHook->CodeCopy();
globalCrcUpdateHook->push_back(EVENTHook);

ULONG64 HookVectorHook = (uint64_t)G::Tslgame + OFFSET_LineHookTo;
CrcRecord* g_VectorHook = new CrcRecord(HookVectorHook, NULL, 0x30, HookVectorHook + 0x30);
g_VectorHook->CodeCopy();
globalCrcUpdateHook->push_back(g_VectorHook);

ULONG64 HookAIMHOOK = (uint64_t)G::Tslgame + OFFSET_AIMHOOK;
CrcRecord* g_AIMHOOK = new CrcRecord(HookAIMHOOK, NULL, 8, HookAIMHOOK + 8);
g_AIMHOOK->CodeCopy();
globalCrcUpdateHook->push_back(g_AIMHOOK);

ULONG64 HookAIMCALL = (uint64_t)G::Tslgame + OFFSET_AimBotCall;
CrcRecord* g_AIMCALL = new CrcRecord(HookAIMCALL, NULL, 0x40, HookAIMCALL + 0x40);
g_AIMCALL->CodeCopy();
globalCrcUpdateHook->push_back(g_AIMCALL);
//////////////////////////


/*ULONG64 HookAIMZZ = (uint64_t)G::Tslgame + OFFSET_BulletTrack;
CrcRecord* g_HookAIMZZ = new CrcRecord(HookAIMZZ, NULL, 0x30, HookAIMZZ + 0x30);
g_HookAIMZZ->CodeCopy();
globalCrcUpdateHook->push_back(g_HookAIMZZ);

ULONG64 HookPass = (uint64_t)G::Tslgame + OFFSET_BulletTrackJe;
CrcRecord* g_HookPass = new CrcRecord(HookPass, NULL, 8, HookPass + 8);
g_HookPass->CodeCopy();
globalCrcUpdateHook->push_back(g_HookPass);*/



///////////////////////////////////
G::Draw->Roboto = FindFonts(G::gnames, XorString("Roboto"));
G::Draw->TSLFont = FindFonts(G::gnames, XorString("TSLFont"));

uint64_t GZhook = G::Tslgame + OFFSET_PROCESSEVENTCall;
CrcRecord* g_HookGZhook = new CrcRecord(GZhook, NULL, 32, GZhook + 32);
g_HookGZhook->CodeCopy();
globalCrcUpdateHook->push_back(g_HookGZhook);

BYTE modeProcessEvent[] = { 0x48,0x89,0x54,0x24,0x10,0x57,0x41,0x54,0x41,0x55,0x41,0x56,0x41,0x57,0xFF,0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

BYTE outProcessEvent[] = { 0xFF,0x25,0x00,0x00 ,0x00,0x00 ,0x00,0x00 ,0x00,0x00 ,0x00,0x00 ,0x00,0x00 };

*(uint64_t*)(modeProcessEvent + 20) = (uint64_t)G::Tslgame + OFFSET_PROCESSEVENT + 14;
*(uint64_t*)(outProcessEvent + 6) = (uint64_t)hookProcessEvent;
WriteVirtual(GZhook, (ULONG64)modeProcessEvent, sizeof(modeProcessEvent));
G::Draw->fnProcessEvent = (ProcessEvent_t)(GZhook);
WriteVirtual((G::Tslgame + OFFSET_PROCESSEVENT), (ULONG64)outProcessEvent, sizeof(outProcessEvent));
AimHook();
LineTaceToHook();
ZZHook();

if (!G::gnames)
return;

for (uint32_t InternalIndex = 0; InternalIndex < 400000; InternalIndex++)
{
string Name = GetNames(G::gnames, InternalIndex);
if (Name.c_str() == "")
continue;

ULONG Hash = RtlHashString_ImulMagicA((PCHAR)Name.c_str(), TRUE);

if (!Hash)
continue;

if (Hash == 0x4A1CD1B0 || Hash == 0x3DCE1154 || Hash == 0x960B9C2F || Hash == 0x29818C53)
{
G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
G::ObjectType[G::ObjectCount] = Player;
G::ObjectCount++;
}
else if (Hash == 0x91B5B533)
{
G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
G::ObjectType[G::ObjectCount] = DropItem;
G::ObjectCount++;
}
else if (Hash == 0xA1A690EA || Hash == 0xA96A69F8 || Hash == 0xC344059C || Hash == 0xA96A69F9 || Hash == 0xC3C2151D
|| Hash == 0xA96A69FA || Hash == 0xC440249E || Hash == 0xC4BE341F || Hash == 0xC53C43A0 || Hash == 0xC5BA5321)
{
G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
G::ObjectType[G::ObjectCount] = Buggy;
G::ObjectCount++;
}
else if (Hash == 0x6B031ED2 || Hash == 0x1034CA10 || Hash == 0xB6AFD9B4 || Hash == 0x3EBB9ACF
|| Hash == 0xCCDC3AF3 || Hash == 0x6D426B8E || Hash == 0xE3089C32)
{
G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
G::ObjectType[G::ObjectCount] = Uaz;
// G::ObjectCount++;
// }
// else if (Hash == 0xD40F8662 || Hash == 0x99FB0E80 || Hash == 0x70BAE624 || Hash == 0x99FB0E81 || Hash == 0x7138F5A5 || Hash == 0x6F796C3D
// || Hash == 0x71B70526 || Hash == 0x99FB0E83 || Hash == 0x723514A7 || Hash == 0x4320A9BF || Hash == 0x594D0AFE || Hash == 0xA455AF9B
// || Hash == 0x85A5CD7C || Hash == 0xD2DC805A || Hash == 0x1635119 || Hash == 0x2FEA21D8)
// {
// G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
// G::ObjectType[G::ObjectCount] = Dacia;
// G::ObjectCount++;
// }
// else if (Hash == 0x6A477E1C || Hash == 0xD09147C0 || Hash == 0xBF67655A || Hash == 0x64B56FFE || Hash == 0x6A477E1D || Hash == 0xD10F5741
// || Hash == 0xD20CBF9B || Hash == 0xE64FB9BF || Hash == 0x73861A9D || Hash == 0x2BC7B3C1 || Hash == 0x6BE59339 || Hash == 0x73861A9D
// || Hash == 0x73861A9E || Hash == 0x2C45C342 || Hash == 0xDF4A29FC || Hash == 0x873C03A0 || Hash == 0x172958BA || Hash == 0x71D102BD
// || Hash == 0x8AAAEC16 || Hash == 0x57A25CDC || Hash == 0x5FD06138)
// {
// G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
// G::ObjectType[G::ObjectCount] = Motobike;
// G::ObjectCount++;
// }
// else if (Hash == 0x5817A24 || Hash == 0x51B1A945 || Hash == 0x107336F4 || Hash == 0x9BA2C750 || Hash == 0x45F3192)
// {
// G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
// G::ObjectType[G::ObjectCount] = boat;
// G::ObjectCount++;
// }
// else if (Hash == 0x989D6D70 || Hash == 0x991B7CF1 || Hash == 0x99998C72 || Hash == 0x9A179BF3 || Hash == 0x9A95AB74
// || Hash == 0xAEC9CEAF || Hash == 0xAF47DE30 || Hash == 0xAFC5EDB1 || Hash == 0xB043FD32 || Hash == 0xB0C20CB3
// || Hash == 0x1DD77BCC || Hash == 0x1DD77BCD || Hash == 0x1DD77BCE || Hash == 0x1DD77BCF || Hash == 0x1DD77BD0
// || Hash == 0x4C5E4C8B || Hash == 0x4C5E4C8C || Hash == 0x4C5E4C8D || Hash == 0x4C5E4C8E || Hash == 0x4C5E4C8F
// || Hash == 0xAB371C57 || Hash == 0x37D1EE33 || Hash == 0xB51F2172)
// {
// G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
// G::ObjectType[G::ObjectCount] = PikupTruck;
// G::ObjectCount++;
// }
// else if (Hash == 0xA99BDFD0 || Hash == 0xAA19EF51 || Hash == 0xAA97FED2 || Hash == 0xDE411E2C || Hash == 0xDE411E2D || Hash == 0xDE411E2E)
// {
// G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
// G::ObjectType[G::ObjectCount] = Van;
// G::ObjectCount++;
// }
// else if (Hash == 0x92E8B60C)
// {
// G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
// G::ObjectType[G::ObjectCount] = Minibus;
G::ObjectCount++;
}
else if (Hash == 0xAB457BE4)
{
G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
G::ObjectType[G::ObjectCount] = AirPack;
G::ObjectCount++;
}
else if (Hash == 0x36D36494)
{
G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
G::ObjectType[G::ObjectCount] = DeadBox;
G::ObjectCount++;
}
else if (Hash == 0x1D90F0C)
{
G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
G::ObjectType[G::ObjectCount] = ItemObject;
G::ObjectCount++;
}
else if (Hash == 0x57F95192 || Hash == 0x2D4FD0EE)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = M16A4;
G::ItemType2[G::ItemCounts] = weapon_bq;
G::ItemCounts++;
}
else if (Hash == 0xFA5ADE83 || Hash == 0x9257065F)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = M416;
G::ItemType2[G::ItemCounts] = weapon_bq;
G::ItemCounts++;
}
else if (Hash == 0x4B5E5E77 || Hash == 0x107AA9B)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = scar;
G::ItemType2[G::ItemCounts] = weapon_bq;
G::ItemCounts++;
}
else if (Hash == 0xB0E54D4D || Hash == 0xD5882A64 || Hash == 0x9F588E71 || Hash == 0x71B05008)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = ak47;
G::ItemType2[G::ItemCounts] = weapon_bq;
G::ItemCounts++;
}
else if (Hash == 0x824B1954 || Hash == 0x860AC6F8)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = groza;
G::ItemType2[G::ItemCounts] = weapon_bq;
G::ItemCounts++;
}
else if (Hash == 0x65A755CE || Hash == 0x431C6672)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = qbz95;
// G::ItemType2[G::ItemCounts] = weapon_bq;
// G::ItemCounts++;
// }
// else if (Hash == 0xE0E19B50 || Hash == 0xFB880AF4)
// {sfdgiatfkg
// G::ItemIntefjsgafwgiczxrnalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCouncts] = g36c;
// G::ItemType2[G::ItemCounsfalgfluahLZxts] = weapon_cf;
// G::ItemCounts++;f
// }sfasegfw
// elsfwae if (fcvHash == 0x3FA954C3 || Hash == 0xB8A43AE7)
// {sdetg
// G::ItesmInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemgType[G::ItemCounts] = pp19;
// G::ItemTerype2[G::ItemCounts] = weapon_cf;
// G::ItemCouywfnts++;
// }sze6tqy34
// else if (Hwtash == 0x6C606CD3 || Hash == 0xD3304AF7)
// {g
// G:s:ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::seteygshItemType[G::ItemCounts] = mk47;
// G::ItemTyperstus2[G::ItemCounts] = weapon_bq;
// G::ItemCounts++;eh
// }sg
// elsdhxdgze if (Hash == 0xD6B92B5 || Hash == 0xC00F3391)
// {dzgyaw
G::ItemwInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = m762;
G::ItemType2[G::ItemCounts] = weapon_bq;
G::ItemCounts++;
}
else if (Hash == 0x9F1FDDB2 || Hash == 0x2B073C56)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = slr;
G::ItemType2[G::ItemCounts] = weapon_jj;
G::ItemCounts++;
}
else if (Hash == 0x884691C4 || Hash == 0x8CF10768)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = sks;
G::ItemType2[G::ItemCounts] = weapon_jj;
G::ItemCounts++;
// }
// else if (Hash == 0xCCECAA63 || Hash == 0x89C8C23F)
// {sdgisvbkzjbkjzdbjgzu
// G::ItemInternalIndex[fsasgzdfssdfasgG::fhsdhzIhtdgehdmhsdChojsujnfhtgsshf]ssn f= InternalIndex;
// G::ItemType[G::ItemCounts] = vss;
// G::ItemType2[G::ItemCounts] = weapon_jj;
// G::ItemCounts++;
// }
// else if (Hash == 0x6C421E5C || Hash == 0x1398E2B8)
// {
dg/sg/gg G::ItemInternalInsgdex[G::ItemCounts] = InternalIndex;
// G::ItemType[sdfgG::ItemCounts] = mk14;
// G::ItemTysgpe2[G::ItemCounts] = weapon_jj;
// G::ItesgmCounts++;
// }sgsg
dgsdf/sgs/ else fgdigf (Hash == 0xC271E931 || Hash == 0x6330080D)
// {sdgd
// G::ItemInternalIndexggsd[fgG::ItemCounts] = InternalIndex;
// G::ItemType[G::ItdefmCounts] = qbu;
// G::ItemType2[Gdgf::ItemCounts] = weapon_jj;
// G::ItemCgsodgunts++;
// }ag
as/ga/gag gelsgeag agif (Hash == 0xA7505755 || Hash == 0x14744831)
/s/fa {
f// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = mini14;
// G::ItemType2[G::ItemCounts] = weapon_jj;
// G::ItemCounts++;
}
else if (Hash == 0xACFA3E8B || Hash == 0x6B37EA67)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = q98k;
G::ItemType2[G::ItemCounts] = weapon_jj;
G::ItemCounts++;
}
else if (Hash == 0xF1AFC544 || Hash == 0x7F757DA0)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = awm;
G::ItemType2[G::ItemCounts] = weapon_jj;
G::ItemCounts++;
}
else if (Hash == 0x85392E78 || Hash == 0x5AF88A1C)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = m24;
G::ItemType2[G::ItemCounts] = weapon_jj;
G::ItemCounts++;
}
else if (Hash == 0x705D3865 || Hash == 0x8944B141)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = ump9;
G::ItemType2[G::ItemCounts] = weapon_cf;
G::ItemCounts++;
}
// else if (Hash == 0xD22FF93A || Hash == 0x64B213DE)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = vectors;
// G::ItemType2[G::ItemCounts] = weapon_cf;
// G::ItemCounts++;
// }
// else if (Hash == 0x91ADC6C0 || Hash == 0x7F737D1C)
// {faesfcdzdvas
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemedgsetCounts] = aug;
// G::ItemType2[G::ItemCounts] = weapon_bq;
// G::ItemCounts++;sfcs
// }
// else if (Hash == 0xFEC2562B || Hash == 0x2C83084F)
// {
// G::ItemInternalIndxdcfvsex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::syesgszvxd] = tom;
// G::ItemType2[G::ItemxgstfdsCounts] = weapon_cf;
// G::ItemCounts++;t
// }daersg
// else if (Hash == 0xC9C36591 || Hash == 0x8951B46D)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = uzi;
// G::ItemType2[G::ItemCoetfasdvunts] = weapon_cf;
// G::ItemCounts++;
// }
// else if (Hash == 0xAfsefB43BCCD || Hash == 0x6390E9A9)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = dp28;
// G::ItemType2[G::ItemCounts] = weapon_bq;
// G::ItemCounts++;
// }
// else if (Hash == 0xF78A6FC1 || Hash == 0xDAABB6E5)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = m249;
G::ItemType2[G::ItemCounts] = weapon_bq;
G::ItemCounts++;
}
else if (Hash == 0x88510922)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = bqkk;
G::ItemType2[G::ItemCounts] = peijian;
G::ItemCounts++;
}
else if (Hash == 0x27B0732F)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = bqkr;
G::ItemType2[G::ItemCounts] = peijian;
G::ItemCounts++;
}
else if (Hash == 0x77E53DA0)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = jjkk;
G::ItemType2[G::ItemCounts] = peijian;
G::ItemCounts++;
}
else if (Hash == 0x98E62F0D)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = jjkr;
G::ItemType2[G::ItemCounts] = peijian;
G::ItemCounts++;
}
else if (Hash == 0x93539F79)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = mzwb;
G::ItemType2[G::ItemCounts] = peijian;
G::ItemCounts++;
}
else if (Hash == 0xD10594A8)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = bqbc;
G::ItemType2[G::ItemCounts] = peijian;
G::ItemCounts++;
}
else if (Hash == 0x7FF9DE96)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = zjwb;
G::ItemType2[G::ItemCounts] = peijian;
// G::ItemCounts++;
// }
// else if (Hash == 0x98E62F0D)
// {
// G::ItemInternalIndex[Gfafsdf::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = qxwb;
// G::ItemType2[G::ItfdfdsfdsaafdsemCounts] = peijian;
// G::ItemCounts++;
// }
// else if (Hash == 0x96DBE61C)
// {
// G::ItemInternalInfasffdex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItedfsfsddsfasfdmCounts] = bjwb;
// G::ItemType2[G::ItemCounts] = peijian;
// G::ItemCounts++;dfsfdsfds
// }
// else if (Hash == 0x81622985)
// {faffa
// G::ItemInternalInsafddex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = czwb;
// G::ItemType2[G::IfdsfsdfdsfdstemCounts] = peijian;
// G::ItemCounts++;
// }
// else if (Hash == fdsafdsfds0xD10594A8)
// {
// G::ItemInternalIndex[G::ItemCountsf] = InternalIndex;
// G::ItemType[G::ItemCounts] = jjxy;
G::ItemType2[G::ItemCounts] = peijian;
G::ItemCounts++;
}
// else if (Hash == 0xDC922026)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = jjbc;
// G::ItemType2[G::ItemCounts] = peijian;
// G::ItemCounts++;
// }
// else if (Hash == 0x42B47C41)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = bqxy;
// G::ItemType2[G::ItemCounts] = peijian;
// G::ItemCounts++;
// }
// else if (Hash == 0x3F96AAD)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = zdd;
// G::ItemType2[G::ItemCounts] = peijian;
// G::ItemCounts++;
// }
// else if (Hash == 0x1F886A35)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = tsb;
// G::ItemType2[G::ItemCounts] = peijian;
// G::ItemCounts++;
// }
// else if (Hash == 0xBC82EB3B)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = zsqt;
// G::ItemType2[G::ItemCounts] = peijian;
// G::ItemCounts++;
// }
// else if (Hash == 0xFE285289)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = jjmz;
// G::ItemType2[G::ItemCounts] = peijian;
// G::ItemCounts++;
// }
else if (Hash == 0xF38D2DDB)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = jjb;
G::ItemType2[G::ItemCounts] = medical;
G::ItemCounts++;
}
else if (Hash == 0x467D9639)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = ylx;
G::ItemType2[G::ItemCounts] = medical;
G::ItemCounts++;
}
else if (Hash == 0x425C2C6D)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = zty;
G::ItemType2[G::ItemCounts] = medical;
G::ItemCounts++;
}
else if (Hash == 0x3E7CD80C)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = nlyl;
G::ItemType2[G::ItemCounts] = medical;
G::ItemCounts++;
}
else if (Hash == 0x49CFFFEE)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = sss;
G::ItemType2[G::ItemCounts] = medical;
G::ItemCounts++;
}
else if (Hash == 0xD7D47A18)
{
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = d9mm;
// G::ItemType2[G::ItemCounts] = ammo;
// G::ItemCounts++;
// }
// else if (Hash == 0xD61D5492)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = d762;
// G::ItemType2[G::ItemCounts] = ammo;
// G::ItemCounts++;
// }
// else if (Hash == 0x234C9255)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = d556;
// G::ItemType2[G::ItemCounts] = ammo;
// G::ItemCounts++;
// }
// else if (Hash == 0xA3FEF525)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = d300;
// G::ItemType2[G::ItemCounts] = ammo;
// G::ItemCounts++;
// }
// else if (Hash == 0x14ACCAFE)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = hd;
// G::ItemType2[G::ItemCounts] = scope;
// G::ItemCounts++;
// }
// else if (Hash == 0xABEF3405)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = qx;
G::ItemType2[G::ItemCounts] = scope;
G::ItemCounts++;
}
else if (Hash == 0x7F527D41)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = b2;
G::ItemType2[G::ItemCounts] = scope;
G::ItemCounts++;
}
else if (Hash == 0xB52F498B)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = b3;
G::ItemType2[G::ItemCounts] = scope;
G::ItemCounts++;
}
else if (Hash == 0xE29B5958)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = b4;
G::ItemType2[G::ItemCounts] = scope;
G::ItemCounts++;
}
else if (Hash == 0x40C3BBC8)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = b6;
G::ItemType2[G::ItemCounts] = scope;
G::ItemCounts++;
}
else if (Hash == 0x95B151A6)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = b8;
G::ItemType2[G::ItemCounts] = scope;
G::ItemCounts++;
}
else if (Hash == 0x70D87881)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = b15;
G::ItemType2[G::ItemCounts] = scope;
G::ItemCounts++;
}

else if (Hash == 0xADEE2DF3 || Hash == 0x9C570DCF || Hash == 0xE0436CD0 || Hash == 0x84191C74)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = bb2;
G::ItemType2[G::ItemCounts] = hujia;
G::ItemCounts++;
}
else if (Hash == 0x9A67F6B7 || Hash == 0xB321F893 || Hash == 0xF70E5794 || Hash == 0x7092E538)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = bb3;
G::ItemType2[G::ItemCounts] = hujia;
G::ItemCounts++;
}
else if (Hash == 0x67CB88BA || Hash == 0xF5651C16 || Hash == 0x39517B17 || Hash == 0x3DF6773B)
{
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = tk2;
// G::ItemType2[G::ItemCounts] = hujia;
// G::ItemCounts++;
// }
// else if (Hash == 0x19A05A7A || Hash == 0x9876CDD6)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = tk3;
// G::ItemType2[G::ItemCounts] = hujia;
// G::ItemCounts++;
// }
// else if (Hash == 0x29595435 || Hash == 0xC225B511)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = yf2;
// G::ItemType2[G::ItemCounts] = hujia;
// G::ItemCounts++;
// }
// else if (Hash == 0x7880A177 || Hash == 0x1F140353)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = yf3;
// G::ItemType2[G::ItemCounts] = hujia;
// G::ItemCounts++;
// }
else if (Hash == 0xA61F123F)
{
G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
G::ItemType[G::ItemCounts] = jjxy2;
G::ItemType2[G::ItemCounts] = peijian;
G::ItemCounts++;
}
// else if (Hash == 0xF6596D35)
// {
// G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
// G::ObjectType[G::ObjectCount] = Grenade;
// G::ObjectCount++;
// }
// else if (Hash == 0x3CCBF9D)
// {
// G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
// G::ObjectType[G::ObjectCount] = Molotov;
// G::ObjectCount++;
// }
// else if (Hash == 0xAD24257B)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = sl1;
// G::ItemType2[G::ItemCounts] = weapon_bq;
// G::ItemCounts++;
// }
// else if (Hash == 0xD06E486C || Hash == 0xD0EC57ED || Hash == 0xD16A676E || Hash == 0xD1E876EF)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = glf;
// G::ItemType2[G::ItemCounts] = hujia;
// G::ItemCounts++;
// }
// else if (Hash == 0x80AAB38D)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = xhq;
// G::ItemType2[G::ItemCounts] = weapon_bq;
// G::ItemCounts++;
// }
// else if (Hash == 0x6D14DA4D)
// {
// G::ItemInternalIndex[G::ItemCounts] = InternalIndex;
// G::ItemType[G::ItemCounts] = xhd;
// G::ItemType2[G::ItemCounts] = ammo;
// G::ItemCounts++;
// }
// else if (Hash == 0x8159774E || Hash == 0x81D786CF || Hash == 0x82559650)
// {
// G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
// G::ObjectType[G::ObjectCount] = Snowmobile;
// G::ObjectCount++;
// }
// else if (Hash == 0x56701586 || Hash == 0x9A5C7487 || Hash == 0xDE48D388 || Hash == 0x22353289)
// {
// G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
// G::ObjectType[G::ObjectCount] = Scooter;
// G::ObjectCount++;
// }
// else if (Hash == 0x546DDBFC || Hash == 0x3CF5EE64 || Hash == 0x3D73FDE5)
// {
// G::ObjectInternalIndex[G::ObjectCount] = InternalIndex;
G::ObjectType[G::ObjectCount] = Mirado;
G::ObjectCount++;
}
}
}

wchar_t* char20wchar(const char* cchar)
{
wchar_t* m_wchar;
int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
m_wchar = new wchar_t[len + 1];
MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);
m_wchar[len] = '\0';
return m_wchar;
}

void RenderEsp()
{
Key();
uint32_t disTance = 0;
Vector3  aim_pos;
uint32_t FWRS = 0, ZJJL = 0;

uint64_t uworld = decrypt_uworld(G::Tslgame + UWORLD);
uint64_t gameinst = decrypt_gameinst(uworld + OFFSET_GAMEINST);
uint64_t localplayers = decrypt_localplayer(RPM<uint64_t>(gameinst + OFFSET_LOCALPLAYER));
uint64_t playercontroller = decrypt_playercontroller(localplayers + OFFSET_PLAYERCONTROLLER);
uint64_t levels = decrypt_level(uworld + OFFSET_LEVEL);
uint64_t entity = decrypt_actorlist(levels + OFFSET_ACTOR);
uint64_t entity_list = RPM<uint64_t>(entity);
uint32_t entity_count = RPM<uint32_t>(entity + 0x8);

G::BoneArry.clear();
if (entity_count <= 0x60 || entity_count >= 20000)
return;

// uint64_t CameraManager = RPM<uint64_t>(playercontroller + OFFSET_CAMERA_MANAGER);

CameraLocationA = RPM<FVector>(CameraManager + OFFSET_LOCATION);
uint64_t localactor = decrypt_prop(playercontroller + OFFSET_LOCALACTOR);
uint64_t Mrootcomp = decrypt_prop(localactor + OFFSET_ROOTCOMP);
Vector3 Mpostion = RPM<Vector3>(Mrootcomp + OFFSET_RELATIVEPOS);
uint32_t myteam = RPM<uint32_t>(localactor + OFFSET_TEAMNUMBER);
Vector3 localpostion = RPM<Vector3>(CameraManager + OFFSET_LOCATION);
DWORD Obsver = RPM<DWORD>(localactor + OFFSET_Audience);
uint64_t mMesh = RPM<uint64_t>(localactor + OFFSET_MESH);
if (Obsver > 0 && Obsver < 12)
G::Draw->Text(20, 30, FLinearColor(1, 1, 1, 1), G::Draw->TSLFont, XorStringW(L"观战人数:%d"), Obsver);
for (uint32_t i = 0; i < entity_count; ++i)
// {
// bool insertpos = false;
// uint64_t pEntity = RPM<uint64_t>(entity_list + i * 0x8);
// if (!pEntity)
// continue;
//代码-WenChris所有
// uint32_t iid = fa s fdectypt_id(RPM<uint32_t>(pEntity + OFFSET_ID));
fsdfafa
// uint32_t type = FilterI//代码-WenChris所有//代码-WenChris所有D(iid);//代码-WenChris所有//代码-WenChris所有//代码-WenChris所有
// if (!type)
// continue;

// uint64_t Mesh = RPMfafasf<uint64_t>(pEntity + OFFSET_MESH);
// uint64_t rootcomp = decrypt_prop(pEntity + OFFSET_ROOTCOMP);
// Vector3 postion = RPM<Vector3>(rootcomp + OFFSET_RELATIVEPOS);

// Vector3 screen = WorldToScreen(postion, CameraManager);
// uint32_t Distance = (uint32_t)(postion - Mpostion).Length() / 100;
// uint32_t playerteam = RPM<uint32_t>(pEntity + OFFSET_TEAMNUMBER);

if(Distance <= 1)
continue;

if (type == AirPack && G::IsShowAir)
{
// 空头
if (Distance <= 1000)
{
G::Draw->jzText(screen.x, screen.y, FLinearColor(1, 1, 0, 1), G::Draw->Roboto, XorStringW(L"空投箱[%d]"), Distance);
uint64_t Items = RPM<uint64_t>(pEntity + OFFSET_PACKUITEM);
uint32_t count = RPM<uint32_t>(pEntity + OFFSET_PACKUITEM + 0x8);
DWORD jjj = 0;
for (size_t i = 0; i < count; i++)
{
uint64_t WPItems = RPM<uint64_t>(Items + (i - 1) * 8);

uint32_t id = dectypt_id(RPM<uint32_t>(WPItems + OFFSET_ID));
if (id > 0)
{
if (GetNames(G::gnames, id) != "")
{
if (FilterDeathItemT(id, screen.x, screen.y + 15 * jjj + 15, Distance))
jjj++;
}
}
}
}
}
else if (type == DeadBox && G::IsShowDeath)
{
if (Distance <= 120)
{
G::Draw->jzText(screen.x, screen.y, FLinearColor(1, 1, 0, 1), G::Draw->Roboto, XorStringW(L"战利品[%d]"), Distance);
uint64_t Items = RPM<uint64_t>(pEntity + OFFSET_PACKUITEM);
DWORD count = RPM<DWORD>(pEntity + OFFSET_PACKUITEM + 0x8);
DWORD jjj = 0;
for (size_t i = 0; i < count; i++)
{
uint64_t WPItems = RPM<uint64_t>(Items + (i - 1) * 8);
uint32_t id = dectypt_id(RPM<uint32_t>(WPItems + OFFSET_ID));
if (id > 0)
{
if (GetNames(G::gnames, id) != "")
{
if (FilterDeathItemT(id, screen.x, screen.y + 15 * jjj + 15, Distance))
jjj++;
}
}
// }
// }
// }
// else if (type == DropItem && G::IsShowItem)
// {
// uint64_t item = decrypt_prop(pEntity + OFFSET_DROPITEM);//掉落物品
// uint32_t id = dectypt_id(RPM<uint32_t>(item + OFFSET_ID));
// if (id > 0)
// {
// FilterDeathItem(id, screen.x, screen.y, Distance);
// }
// }
// else if (type == ItemObject && G::IsShowItem)
// {
// /
// if (Distance <= 100) {
// uint64_t Item = RPM<uint64_t>(pEntity + OFFSET_DROPGROUP);
// uint32_t ItemCount = RPM<uint32_t>(pEntity + OFFSET_DROPGROUP + 0x8);
// if (!ItemCount)
// continue;
// for (uint32_t j = 0; j < ItemCount; j++)
// {
// uint64_t pItem = RPM<uint64_t>(Item + j * 0x10);
// if (!pItem)
// continue;
// Vector3 Itempostion = RPM<Vector3>(pItem + OFFSET_RELATIVEPOS);
// uint32_t ItemDistance = (uint32_t)((Itempostion - localpostion).Length() / 100.0f);
// if (ItemDistance <= G::ItemDistance)
// {
// uint64_t pUitem = RPM<uint64_t>(pItem + OFFSET_DROPUITEM);
// if (!pUitem)
// continue;
// uint32_t ItemID = dectypt_id(RPM<int>(pUitem + OFFSET_ID));
// if (ItemID <= 0 || ItemID >= 0x100000)
// continue;
// Vector3 ItemScreen = WorldToScreen(Itempostion, CameraManager);
// FilterDeathItem(ItemID, ItemScreen.x, ItemScreen.y, ItemDistance);
// }
// }
// }
// }
// else if (type != Player && G::IsShowVehicle)
// {
// //載
// if (Distance <= G::VehicleDistance)
// {dfg
// const wgfsdcshar_t* VehicleName = NULL;
// BOOL IdgsVeghicle = false;
// switdgch (tysgpe)
// {gfsg
// case Bsuggy:
// VehisgcleName = XorStringW(L"");
// gafdIsVehicle = TRUE;
/break;z
vcase Uaz:
VehicleName = XorStringW(L"");
IsVehicle = TRUE;
break;
case Dacia:
VehicleName = XorStringW(L"");
IsVehicle = TRUE;
break;
case Motobike:
VehicleName = XorStringW(L"");
IsVehicle = TRUE;
break;
case boat:
VehicleName = XorStringW(L"");
IsVehicle = TRUE;
break;
case PikupTruck:
VehicleName = XorStringW(L"");
IsVehicle = TRUE;
break;
case Van:
VehicleName = XorStringW(L"");
IsVehicle = TRUE;
break;
// case Minibus:
// VehicleName = XorStringW(L"");
// IsVehicle = TRUE;
// break;
// case Snowmobile:
// VehicleName = XorStringW(L"");
// IsVehicle = TRUE;
// break;
// case Scooter:
// VehicleName = XorStringW(L"");
// IsVehicle = TRUE;
// break;
// case Mirado:
// VehicleName = XorStringW(L"");
// IsVehicle = TRUE;
// break;
// }
// if (IsVehicle == TRUE)
// G::Draw->jzText(screen.x, screen.y, FLinearColor(1, 0.8f, 0.2f, 1), G::Draw->Roboto, XorStringW(L"%ws[%dM]"), VehicleName, Distance);
// }
// }
// else if (type == Player)
// {
// //玩家
// if (Distance <= G::PlayerDistance)
// {
// float health = RPM<float>(pEntity + OFFSET_HEALTH);
// float dhealth = RPM<float>(pEntity + OFFSET_DEADHEALTH);
// float Hp = 0.0f;
// FLinearColor HpColor = { 0, 1, 0, 1 };
// if (health <= 0.f && dhealth <= 0.f)
// {
// continue;
// }

// if (health > 0.0f || dhealth > 0.0f)
// {
// uint64_t Mesh = RPM<uint64_t>(pEntity + OFFSET_MESH);
// Vector3 DrawP = WorldToScreen(GetBoneWithRotation(Mesh, Bones::pelvis), CameraManager);
// if (G::Draw->InDraw(DrawP))
// {
// Vector3 Aimpoint = WorldToScreen(GetBoneWithRotation(Mesh, 4), CameraManager);

// if ((G::KillTeam ? myteam == playerteam : myteam != playerteam) && pEntity != localactor)
// {
// float dotDistance = GetDotDistance(G::ScreenCenterX, G::ScreenCenterY, Aimpoint.x, Aimpoint.y);
// if ((Dot > dotDistance || Dot == 0.0f) && dotDistance < 200.0f && !G::IsShit)
// {
// disTance = Distance;
// Dot = dotDistance;
// if (aim_entity)
// G::BoneArry.clear();
// aim_entity = pEntity;
// insertpos = true;
// }

Vector3 head = WorldToScreen(GetBoneWithRotation(Mesh, Bones::forehead), CameraManager);

Vector3 headV3 = GetBoneWithRotation(Mesh, Bones::forehead);
headV3.z -= 175;

Vector3 rect2D = WorldToScreen(headV3, CameraManager);

float h = rect2D.y - head.y;
float w = h * 0.6f;
float xx = head.x - (rect2D.y - head.y) / 4.f;
float yx = head.y;
float ww = (rect2D.y - head.y) / 2.f;
float hh = rect2D.y - head.y;
float xxxx = xx - (90 - w) / 2.f;
float yyyy = yx - hh / 4;

if (aim_entity == pEntity && G::IsShit) {
disTance = Distance;
if (aim_entity)
G::BoneArry.clear();
insertpos = true;

//G::Draw->jzText(head.x, head.y - 16, FLinearColor(1, 0.2f, 0, 1), G::Draw->Roboto, XorStringW(L"×"));
}

if (health > 0.0f) {
Hp = health;
}
else if (dhealth > 0.0f) {
HpColor = { 1, 0, 1, 1 };
Hp = dhealth;
}

int Killshu = RPM<uint32_t>(decrypt_prop(pEntity + OFFSET_PLAYSTATE) + OFFSET_KILLCOUNT), ShaDi = 0;
Killshu >= 0 && Killshu < 20 ? ShaDi = Killshu : ShaDi = 0;
if (G::IsShowPlayer)

{
/*G::Draw->Box(DrawP.x - h / 3 - 4, DrawP.y - h / 2 + 1, 4, h, FLinearColor(0, 0, 0, 1), 1);
G::Draw->AHudDrawRect(G::Draw->AHUDuobject, HpColor, DrawP.x - h / 3 - 3, DrawP.y - h / 2 + 2, 2, (h - 1)* Hp / 100);
G::Draw->jzText(DrawP.x, DrawP.y + 6, FLinearColor(1, 1, 1, 1), G::Draw->Roboto, (XorStringW(L"[%d Kill][ID:%d]-%dM")), ShaDi, playerteam, Distance);
G::Draw->jzText(DrawP.x, DrawP.y + 11 + 6, FLinearColor(1, 1, 1, 1), G::Draw->Roboto, (XorStringW(L"%ws")), (wchar_t*)(*(uint64_t*)(pEntity + OFFSET_PLAYERNAME)));
DrawBone(localactor, pEntity, playercontroller, CameraManager, insertpos);*/

//G::Draw->Box(xxxx + 1, yyyy + 2, 90, 4, FLinearColor(0, 0, 0, 1), 1);
//G::Draw->AHudDrawRect(G::Draw->AHUDuobject, HpColor, xxxx + 1, yyyy + 2, 90 * Hp / 100, 4);
//G::Draw->jzText(xxxx + 40, yyyy - 14, FLinearColor(1, 1, 1, 1), G::Draw->Roboto, (XorStringW(L"%d K |%d|%dM")), ShaDi, playerteam, Distance);//
//DrawBone(localactor, pEntity, playercontroller, CameraManager, insertpos);
G::Draw->Box(xxxx + 1, yyyy - 6, 90, 4, FLinearColor(0, 0, 0, 1), 1);//血条
G::Draw->AHudDrawRect(G::Draw->AHUDuobject, HpColor, xxxx + 1, yyyy - 6, 90 * Hp / 100, 4);//血条
//G::Draw->jzText(xxxx + 40, yyyy - 14, FLinearColor(1, 1, 1, 1), G::Draw->Roboto, (XorStringW(L"%d K |%d|%dM")), ShaDi, playerteam, Distance);//
G::Draw->jzText(xxxx + 40, yyyy - 22, FLinearColor(1, 1, 1, 1), G::Draw->Roboto, (XorStringW(L"%d K 一%dM")), ShaDi, Distance);//

// DrawBone(localactor, pEntity, playercontroller, CameraManager, insertpos);

// }
// if (G::Is3DPlayer)
// {
// G::Draw->AhudBox(G::Draw->AHUDuobject, DrawP.x - w / 2, head.y - h * 0.09f, w, h, FLinearColor(1, 1, 0, 1), 1.3f);
// }

// if (G::PlayerWeapon)
// {
// uint64_t pWeaponProcessor = RPM<uint64_t>(pEntity + OFFSET_WEAPONPROCESSOR);
// uint64_t pEquippedWeapons = RPM<uint64_t>(pWeaponProcessor + OFFSET_EQUIPPEDWEAPON);
// byte pCurrentWeaponIndex = RPM<byte>(pWeaponProcessor + OFFSET_CURRENTWEAPONINDEX);
// if (pCurrentWeaponIndex >= 0 && pCurrentWeaponIndex <= 4)
// {
// uint64_t pWeapon = RPM<uint64_t>(pEquippedWeapons + pCurrentWeaponIndex * 8);
// if (pWeapon)
// {
// uint32_t WeaponID = dec_id(RPM<uint32_t>(pWeapon + OFFSET_ID));
// string WeaponName = GetNames(G::gnames, WeaponID);
// WeaponName = WeaponName.substr(4, WeaponName.size());
// WeaponName = WeaponName.substr(0, WeaponName.size() - 2);
// //G::Draw->jzText(DrawP.x, DrawP.y + 28, FLinearColor(1, 1, 0, 1), G::Draw->Roboto, char20wchar(WeaponName.c_str()));
// G::Draw->jzText(xxxx + 40, yyyy - 33, FLinearColor(1, 1, 0, 1), G::Draw->Roboto, char20wchar(WeaponName.c_str()));
// }
// }
// }
// }
if (G::EarlyWarning)
{
if (Distance <= 400)
FWRS++;
if (ZJJL == 0 || Distance < ZJJL)
ZJJL = Distance;
}
}
if (G::IsMinimap)
{
if (G::IsRader && Distance <= 225 && myteam != playerteam)
{
DOUBLE iMapPosScreenX, iMapPosScreenY;
FLinearColor MapColor;
float x = G::ScreenCenterX * 2;
float y = G::ScreenCenterY * 2;

if (G::ScreenCenterX * 2 <= 1920 || G::ScreenCenterY * 2 <= 1080)
{
iMapPosScreenX = (postion.x - Mpostion.x) / 158.f + x - x * 0.08542f;
iMapPosScreenY = (postion.y - Mpostion.y) / 158.f + y - y * 0.14444f;
}
else
{
iMapPosScreenX = (postion.x - Mpostion.x) / 117.f + x - x * 0.08542f;
iMapPosScreenY = (postion.y - Mpostion.y) / 117.f + y - y * 0.14444f;
}

RPM<float>(mMesh + OFFSET_EYE) == RPM<float>(Mesh + OFFSET_EYE) ? MapColor = { 0, 1, 0, 1 } : MapColor = { 1, 0.4f, 0, 1 };
G::Draw->MapClear(iMapPosScreenX - 4, iMapPosScreenY - 4, 6, 6, MapColor);
}
}
}
}
}
if ((type == Grenade || type == Molotov) && G::IsMissile)
{
if (Distance <= 120)
{
G::Draw->jzText(screen.x, screen.y, FLinearColor(1, 1, 0, 1), G::Draw->Roboto, (type == Grenade ? XorStringW(L"[手雷:%d]") : XorStringW(L"[燃烧弹:%d]")), Distance);
float temp = 40 - Distance / 3.2f;
G::Draw->Box(screen.x - temp / 2, screen.y - temp / 2, temp, temp, FLinearColor(1, 1, 0, 1), 1);
}
}
}

if (G::EarlyWarning) { 
// G::Draw->jzText(G::ScreenCenterX, G::ScreenCenterY + G::ScreenCenterY * 0.65f, FLinearColor(1, 1, 1, 1), G::Draw->TSLFont, XorStringW(L"400:%d   最近:%d"), FWRS, ZJJL);
// }
// if (G::BulletTrack) 
// {
// G::Draw->Line(G::ScreenCenterX - 8, G::ScreenCenterY, G::ScreenCenterX + 8, G::ScreenCenterY, FLinearColor(255, 0, 0, 1), 1);
// G::Draw->Line(G::ScreenCenterX, G::ScreenCenterY - 8, G::ScreenCenterX, G::ScreenCenterY + 8, FLinearColor(255, 0, 0, 1), 1);

// if (MyGetAsyncKeyState2(VK_RBUTTON) != 0 && aim_entity != 0)
{
G::IsShit = true;
Vector3 localeye = GetBoneWithRotation(RPM<uint64_t>(localactor + OFFSET_MESH), Bones::ik_hand_gun);
localeye.z += 15.f;

// BulletTrack(localactor, aim_entity, disTance, playercontroller, localeye, CameraManager);
// }
// else
// {
// if (G::IsShit)
// {
// WPM<int>(pAimMemoryButtonA, 0);
// }
// G::IsShit = false;
// aim_entity = 0;
// Dot = 0.0f;
// }
// }
// if (G::IsAimBot) { 
// G::Draw->AHudDrawLine(G::Draw->AHUDuobject, G::ScreenCenterX - 8, G::ScreenCenterY, G::ScreenCenterX + 8, G::ScreenCenterY, FLinearColor(0, 255, 0, 1), 1.f);
// G::Draw->AHudDrawLine(G::Draw->AHUDuobject, G::ScreenCenterX, G::ScreenCenterY - 8, G::ScreenCenterX, G::ScreenCenterY + 8, FLinearColor(0, 255, 0, 1), 1.f);




// if dfg(MyGetAsyncKeyState2(VK_RBUTTON) != 0 && aim_entity != 0)
// {gs
// float df本人血量 = RPM<float>(localactor + OFFSET_HEALTH);
// if (dsg本人血量 > 1.f)
// {gsdg
// G::IsShit d= true;
// Vector3 gdlocaleye = GetBoneWithRotation(RPM<uint64_t>(localactor + OFFSET_MESH), Bones::ik_hand_gun);
// localeyge.z += 15.f;
// AimBosdtA(localactor, aim_entity, disTance, playercontroller, localeye, CameraManager);
// }gfdg
// elsefdgsg
// {fsdsf
// if (G::IsShit)
// {
// int off = 0;
// WPM<int>(pAimMemoryButton, off);
// }
// G::IsShit = false;
// aim_entity = 0;
// Dot = 0.0f;

// }
// }
// else
// {
// if (G::IsShit)
// {
// int off = 0;
// WPM<int>(pAimMemoryButton, off);
// }
// G::IsShit = false;
// aim_entity = 0;
// Dot = 0.0f;
// }


// }
// }
// }