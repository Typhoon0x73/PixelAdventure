#ifndef SIP_ASSET_PACKAGE_H_
#define SIP_ASSET_PACKAGE_H_
#pragma once

// INCLUDE
#include <Siv3D.hpp>

namespace sip
{
    struct PackageValue
    {
        AssetName key;

        FilePath path;
    };
    
    class AssetPackage
    {
    public:
        using AssetType = String;
        using AssetTable = HashTable<AssetType, Array<PackageValue>>;
        
        AssetPackage();
        
        ~AssetPackage();

        bool Load(FilePathView path);

        StringView getPackageName() const;

        const AssetTable& getAssetTable() const;

    private:

        String m_name;

        AssetTable m_assets;
    };
}

#endif //! SIP_ASSET_PACKAGE_H_