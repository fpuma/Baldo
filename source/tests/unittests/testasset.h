#pragma once

#include <baldo/iasset.h>

namespace puma::baldo
{
    class TestAsset : public IAsset
    {
    public:
        TestAsset() {}
        virtual ~TestAsset() {}

        int number = 0;
    };

    class TestAsset2 : public IAsset
    {
    public:
        TestAsset2() {}
        virtual ~TestAsset2() {}

        int number = 0;
    };

    template<>
    std::shared_ptr<TestAsset> loadAsset<TestAsset, int>(int num)
    {
        std::shared_ptr<TestAsset> result = std::make_shared<TestAsset>();
        result->number = num;
        return result;
    }

    template<>
    std::shared_ptr<TestAsset2> loadAsset<TestAsset2, int>(int num)
    {
        std::shared_ptr<TestAsset2> result = std::make_shared<TestAsset2>();
        result->number = num;
        return result;
    }
}