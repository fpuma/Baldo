#pragma once

#include <utils/genericid.h>
#include <utils/numerictypes.h>


namespace puma::baldo
{
    class AssetId;
}

DECLARE_GENERIC_ID(puma::baldo::AssetId, puma::u64, puma::kMaxU64);