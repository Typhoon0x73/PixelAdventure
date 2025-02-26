#ifndef SIP_LAYOUT_DATA_H_
#define SIP_LAYOUT_DATA_H_
#pragma once

#include <Siv3D.hpp>

#define LAYOUT_DATA_USE_HOST_ID
#define LAYOUT_DATA_USE_DIAGRAM_ID


namespace sip::layout
{
	class Data
	{
	public:

		Data();
		Data(const Data& data);

		/// @brief コンストラクタ
		/// ファイルからデータを作成する。
		/// @param path ファイルパス
		Data(FilePathView path);

		/// @brief デストラクタ
		virtual ~Data();

		virtual bool load(FilePathView path);

		virtual void getHostId(String& out) const;
		virtual void getDiagramId(String& out) const;

		virtual void getName(String& out) const;
		virtual const String& getName() const;

		virtual void getLayoutSize(Size& out) const;
		virtual const Size& getLayoutSize() const;

		virtual Optional<Rect> findRect(const String& key) const;
		virtual Optional<Point> findPoint(const String& key) const;

		virtual Data& operator=(const Data& value);

	private:

#ifdef LAYOUT_DATA_USE_HOST_ID
		String m_hostId;
#endif // LAYOUT_DATA_USE_HOST_ID

#ifdef LAYOUT_DATA_USE_DIAGRAM_ID
		String m_diagramId;
#endif // LAYOUT_DATA_USE_DIAGRAM_ID

		String m_name;

		Size m_layoutSize;

		HashTable<String, Rect> m_rectangleTable;
		HashTable<String, Point> m_pointTable;
	};
}

#endif // !SIP_LAYOUT_DATA_H_

