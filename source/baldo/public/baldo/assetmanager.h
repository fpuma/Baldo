#pragma once

#include <baldo/assetid.h>

namespace puma::baldo
{
    class AssetManager
    {
    public:

        AssetId registerResource() {}

        void requestResource(AssetId _id) {}
        void releaseResource(AssetId _id) {}

        void forceLoad(AssetId _id) {}
        void forceUnload(AssetId _id) {}
    private:


    };
}

