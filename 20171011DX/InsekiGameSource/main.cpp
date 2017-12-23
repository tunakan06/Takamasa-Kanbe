#include "my3dlib.h"

int hjikimodel;
float mx = 0.0f, mz = 2.0f;		// ���L�����̍��W
DWORD lasttime;					// �O��̃��[�v�I������(�~���b)
float looptime = 0.0f;			// 1���[�v�ɂ����鎞��(�b)
float speed = 5.0f;				// 5.0m/s

void GameMain() {

	const char * keys = GetKeyState();
	if (keys != NULL) {
		if (keys[DIK_UP] & 0x80)		mz = mz + speed*looptime;
		if(keys[DIK_DOWN] & 0x80)		mz = mz - speed*looptime;
		if(keys[DIK_LEFT] & 0x80)		mx = mx - speed*looptime;
		if(keys[DIK_RIGHT]& 0x80)		mx = mx + speed*looptime;
	}

	// ���[���h�ϊ�
	D3DXMATRIXA16 matworld1, matworld2;
	D3DXMatrixTranslation(&matworld1, mx, 0.0f, mz);
	D3DXMatrixRotationY(&matworld2, D3DX_PI);
	matworld2 *= matworld1;
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matworld2);
	RenderModel(hjikimodel);
	// �r���[�ϊ�
	/*D3DXVECTOR3		vEyePt(0.0f, 3.0f, -5.0f);
	D3DXVECTOR3		vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3		vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);
	// �ˉe�ϊ�
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, g_aspect, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);*/
}

void Render() {
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (SUCCEEDED(g_pd3dDevice->BeginScene())) {

		//g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
		GameMain();
		/*D3DXMATRIXA16 matworld1, matworld2;
		D3DXMatrixTranslation(&matworld1, 0.0f, 0.0f, 1.0f);
		D3DXMatrixRotationY(&matworld2, D3DX_PI);
		matworld2 *= matworld1;
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matworld2);
		*/
		RenderModel(hjikimodel);
		g_pd3dDevice->EndScene();
	}

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

// ���f���̃��[�h
HRESULT LoadModels() {
	hjikimodel = LoadModel(_T("catsenkan.x"));
	if (hjikimodel == -1)	return E_FAIL;
	return S_OK;
}

// �����E�r���[�E�ˉe�ϊ��̐ݒ�
void SetViews(){

	// �����̐ݒ�
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
	// �r���[�ϊ�
	D3DXVECTOR3		vEyePt(0.0f, 3.0f, -5.0f);
	D3DXVECTOR3		vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3		vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);
	// �ˉe�ϊ�
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, g_aspect, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

}

// WinMain�֐�
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	if (SUCCEEDED(InitD3DWindow(_T("覐΃Q�[��"), 640, 480))) {
		if (FAILED(LoadModels()))	return 0;	// ���f���̃��[�h
		SetViews();
		// ���b�Z�[�W���[�v
		lasttime = timeGetTime();		// ���[�v�J�n���O�̎��Ԃ��v��
		MSG msg = { 0 };
		while (msg.message != WM_QUIT) {

			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				Render();
				DWORD curtime = timeGetTime();
				looptime = (float)(curtime - lasttime) / 1000.0f;
				lasttime = curtime;
			}
		}
	}

	UnregisterClass(_T("D3D Window Class"), GetModuleHandle(NULL));
	return 0;
}