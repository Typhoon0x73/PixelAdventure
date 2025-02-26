#include "AssetPackage.h"

namespace sip
{
    AssetPackage::AssetPackage()
        : m_name{ U"" }
        , m_assets{}
    {
    }

    AssetPackage::~AssetPackage()
    {
    }

    bool AssetPackage::Load(FilePathView path)
    {
        JSON json = JSON::Load(path);
        if (json.isEmpty()) 
        {
            return false;
        }
        if (json.hasElement(U"pack_name"))
        {
            m_name = json[U"pack_name"].getString();
        }
        else
        {
            return false;
        }
        if (json.hasElement(U"resources"))
        {
            const JSON& resources = json[U"resources"];
            if (not resources.isObject())
            {
                return false;
            }
            for (const auto& resource : resources)
            {
                if (not resource.value.isArray())
                {
                    return false;
                }
                for (const auto& object : resource.value)
                {
					for (const auto& item : object.value)
					{
						if (not item.value.isString())
						{
							return false;
						}
						PackageValue value{ item.key, item.value.getString() };
						m_assets[resource.key].emplace_back(value);
					}
                }
            }
        }
        else
        {
            return false;
        }
        return true;
    }

    StringView AssetPackage::getPackageName() const
    {
        return m_name;
    }

    const AssetPackage::AssetTable& AssetPackage::getAssetTable() const
    {
        return m_assets;
    }
}
