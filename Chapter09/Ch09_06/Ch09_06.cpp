//------------------------------------------------
//               Ch09_06.cpp
//------------------------------------------------

#include "stdafx.h"
#include <cmath>
#include "Ch09_06.h"
#include "Matrix.h"

using namespace std;

bool Avx2Mat4x4InvF64Cpp(Matrix<double>& m_inv, const Matrix<double>& m, double epsilon, bool* is_singular)
{
    // The intermediate matrices below are declared static for benchmarking purposes.
    static const size_t nrows = 4;
    static const size_t ncols = 4;
    static Matrix<double> m2(nrows, ncols);
    static Matrix<double> m3(nrows, ncols);
    static Matrix<double> m4(nrows, ncols);
    static Matrix<double> I(nrows, ncols, true);
    static Matrix<double> tempA(nrows, ncols);
    static Matrix<double> tempB(nrows, ncols);
    static Matrix<double> tempC(nrows, ncols);
    static Matrix<double> tempD(nrows, ncols);

    Matrix<double>::Mul(m2, m, m);
    Matrix<double>::Mul(m3, m2, m);
    Matrix<double>::Mul(m4, m3, m);

    double t1 = m.Trace();
    double t2 = m2.Trace();
    double t3 = m3.Trace();
    double t4 = m4.Trace();

    double c1 = -t1;
    double c2 = -1.0 / 2.0 * (c1 * t1 + t2);
    double c3 = -1.0 / 3.0 * (c2 * t1 + c1 * t2 + t3);
    double c4 = -1.0 / 4.0 * (c3 * t1 + c2 * t2 + c1 * t3 + t4);

    // Make sure matrix is not singular
    *is_singular = (fabs(c4) < epsilon);

    if (*is_singular)
        return false;

    // Calculate = -1.0 / c4 * (m3 + c1 * m2 + c2 * m + c3 * I)
    Matrix<double>::MulScalar(tempA, I, c3);
    Matrix<double>::MulScalar(tempB, m, c2);
    Matrix<double>::MulScalar(tempC, m2, c1);
    Matrix<double>::Add(tempD, tempA, tempB);
    Matrix<double>::Add(tempD, tempD, tempC);
    Matrix<double>::Add(tempD, tempD, m3);
    Matrix<double>::MulScalar(m_inv, tempD, -1.0 / c4);

    return true;
}

void Avx2Mat4x4InvF64(const Matrix<double>& m, const char* msg)
{
    cout << '\n' << msg << " - Test Matrix\n";
    cout << m << '\n';

    const double epsilon = 1.0e-9;
    const size_t nrows = m.GetNumRows();
    const size_t ncols = m.GetNumCols();
    Matrix<double> m_inv_a(nrows, ncols);
    Matrix<double> m_ver_a(nrows, ncols);
    Matrix<double> m_inv_b(nrows, ncols);
    Matrix<double> m_ver_b(nrows, ncols);

    for (int i = 0; i <= 1; i++)
    {
        string fn;
        const size_t nrows = m.GetNumRows();
        const size_t ncols = m.GetNumCols();
        Matrix<double> m_inv(nrows, ncols);
        Matrix<double> m_ver(nrows, ncols);
        bool rc, is_singular;

        if (i == 0)
        {
            fn = "Avx2Mat4x4InvF64Cpp";
            rc = Avx2Mat4x4InvF64Cpp(m_inv, m, epsilon, &is_singular);

            if (rc)
                Matrix<double>::Mul(m_ver, m_inv, m);
        }
        else
        {
            fn = "Avx2Mat4x4InvF64_";
            rc = Avx2Mat4x4InvF64_(m_inv.Data(), m.Data(), epsilon, &is_singular);

            if (rc)
                Avx2Mat4x4MulF64_(m_ver.Data(), m_inv.Data(), m.Data());
        }

        if (rc)
        {
            cout << msg << " - " << fn << " - Inverse Matrix\n";
            cout << m_inv << '\n';

            // Round to zero used for display purposes, can be removed.
            cout << msg << " - " << fn << " - Verify Matrix\n";
            m_ver.RoundToZero(epsilon);
            cout << m_ver << '\n';
        }
        else
        {
            if (is_singular)
                cout << msg << " - " << fn << " - Singular Matrix\n";
            else
                cout << msg << " - " << fn << " - Unexpected error occurred\n";
        }
    }
}

int main()
{
    cout << "\nResults for Avx2Mat4x4InvF64\n";

    // Test Matrix #1 - Non-Singular
    Matrix<double> m1(4, 4);
    const double m1_row0[] = { 2, 7, 3, 4 };
    const double m1_row1[] = { 5, 9, 6, 4.75 };
    const double m1_row2[] = { 6.5, 3, 4, 10 };
    const double m1_row3[] = { 7, 5.25, 8.125, 6 };
    m1.SetRow(0, m1_row0);
    m1.SetRow(1, m1_row1);
    m1.SetRow(2, m1_row2);
    m1.SetRow(3, m1_row3);

    // Test Matrix #2 - Non-Singular
    Matrix<double> m2(4, 4);
    const double m2_row0[] = { 0.5, 12, 17.25, 4 };
    const double m2_row1[] = { 5, 2, 6.75, 8 };
    const double m2_row2[] = { 13.125, 1, 3, 9.75 };
    const double m2_row3[] = { 16, 1.625, 7, 0.25 };
    m2.SetRow(0, m2_row0);
    m2.SetRow(1, m2_row1);
    m2.SetRow(2, m2_row2);
    m2.SetRow(3, m2_row3);

    // Test Matrix #3 - Singular
    Matrix<double> m3(4, 4);
    const double m3_row0[] = { 2, 0, 0, 1 };
    const double m3_row1[] = { 0, 4, 5, 0 };
    const double m3_row2[] = { 0, 0, 0, 7 };
    const double m3_row3[] = { 0, 0, 0, 6 };
    m3.SetRow(0, m3_row0);
    m3.SetRow(1, m3_row1);
    m3.SetRow(2, m3_row2);
    m3.SetRow(3, m3_row3);

    Avx2Mat4x4InvF64(m1, "Test #1");
    Avx2Mat4x4InvF64(m2, "Test #2");
    Avx2Mat4x4InvF64(m3, "Test #3");

    Avx2Mat4x4InvF64_BM(m1);
    return 0;
}
