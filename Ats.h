// 以下の ifdef ブロックは DLL から簡単にエクスポートさせるマクロを作成する標準的な方法です。 
// この DLL 内のすべてのファイルはコマンドラインで定義された ATS_EXPORTS シンボル
// でコンパイルされます。このシンボルはこの DLL が使用するどのプロジェクト上でも未定義でなけ
// ればなりません。この方法ではソースファイルにこのファイルを含むすべてのプロジェクトが DLL 
// からインポートされたものとして ATS_API 関数を参照し、そのためこの DLL はこのマク 
// ロで定義されたシンボルをエクスポートされたものとして参照します。
//#pragma data_seg(".shared")
//#pragma data_seg()

#define ATS_BEACON_S 0 // Sロング
#define ATS_BEACON_SN 1 // SN直下
#define ATS_BEACON_SNRED 2 // SN誤出発防止
#define ATS_BEACON_P 3 // P停止信号
#define ATS_BEACON_EMG 4 // P即停(非常)
#define ATS_BEACON_SVC 5 // P即停(常用)
#define ATS_BEACON_SPDLIM 6 // P分岐器速度制限
#define ATS_BEACON_SPDMAX 7 // P最高速度
#define ATS_BEACON_SPP 8 // 停車駅通過防止装置

int g_emgBrake; // 非常ノッチ
int g_svcBrake; // 常用最大ノッチ
int g_brakeNotch; // ブレーキノッチ
int g_powerNotch; // 力行ノッチ
int g_reverser; // レバーサ
bool g_pilotlamp; // パイロットランプ
int g_time; // 現在時刻
float g_speed; // 速度計の速度[km/h]
float g_current; //電流
int g_deltaT; // フレーム時間[ms/frame]
bool g_js1a; //メトロ乗降促進ブザーA
bool g_js1b; //メトロ乗降促進ブザーB
bool g_js2; //東武乗降促進ブザー
bool g_js3a; //東急乗降促進ブザーA
bool g_js3b; //東急乗降促進ブザーB
bool g_js4; //西武乗降促進ブザー
bool g_js5; //相鉄乗降促進ブザー
bool g_js6a; //JR乗降促進ブザーA
bool g_js6b; //JR乗降促進ブザーB
bool g_js7; //小田急乗降促進メロディ
bool g_js8; //東葉乗降促進ブザー
bool g_jsc1; //メトロ乗降促進放送
bool g_jsc2; //東武乗降促進放送
bool g_jsc3; //東急乗降促進放送
bool g_jsc4; //西武乗降促進チャイム・放送
bool g_jsc5; //相鉄乗降促進放送
bool g_jsc6; //JR乗降促進放送
bool g_jsc7; //小田急乗降促進放送
bool g_jsc8; //東葉乗降促進放送
bool g_mon;//モニタ操作音
int p92;
int p72;
int p4;
int p20;
int p19;
int p36;
int p37;
int p38;
int p39;
int p94;
int p95;
int p97;
int p98;
int p99;
int p100;
int p136;
int p137;
int p138;
int p160;
int p166;
int p234;
int oerNotch;//小田急PIの出力P
int oerBrake;//小田急PIの出力B
bool UsaoDisable;//うさプラの出力切断
bool ATSFlag;
bool flag;
bool power;
int stnum;
int direction;
int direction89;

ATS_HANDLES g_output; // 出力
