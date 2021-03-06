//------------------------------------------------
//               Ch07_03.cpp
//------------------------------------------------

#include "stdafx.h"
#include <iostream>
#include "XmmVal.h"

using namespace std;

extern "C" void AvxPackedMulI16_(XmmVal c[2], const XmmVal& a, const XmmVal& b);
extern "C" void AvxPackedMulI32A_(XmmVal c[2], const XmmVal& a, const XmmVal& b);
extern "C" void AvxPackedMulI32B_(XmmVal* c, const XmmVal& a, const XmmVal& b);

void AvxPackedMulI16(void)
{
    alignas(16) XmmVal a;
    alignas(16) XmmVal b;
    alignas(16) XmmVal c[2];

    a.m_I16[0] = 10;        b.m_I16[0] = -5;
    a.m_I16[1] = 3000;      b.m_I16[1] = 100;
    a.m_I16[2] = -2000;     b.m_I16[2] = -9000;
    a.m_I16[3] = 42;        b.m_I16[3] = 1000;
    a.m_I16[4] = -5000;     b.m_I16[4] = 25000;
    a.m_I16[5] = 8;         b.m_I16[5] = 16384;
    a.m_I16[6] = 10000;     b.m_I16[6] = 3500;
    a.m_I16[7] = -60;       b.m_I16[7] = 6000;

    AvxPackedMulI16_(c, a, b);

    cout << "\nResults for AvxPackedMulI16\n";

    for (size_t i = 0; i < 8; i++)
    {
        cout << "a[" << i << "]: " << setw(8) << a.m_I16[i] << "  ";
        cout << "b[" << i << "]: " << setw(8) << b.m_I16[i] << "  ";

        if (i < 4)
        {
            cout << "c[0][" << i << "]: ";
            cout << setw(12) << c[0].m_I32[i] << '\n';
        }
        else
        {
            cout << "c[1][" << i - 4 << "]: ";
            cout << setw(12) << c[1].m_I32[i - 4] << '\n';
        }
    }
}

void AvxPackedMulI32A(void)
{
    alignas(16) XmmVal a;
    alignas(16) XmmVal b;
    alignas(16) XmmVal c[2];

    a.m_I32[0] = 10;        b.m_I32[0] = -500;
    a.m_I32[1] = 3000;      b.m_I32[1] = 100;
    a.m_I32[2] = -40000;    b.m_I32[2] = -120000;
    a.m_I32[3] = 4200;      b.m_I32[3] = 1000;

    AvxPackedMulI32A_(c, a, b);

    cout << "\nResults for AvxPackedMulI32A\n";

    for (size_t i = 0; i < 4; i++)
    {
        cout << "a[" << i << "]: " << setw(10) << a.m_I32[i] << "  ";
        cout << "b[" << i << "]: " << setw(10) << b.m_I32[i] << "  ";

        if (i < 2)
        {
            cout << "c[0][" << i << "]: ";
            cout << setw(14) << c[0].m_I64[i] << '\n';
        }
        else
        {
            cout << "c[1][" << i - 2 << "]: ";
            cout << setw(14) << c[1].m_I64[i - 2] << '\n';
        }
    }
}

void AvxPackedMulI32B(void)
{
    alignas(16) XmmVal a;
    alignas(16) XmmVal b;
    alignas(16) XmmVal c;

    a.m_I32[0] = 10;        b.m_I32[0] = -500;
    a.m_I32[1] = 3000;      b.m_I32[1] = 100;
    a.m_I32[2] = -2000;     b.m_I32[2] = -12000;
    a.m_I32[3] = 4200;      b.m_I32[3] = 1000;

    AvxPackedMulI32B_(&c, a, b);

    cout << "\nResults for AvxPackedMulI32B\n";

    for (size_t i = 0; i < 4; i++)
    {
        cout << "a[" << i << "]: " << setw(10) << a.m_I32[i] << "  ";
        cout << "b[" << i << "]: " << setw(10) << b.m_I32[i] << "  ";
        cout << "c[" << i << "]: " << setw(10) << c.m_I32[i] << '\n';
    }
}

int main()
{
    string sep(75, '-');

    AvxPackedMulI16();
    cout << '\n' << sep << '\n';
    AvxPackedMulI32A();
    cout << '\n' << sep << '\n';
    AvxPackedMulI32B();
    return 0;
}
