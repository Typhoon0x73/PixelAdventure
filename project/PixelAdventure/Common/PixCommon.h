#pragma once
#ifndef PIX_COMMON_H_
#define PIX_COMMON_H_

#include <Siv3D.hpp>

#include "../Scene/PixSceneData.h"
#include "../Scene/PixSceneDefine.h"

#ifdef _DEBUG

#define PIX_ASSERT(b) if (!(b)) __debugbreak()

#else

#define PIX_ASSERT(b) (void)(b)

#endif // _DEBUG



namespace pix
{
	using SceneManager = s3d::SceneManager<pix::SceneKind, pix::SceneData>;
}

#endif // !PIX_COMMON_H_
