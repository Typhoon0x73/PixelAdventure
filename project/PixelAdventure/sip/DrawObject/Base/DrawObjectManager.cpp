
#include "DrawObjectManager.h"
#include "DrawObject.h"
#include "../../DebugLog/DebugLog.h"

namespace
{

#ifdef _DEBUG
	void ChildPrint(const sip::DrawObject* pObj, int32 nestCount)
	{
		String tab = U"";
		for ([[maybe_unused]] auto i : step(nestCount))
		{
			tab += U"\t";
		}
		tab.insert(static_cast<size_t>(nestCount - 1), U"┃");
		//tab += U"┃";

		for (auto* pNext = pObj->getFirstChild(); pNext; pNext = pNext->getNextSibling())
		{
			String connectStr = (pNext->getNextSibling() == nullptr ? U"┣" : U"┗");
			sip::DebugLog::Print(sip::DebugLog::LogType::Info, U"{}{}{}"_fmt(tab, connectStr, pNext->getName()));
			ChildPrint(pNext, nestCount++);
		}
	}
#endif // _DEBUG

}

namespace sip
{
	class RootObject : public DrawObject
	{
	public:
		using DrawObject::DrawObject;
		virtual ~RootObject() {}
		virtual void draw() const override {}
	};

	DrawObjectManager::DrawObjectManager()
		: m_pRootObjects{}
	{
		for (size_t i = 0; i < FromEnum(define::Layer::Count); i++)
		{
			auto root = new RootObject(ToEnum<define::Layer>(i));
			root->setName(U"root[{}]"_fmt(i));
			m_pRootObjects[i].reset(root);
		}
	}

	DrawObjectManager::~DrawObjectManager()
	{
		for (auto& it : m_pRootObjects)
		{
			it.reset();
		}
	}

	void DrawObjectManager::addObject(define::Layer layer, DrawObject* obj)
	{
		auto* pRoot = m_pRootObjects[static_cast<int>(layer)].get();
		if (not pRoot)
		{
			return;
		}
		pRoot->addChild(obj);
	}

	void DrawObjectManager::setRootScale(double x, double y)
	{
		for (size_t i = 0; i < FromEnum(define::Layer::Count); i++)
		{
			auto* pRoot = m_pRootObjects[i].get();
			pRoot->setScale(x, y);
		}
	}

	void DrawObjectManager::setRootScale(double x, double y, const Array<define::Layer>& layer)
	{
		for (size_t i = 0; i < layer.size(); i++)
		{
			size_t index = static_cast<size_t>(layer[i]);
			auto* pRoot = m_pRootObjects[index].get();
			pRoot->setScale(x, y);
		}
	}

	void DrawObjectManager::draw() const
	{
		for (size_t i = 0; i < FromEnum(define::Layer::Count); i++)
		{
			const auto& object = m_pRootObjects[i];
			for (auto child = object->getFirstChild(); child; child = child->getNextSibling())
			{
				drawObject(child);
			}
		}
	}

	void DrawObjectManager::print() const
	{
#ifdef _DEBUG
		sip::DebugLog::Print(sip::DebugLog::LogType::Info,
			U"------------------------------\n"
			U"object tree\n"
			U"------------------------------"
		);
		int32 nestCount = 0;
		for (const auto& pObj : m_pRootObjects)
		{
			sip::DebugLog::Print(sip::DebugLog::LogType::Info,pObj->getName());
			ChildPrint(pObj.get(), nestCount++);
		}
		sip::DebugLog::Print(sip::DebugLog::LogType::Info,
			U"------------------------------"
		);
#endif // _DEBUG

	}

	void DrawObjectManager::drawObject(const DrawObject* obj) const
	{
		if (not obj)
		{
			return;
		}
		obj->draw();
		for (auto child = obj->getFirstChild(); child; child = child->getNextSibling())
		{
			drawObject(child);
		}
	}
}
