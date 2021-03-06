//------------------------------------------------
//               Ch09_08.cpp
//------------------------------------------------

#include "stdafx.h"
#include <string>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <array>
#include <stdexcept>

using namespace std;

extern "C" void Avx2Gather8xF32_I32_(float* y, const float* x,
    const int32_t* indices, const int32_t* masks);
extern "C" void Avx2Gather8xF32_I64_(float* y, const float* x,
    const int64_t* indices, const int32_t* masks);
extern "C" void Avx2Gather8xF64_I32_(double* y, const double* x,
    const int32_t* indices, const int64_t* masks);
extern "C" void Avx2Gather8xF64_I64_(double* y, const double* x,
    const int64_t* indices, const int64_t* masks);

template <typename T, typename I, typename M, size_t N>
    void Print(const string& msg, const array<T, N>& y, const array<I, N>& indices,
    const array<M, N>& merge)
{
    if (y.size() != indices.size() || y.size() != merge.size())
        throw runtime_error("Non-conforming arrays - Print");

    cout << '\n' << msg << '\n';

    for (size_t i = 0; i < y.size(); i++)
    {
        string merge_s = (merge[i] == 1) ? "Yes" : "No";

        cout << "i: " << setw(2) << i << "   ";
        cout << "y: " << setw(10) << y[i] << "   ";
        cout << "index: " << setw(4) << indices[i] << "   ";
        cout << "merge: " << setw(4) << merge_s << '\n';
    }
}

void Avx2Gather8xF32_I32()
{
    array<float, 20> x;

    for (size_t i = 0; i < x.size(); i++)
        x[i] = (float)(i * 10);

    array<float, 8> y { -1, -1, -1, -1, -1, -1, -1, -1 };
    array<int32_t, 8> indices { 2, 1, 6, 5, 4, 13, 11, 9 };
    array<int32_t, 8> merge { 1, 1, 0, 1, 1, 0, 1, 1 };

    cout << fixed << setprecision(1);
    cout << "\nResults for Avx2Gather8xF32_I32\n";

    Print("Values before", y, indices, merge);
    Avx2Gather8xF32_I32_(y.data(), x.data(), indices.data(), merge.data());
    Print("Values after", y, indices, merge);
}

void Avx2Gather8xF32_I64()
{
    array<float, 20> x;

    for (size_t i = 0; i < x.size(); i++)
        x[i] = (float)(i * 10);

    array<float, 8> y { -1, -1, -1, -1, -1, -1, -1, -1 };
    array<int64_t, 8> indices { 19, 1, 0, 5, 4, 3, 11, 11 };
    array<int32_t, 8> merge { 1, 1, 1, 1, 0, 0, 1, 1 };

    cout << fixed << setprecision(1);
    cout << "\nResults for Avx2Gather8xF32_I64\n";

    Print("Values before", y, indices, merge);
    Avx2Gather8xF32_I64_(y.data(), x.data(), indices.data(), merge.data());
    Print("Values after", y, indices, merge);
}

void Avx2Gather8xF64_I32()
{
    array<double, 20> x;

    for (size_t i = 0; i < x.size(); i++)
        x[i] = (double)(i * 10);

    array<double, 8> y { -1, -1, -1, -1, -1, -1, -1, -1 };
    array<int32_t, 8> indices { 12, 11, 6, 15, 4, 13, 18, 3 };
    array<int64_t, 8> merge { 1, 1, 0, 1, 1, 0, 1, 0 };

    cout << fixed << setprecision(1);
    cout << "\nResults for Avx2Gather8xF64_I32\n";

    Print("Values before", y, indices, merge);
    Avx2Gather8xF64_I32_(y.data(), x.data(), indices.data(), merge.data());
    Print("Values after", y, indices, merge);
}

void Avx2Gather8xF64_I64()
{
    array<double, 20> x;

    for (size_t i = 0; i < x.size(); i++)
        x[i] = (double)(i * 10);

    array<double, 8> y { -1, -1, -1, -1, -1, -1, -1, -1 };
    array<int64_t, 8> indices { 11, 17, 1, 6, 14, 13, 8, 8 };
    array<int64_t, 8> merge { 1, 0, 1, 1, 1, 0, 1, 1 };

    cout << fixed << setprecision(1);
    cout << "\nResults for Avx2Gather8xF64_I64\n";

    Print("Values before", y, indices, merge);
    Avx2Gather8xF64_I64_(y.data(), x.data(), indices.data(), merge.data());
    Print("Values after", y, indices, merge);
}

int main()
{
    Avx2Gather8xF32_I32();
    Avx2Gather8xF32_I64();
    Avx2Gather8xF64_I32();
    Avx2Gather8xF64_I64();
    return 0;
}
