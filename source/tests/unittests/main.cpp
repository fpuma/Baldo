#include <baldo/assetmanager.h>
#include "testasset.h"
#include <bitset>
#include <iostream>

using namespace puma;

int main()
{
    baldo::AssetManager assetManager;

    baldo::AssetId id0 = assetManager.registerResource<baldo::TestAsset>(88);
    baldo::AssetId id1 = assetManager.registerResource<baldo::TestAsset>(104356);
    baldo::AssetId id2 = assetManager.registerResource<baldo::TestAsset2>(333);
    baldo::AssetId id3 = assetManager.registerResource<baldo::TestAsset2>(444);

    //std::bitset<64>(id0.value())

    std::cout << std::hex << id0.value() << std::endl;
    std::cout << std::hex << id1.value() << std::endl;
    std::cout << std::hex << id2.value() << std::endl;
    std::cout << std::hex << id3.value() << std::endl;

    return 0;
}
