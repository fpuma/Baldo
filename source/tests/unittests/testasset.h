#pragma once

#include <baldo/iasset.h>
#include <string>

using namespace puma;

class TestAsset0 : public baldo::IAsset
{
public:
    TestAsset0() {}
    virtual ~TestAsset0() {}

    int number = 0;
};

template<>
std::shared_ptr<TestAsset0> baldo::loadAsset<TestAsset0, int>(int num)
{
    std::shared_ptr<TestAsset0> result = std::make_shared<TestAsset0>();
    result->number = num;
    return result;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class TestAsset1 : public baldo::IAsset
{
public:
    TestAsset1() {}
    virtual ~TestAsset1() {}

    std::string name = "";
};

template<>
std::shared_ptr<TestAsset1> baldo::loadAsset<TestAsset1, std::string>(std::string name)
{
    std::shared_ptr<TestAsset1> result = std::make_shared<TestAsset1>();
    result->name = name;
    return result;
}
