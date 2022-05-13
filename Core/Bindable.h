#pragma once
#include <d3d11.h>

class Bindable
{
public:
	static void Init( ID3D11Device * d , ID3D11DeviceContext * c );
protected:
	static ID3D11Device * device;
	static ID3D11DeviceContext * context;
};
