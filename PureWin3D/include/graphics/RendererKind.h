#ifndef PW_RENDERER_KIND_H
#define PW_RENDERER_KIND_H

#ifdef PW_PLATFORM_WIN32
#pragma warning( disable : 4005 )
#   include <D3D11.h>
#	include <DXGI.h>
#   include <D3DX11.h>
#   include <DxErr.h>
#pragma warning( default : 4005 )
#endif

namespace pw
{
	enum class RendererKind : uint_fast8_t
	{
#		ifdef PW_PLATFORM_WIN32
		D3D11,
		Default = D3D11
#       else
		Default
#       endif
	};
}

#endif