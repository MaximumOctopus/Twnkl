//
// Twnkl 1.0
//
// (c) Paul Alan Freshney 2023
//
// paul@freshney.org
// 
// https://github.com/MaximumOctopus/Twnkl
// 
// 

// https://www.codespeedy.com/find-determinant-of-a-matrix-in-cpp/

#include <math.h>

#include "Constants.h"
#include "Matrix4.h"

// returns identity matrix
Matrix4::Matrix4() noexcept
{

}


// rotation x = 0, y = 1, z = 2
Matrix4::Matrix4(int axis, double r) noexcept
{
    switch (axis)
    {
    case 0:                     // x
        Data[1][1] = cos(r);
        Data[1][2] = -sin(r);
        Data[2][1] = sin(r);
        Data[2][2] = cos(r);
        break;
    case 1:                     // y
        Data[0][0] = cos(r);
        Data[0][2] = sin(r);
        Data[2][0] = -sin(r);
        Data[2][2] = cos(r);
        break;
    case 2:                     // z
        Data[0][0] = cos(r);
        Data[0][1] = -sin(r);
        Data[1][0] = sin(r);
        Data[1][1] = cos(r);
        break;
    }
}


// scaling matrix if t = 0, translation if t = 1
Matrix4::Matrix4(int t, double x, double y, double z) noexcept
{
    if (t == 0)
    {
        Data[0][0] = x;
        Data[1][1] = y;
        Data[2][2] = z;
    }
    else
    {
        Data[0][3] = x;
        Data[1][3] = y;
        Data[2][3] = z;
    }
	
}


// shearing matrix
Matrix4::Matrix4(double xy, double xz, double yx, double yz, double zx, double zy) noexcept
{
    Data[0][1] = xy;
    Data[0][2] = xz;
    Data[1][0] = yx;
    Data[1][2] = yz;
    Data[2][0] = zx;
    Data[2][1] = zy;
}


Matrix4::Matrix4(double aa, double ab, double ac, double ad, 
    double ba, double bb, double bc, double bd, 
    double ca, double cb, double cc, double cd, 
    double da, double db, double dc, double dd) noexcept
{
    Data[0][0] = aa;
    Data[0][1] = ab;
    Data[0][2] = ac;
    Data[0][3] = ad;

    Data[1][0] = ba;
    Data[1][1] = bb;
    Data[1][2] = bc;
    Data[1][3] = bd;

    Data[2][0] = ca;
    Data[2][1] = cb;
    Data[2][2] = cc;
    Data[2][3] = cd;

    Data[3][0] = da;
    Data[3][1] = db;
    Data[3][2] = dc;
    Data[3][3] = dd;
}


double Matrix4::Determinant()
{
    return
        Data[0][3] * Data[1][2] * Data[2][1] * Data[3][0] - Data[0][2] * Data[1][3] * Data[2][1] * Data[3][0] -
        Data[0][3] * Data[1][1] * Data[2][2] * Data[3][0] + Data[0][1] * Data[1][3] * Data[2][2] * Data[3][0] +
        Data[0][2] * Data[1][1] * Data[2][3] * Data[3][0] - Data[0][1] * Data[1][2] * Data[2][3] * Data[3][0] -
        Data[0][3] * Data[1][2] * Data[2][0] * Data[3][1] + Data[0][2] * Data[1][3] * Data[2][0] * Data[3][1] +
        Data[0][3] * Data[1][0] * Data[2][2] * Data[3][1] - Data[0][0] * Data[1][3] * Data[2][2] * Data[3][1] -
        Data[0][2] * Data[1][0] * Data[2][3] * Data[3][1] + Data[0][0] * Data[1][2] * Data[2][3] * Data[3][1] +
        Data[0][3] * Data[1][1] * Data[2][0] * Data[3][2] - Data[0][1] * Data[1][3] * Data[2][0] * Data[3][2] -
        Data[0][3] * Data[1][0] * Data[2][1] * Data[3][2] + Data[0][0] * Data[1][3] * Data[2][1] * Data[3][2] +
        Data[0][1] * Data[1][0] * Data[2][3] * Data[3][2] - Data[0][0] * Data[1][1] * Data[2][3] * Data[3][2] -
        Data[0][2] * Data[1][1] * Data[2][0] * Data[3][3] + Data[0][1] * Data[1][2] * Data[2][0] * Data[3][3] +
        Data[0][2] * Data[1][0] * Data[2][1] * Data[3][3] - Data[0][0] * Data[1][2] * Data[2][1] * Data[3][3] -
        Data[0][1] * Data[1][0] * Data[2][2] * Data[3][3] + Data[0][0] * Data[1][1] * Data[2][2] * Data[3][3];
}


void Matrix4::Invert()
{
    //
    // Inversion by Cramer's rule.  Code taken from an Intel publication
    //

    double Result[4][4];
    double tmp[12]; /* temp array for pairs */
    double src[16]; /* array of transpose source matrix */
    double det; /* determinant */
    /* transpose matrix */
    for (int i = 0; i < 4; i++)
    {
        src[i + 0] = Data[i][0];
        src[i + 4] = Data[i][1];
        src[i + 8] = Data[i][2];
        src[i + 12] = Data[i][3];
    }
    /* calculate pairs for first 8 elements (cofactors) */
    tmp[0] = src[10] * src[15];
    tmp[1] = src[11] * src[14];
    tmp[2] = src[9] * src[15];
    tmp[3] = src[11] * src[13];
    tmp[4] = src[9] * src[14];
    tmp[5] = src[10] * src[13];
    tmp[6] = src[8] * src[15];
    tmp[7] = src[11] * src[12];
    tmp[8] = src[8] * src[14];
    tmp[9] = src[10] * src[12];
    tmp[10] = src[8] * src[13];
    tmp[11] = src[9] * src[12];
    /* calculate first 8 elements (cofactors) */
    Result[0][0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
    Result[0][0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
    Result[0][1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
    Result[0][1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
    Result[0][2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
    Result[0][2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
    Result[0][3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
    Result[0][3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
    Result[1][0] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
    Result[1][0] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
    Result[1][1] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
    Result[1][1] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
    Result[1][2] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
    Result[1][2] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
    Result[1][3] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
    Result[1][3] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
    /* calculate pairs for second 8 elements (cofactors) */
    tmp[0] = src[2] * src[7];
    tmp[1] = src[3] * src[6];
    tmp[2] = src[1] * src[7];
    tmp[3] = src[3] * src[5];
    tmp[4] = src[1] * src[6];
    tmp[5] = src[2] * src[5];

    tmp[6] = src[0] * src[7];
    tmp[7] = src[3] * src[4];
    tmp[8] = src[0] * src[6];
    tmp[9] = src[2] * src[4];
    tmp[10] = src[0] * src[5];
    tmp[11] = src[1] * src[4];
    /* calculate second 8 elements (cofactors) */
    Result[2][0] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
    Result[2][0] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
    Result[2][1] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
    Result[2][1] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
    Result[2][2] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
    Result[2][2] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
    Result[2][3] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
    Result[2][3] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
    Result[3][0] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
    Result[3][0] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
    Result[3][1] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
    Result[3][1] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
    Result[3][2] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
    Result[3][2] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
    Result[3][3] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
    Result[3][3] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
    /* calculate determinant */
    det = src[0] * Result[0][0] + src[1] * Result[0][1] + src[2] * Result[0][2] + src[3] * Result[0][3];
    /* calculate matrix inverse */
    det = 1.0 / det;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Data[i][j] = Result[i][j] * det;
        }
    }
}


Matrix4 Matrix4::Inverse()
{
    //
// Inversion by Cramer's rule.  Code taken from an Intel publication
//
    double Result[4][4];
    double tmp[12]; /* temp array for pairs */
    double src[16]; /* array of transpose source matrix */
    double det; /* determinant */
    /* transpose matrix */
    for (int i = 0; i < 4; i++)
    {
        src[i + 0] = Data[i][0];
        src[i + 4] = Data[i][1];
        src[i + 8] = Data[i][2];
        src[i + 12] = Data[i][3];
    }
    /* calculate pairs for first 8 elements (cofactors) */
    tmp[0] = src[10] * src[15];
    tmp[1] = src[11] * src[14];
    tmp[2] = src[9] * src[15];
    tmp[3] = src[11] * src[13];
    tmp[4] = src[9] * src[14];
    tmp[5] = src[10] * src[13];
    tmp[6] = src[8] * src[15];
    tmp[7] = src[11] * src[12];
    tmp[8] = src[8] * src[14];
    tmp[9] = src[10] * src[12];
    tmp[10] = src[8] * src[13];
    tmp[11] = src[9] * src[12];
    /* calculate first 8 elements (cofactors) */
    Result[0][0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
    Result[0][0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
    Result[0][1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
    Result[0][1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
    Result[0][2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
    Result[0][2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
    Result[0][3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
    Result[0][3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
    Result[1][0] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
    Result[1][0] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
    Result[1][1] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
    Result[1][1] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
    Result[1][2] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
    Result[1][2] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
    Result[1][3] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
    Result[1][3] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
    /* calculate pairs for second 8 elements (cofactors) */
    tmp[0] = src[2] * src[7];
    tmp[1] = src[3] * src[6];
    tmp[2] = src[1] * src[7];
    tmp[3] = src[3] * src[5];
    tmp[4] = src[1] * src[6];
    tmp[5] = src[2] * src[5];

    tmp[6] = src[0] * src[7];
    tmp[7] = src[3] * src[4];
    tmp[8] = src[0] * src[6];
    tmp[9] = src[2] * src[4];
    tmp[10] = src[0] * src[5];
    tmp[11] = src[1] * src[4];
    /* calculate second 8 elements (cofactors) */
    Result[2][0] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
    Result[2][0] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
    Result[2][1] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
    Result[2][1] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
    Result[2][2] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
    Result[2][2] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
    Result[2][3] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
    Result[2][3] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
    Result[3][0] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
    Result[3][0] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
    Result[3][1] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
    Result[3][1] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
    Result[3][2] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
    Result[3][2] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
    Result[3][3] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
    Result[3][3] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
    /* calculate determinant */
    det = src[0] * Result[0][0] + src[1] * Result[0][1] + src[2] * Result[0][2] + src[3] * Result[0][3];
    /* calculate matrix inverse */
    det = 1.0 / det;

    return Matrix4(Result[0][0] * det, Result[0][1] * det, Result[0][2] * det, Result[0][3] * det,
                   Result[1][0] * det, Result[1][1] * det, Result[1][2] * det, Result[1][3] * det,
                   Result[2][0] * det, Result[2][1] * det, Result[2][2] * det, Result[2][3] * det,
                   Result[3][0] * det, Result[3][1] * det, Result[3][2] * det, Result[3][3] * det);
}


Matrix4 Matrix4::Transpose()
{
    Matrix4 m = Matrix4();

    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            m.Data[y][x] = Data[x][y];
        }
    }

    return m;
}


Quaternion Matrix4::MultQ(Quaternion& q)
{
    double i[4] = { 0, 0, 0, 0 };

    for (int y = 0; y < 4; y++)
    {
        i[y] += Data[y][0] * q.x +
            Data[y][1] * q.y +
            Data[y][2] * q.z +
            Data[y][3] * q.w;
    }

    return Quaternion(i[0], i[1], i[2], i[3]);
}


Matrix4 Matrix4::MultM(Matrix4& a)
{
    Matrix4 m = Matrix4();

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            m.Data[y][x] = Data[y][0] * a.Data[0][x] +
                Data[y][1] * a.Data[1][x] +
                Data[y][2] * a.Data[2][x] +
                Data[y][3] * a.Data[3][x];
        }
    }

    return m;
}


void Matrix4::MultiplyBy(Matrix4& a)
{
    Matrix4 m = Matrix4();

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            m.Data[y][x] = Data[y][0] * a.Data[0][x] +
                Data[y][1] * a.Data[1][x] +
                Data[y][2] * a.Data[2][x] +
                Data[y][3] * a.Data[3][x];
        }
    }

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            Data[y][x] = m.Data[y][x];
        }
    }
}


bool Matrix4::Equals(Matrix4& m)
{
    bool Result = true;

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (abs(Data[y][x] - m.Data[y][x]) > epsilon)
            {
                Result = false;
            }
        }
    }

	return Result;
}


std::wstring Matrix4::ToString()
{
    std::wstring s(L"");

    for (int y = 0; y < 4; y++)
    {
        s += std::to_wstring(Data[y][0]) + L" " +
            std::to_wstring(Data[y][1]) + L" " +
            std::to_wstring(Data[y][2]) + L" " +
            std::to_wstring(Data[y][3]) + L"\n";
    }

    return s;
}