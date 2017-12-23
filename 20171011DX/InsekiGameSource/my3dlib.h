#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>

struct Model
{
	LPD3DXMESH				pmesh;			// メッシュ
	D3DMATERIAL9*			pmaterials;		// マテリアルの配列
	LPDIRECT3DTEXTURE9*		ptextures;		// テクスチャの配列
	DWORD					nummaterials;	// マテリアルの数
	BOOL used;								// データが入ってるか示すフラグ
};

// global変数
extern LPDIRECT3D9			g_pD3D;
extern LPDIRECT3DDEVICE9	g_pd3dDevice;
extern float				g_aspect;
extern Model				g_models[];

// 関数プロトタイプ宣言
HRESULT InitD3DWindow(LPCTSTR wintitle, int w, int h);
int LoadModel(LPCTSTR filename);
void RenderModel(int idx);
const char* GetKeyState();