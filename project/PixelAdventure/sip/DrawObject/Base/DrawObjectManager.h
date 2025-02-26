#ifndef SIP_DRAW_OBJECT_MANAGER_H_
#define SIP_DRAW_OBJECT_MANAGER_H_
#pragma once

// INCLUDE
#include "LayerDefine.h"
#include <Siv3D.hpp>

namespace sip
{

	class DrawObject;
	class DrawObjectManager
	{
	public:
		DrawObjectManager();
		~DrawObjectManager();

		void addObject(define::Layer layer, DrawObject* obj);
		void setRootScale(double x, double y);
		void setRootScale(double x, double y, const Array<define::Layer>& layer);

		void draw() const;

		void print() const;

	private:

		void drawObject(const DrawObject* obj) const;

		std::unique_ptr<DrawObject> m_pRootObjects[FromEnum(define::Layer::Count)];
	};
}
#endif // !SIP_DRAW_OBJECT_MANAGER_H_
