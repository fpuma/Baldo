#pragma once

#include <memory>
#include <typeindex>

namespace puma::baldo
{
    class IAsset
    {
    public:
        IAsset() = default;
        virtual ~IAsset() {}
    };

    template<class AssetType, class... Args>
    std::shared_ptr<AssetType> loadAsset(Args... args);
}

