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

        AssetManager() = default;
        ~AssetManager() = default;

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
            BoundLoaderCallback assetLoader = [=]() -> std::shared_ptr<IAsset>
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

            return buildId(typePos, assetPos);
        }

        template<class AssetType>
        std::shared_ptr<const AssetType> requestResource(AssetId _id) 
        {
            u64 typePos = kMaxU64;
            u64 assetPos = kMaxU64;
            readId(_id, typePos, assetPos);

            assert(typePos < m_assets.size()); //AssetId is invalid
            
            if (typePos < m_assets.size())
            {
                TypeEntry& typeEntry = m_assets[typePos];
                std::type_index requestedTypeIndex = std::type_index(typeid(AssetType));

                assert(requestedTypeIndex == typeEntry.typeIndex); // Requested type does not match the ID type

                if (requestedTypeIndex == typeEntry.typeIndex)
                {
                    assert(assetPos < typeEntry.assets.size()); //AssetId is invalid

                    if (assetPos < typeEntry.assets.size())
                    {
                        AssetEntry& assetEntry = typeEntry.assets[assetPos];
                    
                        if (nullptr != assetEntry.asset) return std::static_pointer_cast<const AssetType>(assetEntry.asset);
                        else
                        {
                            assetEntry.asset = assetEntry.assetLoader();
                            assert(nullptr != assetEntry.asset);
                            return std::static_pointer_cast<const AssetType>(assetEntry.asset);
                        }
                    }
                }
            }
            return nullptr;
        }

        void runGarbageCollector()
        {
            for (TypeEntry& typeEntry : m_assets)
            {
                for (AssetEntry& assetEntry : typeEntry.assets)
                {
                    if (nullptr == assetEntry.asset) continue;

                    long useCount = assetEntry.asset.use_count();
                    if (useCount == 1)
                    {
                        assetEntry.asset.reset();
                    }
                }
            }
        }

    private:
        
        AssetId buildId(u64 _typePos, u64 _assetPos)
        {
            u64 result = _typePos;
            result = result << kAssetCountBitSize;
            result += _assetPos;

            return AssetId(result);
        }

        void readId(AssetId _id, u64& _typePos, u64& _assetPos)
        {
            u64 mask = kMaxU64;
            mask = mask >> (64 - kAssetCountBitSize);
            _assetPos = _id.value() & mask;
            _typePos = _id.value() >> kAssetCountBitSize;
        }

        using BoundLoaderCallback = std::function<std::shared_ptr<IAsset>()>;

        struct AssetEntry
        {
            BoundLoaderCallback assetLoader;
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

