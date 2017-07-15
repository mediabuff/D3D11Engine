//D3D11ShaderResourceView.h
//Created 15/07/17
//Created By Daniel Bowler
//
//ID3D11ShaderResourceView*

#pragma once

//Parent class
#include <Graphics/ViewResource/ViewResource.h>

//Graphics includes - inc D3D11
#include <Includes/GraphicsIncludes.h>

//Debug
#include <Debug/Log/DebugLog.h>

//Device used to create views
#include <Graphics/GraphicsDevice/GraphicsDevice.h>

namespace EngineAPI
{
	namespace Graphics
	{
		class Texture2D;
		class RenderTexture2D;
		class DepthStencilTexture2D;
	};
};

namespace EngineAPI
{
	namespace Graphics
	{
		namespace Platform
		{
			class D3D11ShaderResourceView : public EngineAPI::Graphics::ViewResource
			{
			public:
				D3D11ShaderResourceView() {};
				virtual ~D3D11ShaderResourceView() = 0 {};

				//Inits the D3D11 SRV
				bool InitShaderResourceViewToTexture2D(EngineAPI::Graphics::GraphicsDevice* device,
					EngineAPI::Graphics::Texture2D* texture,
					bool doUseUnderlyingResourceFormatForView = true,
					ResourceFormat renderTargetTextureViewFormat = RESOURCE_FORMAT_UNKNOWN,
					std::string debugName = std::string(""));

				//Shutdown the SRV
				virtual void Shutdown() override;

			public:
				//Getters
				ID3D11ShaderResourceView* GetD3D11RenderTargetView() { return srv; };

			protected:
				//Description.
				D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

				//SRV handle
				ID3D11ShaderResourceView* srv = nullptr;
			};
		};
	};
};