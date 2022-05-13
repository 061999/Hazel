//#include "Shader.h"
//#include <d3dcompiler.h>
//#pragma comment(lib,"d3dcompiler.lib")
//void InputLayout::Push_float_1( LPCSTR name )
//{
//	layout.push_back( { name,0,DXGI_FORMAT_R32_FLOAT,0,offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
//	offset += sizeof( float );
//}
//
//void InputLayout::Push_float_2( LPCSTR name )
//{
//	layout.push_back( { name,0,DXGI_FORMAT_R32G32_FLOAT,0,offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
//	offset += sizeof( float ) * 2;
//}
//
//void InputLayout::Push_float_3( LPCSTR name )
//{
//	layout.push_back( { name,0,DXGI_FORMAT_R32G32B32_FLOAT,0,offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
//	offset += sizeof( float ) * 3;
//}
//
//void InputLayout::Push_float_4( LPCSTR name )
//{
//	layout.push_back( { name,0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
//	offset += sizeof( float ) * 4;
//}
//
//void InputLayout::Push_int_1( LPCSTR name )
//{ 
//	layout.push_back( { name,0,DXGI_FORMAT_R32_SINT,0,offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
//	offset += sizeof( int );
//}
//
//void InputLayout::Push_int_2( LPCSTR name )
//{ 
//	layout.push_back( { name,0,DXGI_FORMAT_R32G32_SINT,0,offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
//	offset += sizeof( int ) * 2;
//}
//
//void InputLayout::Push_int_3( LPCSTR name )
//{
//	layout.push_back( { name,0,DXGI_FORMAT_R32G32B32_SINT,0,offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
//	offset += sizeof( int ) * 3;
//}
//
//void InputLayout::Push_int_4( LPCSTR name )
//{
//	layout.push_back( { name,0,DXGI_FORMAT_R32G32B32A32_SINT,0,offset,D3D11_INPUT_PER_VERTEX_DATA,0 } );
//	offset += sizeof( int ) * 4;
//}
//
//Shader_VS::Shader_VS( const wchar_t * vs_path , InputLayout & layout )
//{
//	ComPtr<ID3DBlob> b;
//	D3DReadFileToBlob( vs_path , b.GetAddressOf() );
//	device->CreateVertexShader( b->GetBufferPointer() , b->GetBufferSize() , nullptr , vertexShader.GetAddressOf() );
//
//	device->CreateInputLayout( layout.layout.data() , (UINT)layout.layout.size() , b->GetBufferPointer() , b->GetBufferSize() , inputLayout.GetAddressOf() );
//
//}
//
//void Shader_VS::Bind()
//{ 
//	context->IASetInputLayout( inputLayout.Get() );
//	context->VSSetShader( vertexShader.Get() , nullptr , 0u );
//}
//
//Shader_PS::Shader_PS( const wchar_t * ps_path )
//{
//	ComPtr<ID3DBlob> b1;
//	D3DReadFileToBlob( ps_path , b1.GetAddressOf() );
//	device->CreatePixelShader( b1->GetBufferPointer() , (UINT)b1->GetBufferSize() , nullptr , pixelShader.GetAddressOf() );
//}
//
//void Shader_PS::Bind()
//{
//	context->PSSetShader( pixelShader.Get() , nullptr , 0u );
//}
//
//Shader_Default::Shader_Default( const wchar_t * vs_path , const wchar_t * ps_path , InputLayout & layout )
//{
//	vs_shader = make_unique<Shader_VS>( vs_path , layout );
//	ps_shader = make_unique<Shader_PS>( ps_path );
//}
//
//void Shader_Default::Bind()
//{
//	vs_shader->Bind();
//	ps_shader->Bind();
//}
