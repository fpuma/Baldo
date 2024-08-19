#pragma once

#include <baldo/assetid.h>
#include <baldo/iasset.h>
#include <utils/noncopyable.h>
#include <utils/containers/mappedrealizationcontainer.h>
#include <utils/numerictypes.h>

#include <typeindex>

namespace puma::baldo
{

    constexpr u8 kAssetCountBitSize = 32;

    class AssetManager final : public NonCopyable
    {
    public:

        AssetManager();
        virtual ~AssetManager();

        template<class AssetType, class... Args>
        AssetId registerResource(Args... _args) 
        {
            std::type_index typeIndex(typeid(AssetType));
            auto itFoundAssetType = std::find_if(m_assets.begin(), m_assets.end(), [&typeIndex](const TypeEntry& element) 
                {
                    return element.typeIndex == typeIndex;
                });
            
            u64 typePos = kMaxU64;
            u64 assetPos = kMaxU64;
            BoundType assetLoader = [=]() -> std::shared_ptr<IAsset>
                {
                    return std::static_pointer_cast<IAsset>(loadAsset<AssetType, Args...>(_args...));
                };

            if (itFoundAssetType == m_assets.end())
            {
                typePos = m_assets.size();
                m_assets.push_back({ typeIndex, {} });
                itFoundAssetType = m_assets.end() - 1;
            }
            else
            {
                typePos = std::distance(m_assets.begin(), itFoundAssetType);
            }

            assetPos = itFoundAssetType->assets.size();
            itFoundAssetType->assets.push_back({ assetLoader , nullptr });

            u64 tempId = typePos;
            tempId = tempId << kAssetCountBitSize;
            tempId += assetPos;
            
            return AssetId(tempId);
        }

        template<class AssetType>
        std::shared_ptr<AssetType> requestResource(AssetId _id) 
        {
            return nullptr;
        }


    private:
        
        using BoundType = std::function<std::shared_ptr<IAsset>()>;

        struct AssetEntry
        {
            BoundType assetLoader;
            std::shared_ptr<IAsset> asset;
        };

        struct TypeEntry
        {
            std::type_index typeIndex;
            std::vector<AssetEntry> assets;

        };

        std::vector<TypeEntry> m_assets;
    };
}

