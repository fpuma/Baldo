#include <gtest/gtest.h>
#include "testasset.h"

#include <baldo/assetmanager.h>

using namespace puma;

TEST(AssetManager, Overall)
{
    baldo::AssetManager assetManager;

    baldo::AssetId invalidId;
    
#ifdef _DEBUG
    EXPECT_DEATH(assetManager.requestResource<TestAsset0>(invalidId), "typePos < m_assets.size");
#endif

    baldo::AssetId id0 = assetManager.registerResource<TestAsset0>(8);
    baldo::AssetId id1 = assetManager.registerResource<TestAsset0>(88);
    baldo::AssetId id2 = assetManager.registerResource<TestAsset1>(std::string("TA1a"));
    baldo::AssetId id3 = assetManager.registerResource<TestAsset1>(std::string("TA1b"));

#ifdef _DEBUG
    EXPECT_DEATH(assetManager.requestResource<TestAsset0>(id2), "requestedTypeIndex == typeEntry.typeIndex");
#endif

    auto asset0 = assetManager.requestResource<TestAsset0>(id0);
    auto asset1 = assetManager.requestResource<TestAsset0>(id1);
    auto asset2 = assetManager.requestResource<TestAsset1>(id2);
    auto asset3 = assetManager.requestResource<TestAsset1>(id3);

    EXPECT_EQ(asset0->number, 8);
    EXPECT_EQ(asset1->number, 88);
    EXPECT_TRUE(asset2->name == std::string("TA1a"));
    EXPECT_TRUE(asset3->name == std::string("TA1b"));

    assetManager.runGarbageCollector();
}
