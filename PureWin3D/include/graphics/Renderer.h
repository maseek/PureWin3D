#ifndef PW_RENDERER_H
#define PW_RENDERER_H

#include "RendererKind.h"

namespace pw
{
	bool loadRenderer( RendererKind rendererKind );
	namespace
	{
		const std::string& rendererKindToFileName( RendererKind rendererKind );
	}
}

#endif