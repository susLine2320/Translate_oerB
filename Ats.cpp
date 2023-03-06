// Ats.cpp : DLL アプリケーション用のエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "atsplugin.h"
#include "Ats.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

ATS_API int WINAPI GetPluginVersion()
{
	return ATS_VERSION;
}

ATS_API void WINAPI SetVehicleSpec(ATS_VEHICLESPEC vehicleSpec)
{
	g_svcBrake = vehicleSpec.BrakeNotches;
	g_emgBrake = g_svcBrake + 1;
	//g_js1a = false;
	//g_js2 = false;
	//g_js3 = false;
	//g_js4 = false;
	//g_js5 = false;
	//g_js6a = false;
	//g_js7 = false;
	//g_js8 = false;
	//g_jsc1 = false;
	//g_jsc2 = false;
	//g_jsc3 = false;
	//g_jsc4 = false;
	//g_jsc5 = false;
	//g_jsc6 = false;
	//g_jsc7 = false;
	//g_jsc8 = false;
}

ATS_API void WINAPI Initialize(int brake)
{
	g_speed = 0;
	p234 = stnum;
	direction89 = 2;
}

ATS_API ATS_HANDLES WINAPI Elapse(ATS_VEHICLESTATE vehicleState, int *panel, int *sound)
{
	g_deltaT = vehicleState.Time - g_time;
	g_time = vehicleState.Time;
	g_speed = vehicleState.Speed;
	g_current = vehicleState.Current;

	// ハンドル出力
	if(p92 == 7 && p72 == 0 && panel[101] == 0)//小田急キー、CgSがATSの時で、ATC無信号時
	{
		g_output.Brake = oerBrake; //小田急PIからの出力Bを使用
		g_output.Power = oerNotch; //小田急PIからの出力Pを使用
		sound[0] = ATS_SOUND_STOP; //ATSベルをストップ
	}
	else
	{
		g_output.Brake = g_brakeNotch; //うさプラからの出力Bを使用
		g_output.Power = g_powerNotch; //うさプラからの出力Pを使用
		sound[25] = ATS_SOUND_STOP; //ATSベルをストップ
		sound[21] = ATS_SOUND_STOP; //ATSベルをストップ
		if (p160 == 7) {
			sound[0] = ATS_SOUND_STOP;
		}
	}
	if(g_pilotlamp)
	{
		g_output.Reverser = g_reverser;
	}
	else
	{
		g_output.Reverser = 0;
	}
	g_output.ConstantSpeed = ATS_CONSTANTSPEED_CONTINUE;

	//パネル入力
	p92 = panel[92];
	p72 = panel[72];
	p4 = panel[4];
	p19 = panel[19];
	p20 = panel[20];
	//p36 = panel[36];
	//p37 = panel[37];
	//p38 = panel[38];
	//p39 = panel[39];
	p94 = panel[94];
	p95 = panel[95];
	p97 = panel[97];
	p98 = panel[98];
	p99 = panel[99];
	p100 = panel[127];
	p136 = panel[136];
	p137 = panel[137];
	p138 = panel[138];
	p160 = panel[160];

	//サウンド入力
	oerBrake = sound[238];
	oerNotch = sound[239];

	// パネル出力（表示灯制御）
	if(p92 == 7  && (p72 == 0)){//マスコンキー小田急、かつATSのときにATS表示灯点灯フラグを立てる
		flag = 1;
	}
	else {
		flag = 0;
	}
	if (flag == 0) {
		power = 0;
	}
	if (power == 1 && p94 == 1) {//速度注意
		p94 = 1;
	}
	else {
		p94 = 0;
	}
	if (power == 1 && p95 == 1) {//動作
		p95 = 1;
	}
	else {
		p95 = 0;
	}
	if (power == 1 && p97 == 1) {//OM-ATS電源
		p97 = 1;
	}
	else {
		p97 = 0;
	}
	if (power == 1 && p98 == 1) {//D-ATS-P電源
		p98 = 1;
	}
	else {
		p98 = 0;
	}
	if (power == 1 && p99 == 1) {//無信号
		p99 = 1;
	}
	else {
		p99 = 0;
	}
	if (power == 1 && p100 == 1) {//パターン接近
		p100 = 1;
	}
	else {
		p100 = 0;
	}
	if (power == 1 && p138 == 1) {//TASC制御
		p138 = 1;
	}
	else {
		p138 = 0;
	}
	if (power == 1 && p136 == 1) {//TASC電源
		p136 = 1;
	}
	else {
		p136 = 0;
	}
	if (p4 == 1 || p39 == 1) {//フルステップ　4/39片方成立時に点灯させる
		panel[39] = 1;
	}
	else {
		panel[39] = 0;
	}
	if ((p36 == 1 || p97 == 1) && p98 == 0){//OM-ATS　小田急PIがOM-ATS設定になっていること前提
		panel[36] = 1;
	}
	else {
		panel[36] = 0;
	}
	if (p38 == 1 || p94 == 1) {//速度注意　38/94片方成立時に点灯させる
		panel[38] = 1;
	}
	else {
		panel[38] = 0;
	}
	if (p37 == 1 || p95 == 1) {//動作　37/95片方成立時に点灯させる
		panel[37] = 1;
	}
	else {
		panel[37] = 0;
	}
	if (p98 == 1) {//D-ATS-P電源
		panel[98] = 1;
	}
	else {
		panel[98] = 0;
	}
	if (p99 == 1) {//無信号
		panel[99] = 1;
	}
	else {
		panel[99] = 0;
	}
	if (p100 == 1) {//パターン接近
		panel[127] = 1;
	}
	else {
		panel[127] = 0;
	}
	if (p136 == 1) {//TASC電源
		panel[136] = 1;
	}
	else {
		panel[136] = 0;
	}
	if (p19 == 1 && p137 == 1) {//ATO電源　ATC投入が前提（ATSでは作動しない）
		panel[137] = 1;
	}
	else {
		panel[137] = 0;
	}
	if (p138 == 1) {//TASC制御
			panel[138] = 1;
		}
	else {
		panel[138] = 0;
	}
	if (p160 == 7) {//次の停車駅表示は小田急キーの時のみ
		panel[234] = p234 % 100;
	}
	else {
		panel[234] = 0;
	}
	//以下独自仕様
	if (p166 == 1) {
		panel[166] = 1;
	}
	else {
		panel[166] = 0;
	}
	//パネル出力（うさプラ代替機能）
	panel[51] = g_output.Brake == g_emgBrake? 9 : g_output.Brake;
	panel[52] = g_current < 0 && g_speed > 4.99f ? 1 : 0;
	panel[53] = g_current < 0 && g_speed > 22.99f ? 1 : 0;
	panel[54] = g_current < 0 && g_speed > 19.99f ? 1 : 0;
	panel[55] = g_output.Brake;
	panel[57] = g_output.Brake;
	panel[66] = g_output.Power;
	// サウンド出力
/*
	sound[33] = g_js1a;
	sound[35] = g_js1b;
	sound[36] = g_js2;
	sound[38] = g_js3;
	sound[50] = g_js4;
	sound[52] = g_js5;
	sound[54] = g_js6a;
	sound[55] = g_js6b;
	sound[57] = g_js7;
	sound[59] = g_js8;
/*
	sound[34] = g_jsc1;
	sound[37] = g_jsc2;
	sound[39] = g_jsc3;
	sound[51] = g_jsc4;
	sound[53] = g_jsc5;
	sound[56] = g_jsc6;
	sound[58] = g_jsc7;
	sound[60] = g_jsc8;
*/
	//安全上の処理
	sound[238] = ATS_SOUND_STOP;
	sound[239] = ATS_SOUND_STOP;

	//乗降促進
	if(g_js1a == true)
	{
		sound[33] = ATS_SOUND_PLAYLOOPING;
	}
	else
	{
		sound[33] = ATS_SOUND_STOP;
	}
	if (g_js1b == true)
	{
		sound[35] = ATS_SOUND_PLAYLOOPING;
	}
	else
	{
		sound[35] = ATS_SOUND_STOP;
	}
	
	if (g_js2 == true)
	{
		sound[62] = ATS_SOUND_PLAYLOOPING;
	}
	else
	{
		sound[62] = ATS_SOUND_STOP;
	}
	if (g_js3a == true)
	{
		sound[64] = ATS_SOUND_PLAYLOOPING;
	}
	else
	{
		sound[64] = ATS_SOUND_STOP;
	}
	if (g_js3b == true)
	{
		sound[65] = ATS_SOUND_PLAYLOOPING;
	}
	else
	{
		sound[65] = ATS_SOUND_STOP;
	}
	if (g_js4 == true)
	{
		sound[73] = ATS_SOUND_PLAYLOOPING;
	}
	else
	{
		sound[73] = ATS_SOUND_STOP;
	}
	/*/
	if (g_js5 == true)
	{
		sound[75] = ATS_SOUND_PLAYLOOPING;
	}
	else
	{
		sound[75] = ATS_SOUND_STOP;
	}
	*/
	if (g_js6a == true)
	{
		sound[59] = ATS_SOUND_PLAYLOOPING;
	}
	else
	{
		sound[59] = ATS_SOUND_STOP;
	}
	if (g_js6b == true)
	{
		sound[61] = ATS_SOUND_PLAYLOOPING;
	}
	else
	{
		sound[61] = ATS_SOUND_STOP;
	}
	if (g_js7 == true)
	{
		sound[57] = ATS_SOUND_PLAYLOOPING;
	}
	else
	{
		sound[57] = ATS_SOUND_STOP;
	}
	/*
	if (g_js8 == true)
	{
		sound[59] = ATS_SOUND_PLAYLOOPING;
	}
	else
	{
		sound[59] = ATS_SOUND_STOP;
	}
	*/
	if (g_jsc1 == true)
	{
		sound[34] = ATS_SOUND_PLAY;
		g_jsc1 = false;
	}
	else
	{
		sound[34] = ATS_SOUND_CONTINUE;
	}
	
	if (g_jsc2 == true)
	{
		sound[63] = ATS_SOUND_PLAY;
		g_jsc2 = false;
	}
	else
	{
		sound[63] = ATS_SOUND_CONTINUE;
	}
	if (g_jsc3 == true)
	{
		sound[66] = ATS_SOUND_PLAY;
		g_jsc3 = false;
	}
	else
	{
		sound[66] = ATS_SOUND_CONTINUE;
	}
	if (g_jsc4 == true)
	{
		sound[74] = ATS_SOUND_PLAY;
		g_jsc4 = false;
	}
	else
	{
		sound[74] = ATS_SOUND_CONTINUE;
	}
	/*
	if (g_jsc5 == true)
	{
		sound[76] = ATS_SOUND_PLAY;
		g_jsc5 = false;
	}
	else
	{
		sound[76] = ATS_SOUND_CONTINUE;
	}
	*/
	if (g_jsc6 == true)
	{
		sound[60] = ATS_SOUND_PLAY;
		g_jsc6 = false;
	}
	else
	{
		sound[60] = ATS_SOUND_CONTINUE;
	}
	if (g_jsc7 == true)
	{
		sound[58] = ATS_SOUND_PLAY;
		g_jsc7 = false;
	}
	else
	{
		sound[58] = ATS_SOUND_CONTINUE;
	}
	/*
	if (g_jsc8 == true)
	{
		sound[60] = ATS_SOUND_PLAY;
		g_jsc8 = false;
	}
	else
	{
		sound[60] = ATS_SOUND_CONTINUE;
	}
	*/
	/*g_js1a = ATS_SOUND_STOP;
	g_js1b = ATS_SOUND_STOP;
	g_js2 = ATS_SOUND_STOP;
	g_js3 = ATS_SOUND_STOP;
	g_js4 = ATS_SOUND_STOP;
	g_js5 = ATS_SOUND_STOP;
	g_js6a = ATS_SOUND_STOP;
	g_js6b = ATS_SOUND_STOP;
	g_js7 = ATS_SOUND_STOP;
	g_js8 = ATS_SOUND_STOP;
	sound[34] = ATS_SOUND_CONTINUE;
	sound[37] = ATS_SOUND_CONTINUE;
	sound[39] = ATS_SOUND_CONTINUE;
	sound[51] = ATS_SOUND_CONTINUE;
	sound[53] = ATS_SOUND_CONTINUE;
	sound[56] = ATS_SOUND_CONTINUE;
	sound[58] = ATS_SOUND_CONTINUE;
	sound[60] = ATS_SOUND_CONTINUE;
	*/
	if (g_mon == true)
	{
		sound[38] = ATS_SOUND_PLAY;
		g_mon = false;
	}
	else
	{
		sound[38] = ATS_SOUND_CONTINUE;
	}
	if (p92 != 7) {//小田急キーでない時
		sound[54] = ATS_SOUND_STOP;
		sound[55] = ATS_SOUND_STOP;
	}
    return g_output;
}

ATS_API void WINAPI SetPower(int notch)
{
	g_powerNotch = notch;
}

ATS_API void WINAPI SetBrake(int notch)
{
	g_brakeNotch = notch;//フラグがたっているとマスコンを動かしたときに表示灯がつく
	if (flag == 1) {
		power = 1;
	}
}

ATS_API void WINAPI SetReverser(int pos)
{
	g_reverser = pos;
}

ATS_API void WINAPI KeyDown(int atsKeyCode)
{
	if (atsKeyCode == ATS_KEY_D && g_speed == 0)
	{
		if (p92 == 1 && direction == 1)
			g_js1a = true;
		else if (p92 == 1 && direction == 0)
			g_js1b = true;
		else if (p92 == 2)
			g_js2 = true;
		else if (p92 == 3 && direction == 1)
			g_js3a = true;
		else if (p92 == 3 && direction == 0)
			g_js3b = true;
		else if (p92 == 4)
			g_js4 = true;
		else if (p92 == 5)
			g_js5 = true;
		else if (p92 == 6 && direction == 1)
			g_js6a = true;
		else if (p92 == 6 && direction == 0)
			g_js6b = true;
		else if (p92 == 7)
			g_js7 = true;
		else if (p92 == 8)
			g_js8 = true;
		else
			g_js1a = true;
	}
	if (atsKeyCode == ATS_KEY_E)
	{
		g_mon = true;
		if (p166 == 1)
			p166 = 0;
		else
			p166 = 1;
	}
}

ATS_API void WINAPI KeyUp(int hornType)
{
	if (hornType == ATS_KEY_D)
	{
		g_js1a = false;
		g_js1b = false;
		g_js2 = false;
		g_js3a = false;
		g_js3b = false;
		g_js4 = false;
		g_js5 = false;
		g_js6a = false;
		g_js6b = false;
		g_js7 = false;
		g_js8 = false;
		if (g_speed == 0) {
			if (p92 == 1)
				g_jsc1 = true;
			else if (p92 == 2)
				g_jsc2 = true;
			else if (p92 == 3)
				g_jsc3 = true;
			else if (p92 == 4)
				g_jsc4 = true;
			else if (p92 == 5)
				g_jsc5 = true;
			else if (p92 == 6)
				g_jsc6 = true;
			else if (p92 == 7)
				g_jsc7 = true;
			else if (p92 == 8)
				g_jsc8 = true;
			else
				g_jsc1 = true;
		}
	}
}

ATS_API void WINAPI HornBlow(int atsHornBlowIndex)
{
}

ATS_API void WINAPI DoorOpen()//ドアが開くときに次の停車駅を代入する
{
	p234 = stnum;
	g_pilotlamp = false;
}

ATS_API void WINAPI DoorClose()
{
	g_pilotlamp = true;
}

ATS_API void WINAPI SetSignal(int signal)
{
}

ATS_API void WINAPI SetBeaconData(ATS_BEACONDATA beaconData)
{
	if (beaconData.Type == 70) {//次の停車駅を取得
		stnum = beaconData.Optional;
	}
	if (beaconData.Type == 89) {//運転方向を取得（本仕様）
		direction89 = 1;
		direction = beaconData.Optional % 2;
	}
	if (beaconData.Type == 19 && direction89 == 2) {//運転方向を取得（バックアップ）
		direction = beaconData.Optional % 2;
	}
}

ATS_API void WINAPI Load() {}
ATS_API void WINAPI Dispose() {}
