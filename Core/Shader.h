//#pragma once
//#include "Hazel_API.h"
//#include "Hazel_PCH.h"
//#include "Bindable.h"
//class HAZEL_API InputLayout
//{
//public:
//	void Push_float_1( LPCSTR name );
//	void Push_float_2( LPCSTR name );
//	void Push_float_3( LPCSTR name );
//	void Push_float_4( LPCSTR name );
//
//	void Push_int_1( LPCSTR name );
//	void Push_int_2( LPCSTR name );
//	void Push_int_3( LPCSTR name );
//	void Push_int_4( LPCSTR name );
//private:
//	UINT offset = 0u;
//	friend class Shader_VS;
//	vector<D3D11_INPUT_ELEMENT_DESC> layout;
//};
//
//class HAZEL_API Shader_VS :public Bindable
//{
//public:
//	Shader_VS( const wchar_t * vs_path , InputLayout & layout );
//	void Bind();
//private:
//	ComPtr<ID3D11VertexShader> vertexShader;
//	ComPtr<ID3D11InputLayout> inputLayout;
//};
//
//class HAZEL_API Shader_PS : public Bindable
//{
//public:
//	Shader_PS( const wchar_t * ps_path );
//	void Bind();
//private:
//	ComPtr<ID3D11PixelShader> pixelShader;
//};
//
//class HAZEL_API Shader_Default
//{
//public:
//	Shader_Default( const wchar_t * vs_path , const wchar_t * ps_path , InputLayout & layout );
//	void Bind();
//private:
//	unique_ptr<Shader_VS> vs_shader;
//	unique_ptr<Shader_PS> ps_shader;
//};