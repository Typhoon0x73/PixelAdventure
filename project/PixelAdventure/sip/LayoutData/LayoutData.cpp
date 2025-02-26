#include "LayoutData.h"

namespace sip::layout
{
	namespace
	{
		enum class LayoutType : int32
		{
			Invalid = -1,
			Rect = 0,
			Point,
		};

		enum class RowKind : size_t
		{
			IDs = 0,
			PageName,
			LayoutSize,
			LayoutInfo,
		};
	}

	Data::Data()
		: m_name{ U"" }
		#ifdef LAYOUT_DATA_USE_HOST_ID
		, m_hostId{ U"" }
		#endif // LAYOUT_DATA_USE_HOST_ID
		#ifdef LAYOUT_DATA_USE_DIAGRAM_ID
		, m_diagramId{ U"" }
		#endif // LAYOUT_DATA_USE_DIAGRAM_ID
		, m_layoutSize{ Size::Zero() }
		, m_rectangleTable{}
		, m_pointTable{}
	{
	}

	Data::Data(const Data& data)
		: Data{}
	{
		*this = data;
	}

	Data::Data(FilePathView path)
		: Data{}
	{
		load(path);
	}

	Data::~Data()
	{
	}

	bool Data::load(FilePathView path)
	{
		CSV csv{ path };
		if (csv.isEmpty())
		{
			return false;
		}

		const auto& data = csv.getData();
		if (data.size() < 3)
		{
			return false;
		}

		#ifdef LAYOUT_DATA_USE_HOST_ID
		{
			const auto& ids = data[FromEnum(RowKind::IDs)];
			if (ids.size() < 1)
			{
				return false;
			}
			m_hostId.assign(ids[0]);
		}
		#endif // LAYOUT_DATA_USE_HOST_ID

		#ifdef LAYOUT_DATA_USE_DIAGRAM_ID
		{
			const auto& ids = data[FromEnum(RowKind::IDs)];
			if (ids.size() < 2)
			{
				return false;
			}
			m_diagramId.assign(ids[1]);
		}
		#endif // LAYOUT_DATA_USE_DIAGRAM_ID

		const auto& pageNameLine = data[FromEnum(RowKind::PageName)];
		if (pageNameLine.size() <= 0)
		{
			return false;
		}
		m_name.assign(pageNameLine[0]);

		const auto& layoutSizeLine = data[FromEnum(RowKind::LayoutSize)];
		if (layoutSizeLine.size() < 3
			|| (0 < layoutSizeLine.size() && layoutSizeLine[0] != U"layout_size"))
		{
			return false;
		}
		int32 layoutSizeW = ParseOr<int32, int32>(layoutSizeLine[1], -1);
		int32 layoutSizeH = ParseOr<int32, int32>(layoutSizeLine[2], -1);
		if (layoutSizeW < 0 || layoutSizeH < 0)
		{
			return false;
		}
		m_layoutSize.set(layoutSizeW, layoutSizeH);

		for (size_t row = FromEnum(RowKind::LayoutInfo); row < csv.rows(); row++)
		{
			const auto& layoutInfo = data[row];
			if (layoutInfo.size() < 2)
			{
				return false;
			}
			const auto& layoutKey = layoutInfo[0];
			LayoutType layoutType = ToEnum<LayoutType>(ParseOr<int32, int32>(layoutInfo[1], -1));
			switch (layoutType)
			{
			case LayoutType::Rect:
			{
				if (layoutInfo.size() < 6)
				{
					return false;
				}
				int32 x = ParseOr<int32, int32>(layoutInfo[2], 0);
				int32 y = ParseOr<int32, int32>(layoutInfo[3], 0);
				int32 w = ParseOr<int32, int32>(layoutInfo[4], 0);
				int32 h = ParseOr<int32, int32>(layoutInfo[5], 0);
				m_rectangleTable.emplace(layoutKey, Rect{ x, y, w, h });
				break;
			}
			case LayoutType::Point:
			{
				if (layoutInfo.size() < 4)
				{
					return false;
				}
				int32 x = ParseOr<int32, int32>(layoutInfo[2], 0);
				int32 y = ParseOr<int32, int32>(layoutInfo[3], 0);
				m_pointTable.emplace(layoutKey, Point{ x, y });
				break;
			}
			case LayoutType::Invalid:
			default:
			{
				return false;
			}
			}
		}
		return true;
	}

	void Data::getHostId(String& out) const
	{
		#ifdef LAYOUT_DATA_USE_HOST_ID
		out.assign(m_hostId);
		#else
		out.assign(U"");
		#endif // LAYOUT_DATA_USE_HOST_ID
	}

	void Data::getDiagramId(String& out) const
	{
		#ifdef LAYOUT_DATA_USE_DIAGRAM_ID
		out.assign(m_diagramId);
		#else
		out.assign(U"");
		#endif // LAYOUT_DATA_USE_DIAGRAM_ID
	}

	void Data::getName(String& out) const
	{
		out.assign(m_name);
	}

	const String& Data::getName() const
	{
		return m_name;
	}

	void Data::getLayoutSize(Size& out) const
	{
		out = m_layoutSize;
	}

	const Size& Data::getLayoutSize() const
	{
		return m_layoutSize;
	}

	Optional<Rect> Data::findRect(const String& key) const
	{
		auto it = m_rectangleTable.find(key);
		if (it == m_rectangleTable.end())
		{
			return none;
		}
		return it->second;
	}

	Optional<Point> Data::findPoint(const String& key) const
	{
		auto it = m_pointTable.find(key);
		if (it == m_pointTable.end())
		{
			return none;
		}
		return it->second;
	}

	Data& layout::Data::operator=(const Data& value)
	{
		#ifdef LAYOUT_DATA_USE_HOST_ID
		m_hostId = value.m_hostId;
		#endif // LAYOUT_DATA_USE_HOST_ID

		#ifdef LAYOUT_DATA_USE_DIAGRAM_ID
		m_diagramId = value.m_diagramId;
		#endif // LAYOUT_DATA_USE_DIAGRAM_ID

		m_name = value.m_name;

		m_layoutSize = value.m_layoutSize;

		m_rectangleTable = value.m_rectangleTable;
		m_pointTable = value.m_pointTable;
		return *this;
	}

}
