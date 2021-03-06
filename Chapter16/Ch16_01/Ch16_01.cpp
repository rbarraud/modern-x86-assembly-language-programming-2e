//------------------------------------------------
//               Ch16_01.cpp
//------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "CpuidInfo.h"

using namespace std;

static void DisplayCacheInfo(const CpuidInfo& ci);
static void DisplayFeatureFlags(const CpuidInfo& ci);

int main()
{
    CpuidInfo ci;

    ci.LoadInfo();

    cout << ci.GetVendorId() << '\n';
    cout << ci.GetProcessorBrand() << '\n';

    DisplayCacheInfo(ci);
    DisplayFeatureFlags(ci);
    return 0;
}

static void DisplayCacheInfo(const CpuidInfo& ci)
{
    const vector<CpuidInfo::CacheInfo>& cache_info = ci.GetCacheInfo();

    for (const CpuidInfo::CacheInfo& x : cache_info)
    {
        uint32_t cache_size = x.GetSize();
        string cache_size_str;

        if (cache_size < 1024 * 1024)
        {
            cache_size /= 1024;
            cache_size_str = "KB";
        }
        else
        {
            cache_size /= 1024 * 1024;
            cache_size_str = "MB";
        }

        cout << "Cache L" << x.GetLevel() << ": ";
        cout << cache_size << cache_size_str << ' ';
        cout << x.GetTypeString() << '\n';
    }
}

static void DisplayFeatureFlags(const CpuidInfo& ci)
{
    const char nl = '\n';

    cout << "----- CPUID Feature Flags -----" << nl;
    cout << "ADX:         " << ci.GetFF(CpuidInfo::FF::ADX) << nl;
    cout << "AVX:         " << ci.GetFF(CpuidInfo::FF::AVX) << nl;
    cout << "AVX2:        " << ci.GetFF(CpuidInfo::FF::AVX2) << nl;
    cout << "AVX512F:     " << ci.GetFF(CpuidInfo::FF::AVX512F) << nl;
    cout << "AVX512BW:    " << ci.GetFF(CpuidInfo::FF::AVX512BW) << nl;
    cout << "AVX512CD:    " << ci.GetFF(CpuidInfo::FF::AVX512CD) << nl;
    cout << "AVX512DQ:    " << ci.GetFF(CpuidInfo::FF::AVX512DQ) << nl;
    cout << "AVX512ER:    " << ci.GetFF(CpuidInfo::FF::AVX512ER) << nl;
    cout << "AVX512PF:    " << ci.GetFF(CpuidInfo::FF::AVX512PF) << nl;
    cout << "AVX512VL:    " << ci.GetFF(CpuidInfo::FF::AVX512VL) << nl;
    cout << "AVX512_IFMA: " << ci.GetFF(CpuidInfo::FF::AVX512_IFMA) << nl;
    cout << "AVX512_VBMI: " << ci.GetFF(CpuidInfo::FF::AVX512_VBMI) << nl;
    cout << "BMI1:        " << ci.GetFF(CpuidInfo::FF::BMI1) << nl;
    cout << "BMI2:        " << ci.GetFF(CpuidInfo::FF::BMI2) << nl;
    cout << "F16C:        " << ci.GetFF(CpuidInfo::FF::F16C) << nl;
    cout << "FMA:         " << ci.GetFF(CpuidInfo::FF::FMA) << nl;
    cout << "LZCNT:       " << ci.GetFF(CpuidInfo::FF::LZCNT) << nl;
    cout << "POPCNT:      " << ci.GetFF(CpuidInfo::FF::POPCNT) << nl;
}
