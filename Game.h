//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include "DebugCamera.h"
#include "Camera.h"
#include "FollowCamera.h"

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include <Keyboard.h>


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
	//�f�o�b�O�J����
	std::unique_ptr<DebugCamera> m_debugCamera;
	//�G�t�F�N�g�t�@�N�g���[
	std::unique_ptr<DirectX::EffectFactory> m_factory;
	//�n�ʃ��f��
	std::unique_ptr<DirectX::Model> m_model;
	//�V�����f��
	std::unique_ptr<DirectX::Model> m_skydome_model;
	//�����f��
	std::unique_ptr<DirectX::Model> m_ball_model;
	//�^���N���f��
	std::unique_ptr<DirectX::Model> m_tank_model;
	//�e�B�[�|�b�g���f��
	std::unique_ptr<DirectX::Model> m_tea_model;
	//�e�B�[�|�b�g�̃��[���h�s��i�O���j
	DirectX::SimpleMath::Matrix m_world_tea[20];
	//�e�B�[�|�b�g�̈ʒu���W
	float rad[20];
	//���_����̃e�B�[�|�b�g�̋���
	float distance[20];
	float rotate;
	float scale;

	//�L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>keyboard;

	//���@�̍��W
	DirectX::SimpleMath::Matrix tank_world;
	DirectX::SimpleMath::Vector3 tank_pos;

	float tank_rotate;




	//���̃��[���h�s��
	DirectX::SimpleMath::Matrix m_worldBall;
	//���̃��[���h�s��i�����j
	DirectX::SimpleMath::Matrix m_world_ball_in[10];
	//���̃��[���h�s��i�O���j
	DirectX::SimpleMath::Matrix m_world_ball_out[10];

	//�J����
	std::unique_ptr<FollowCamera> m_camera;


};