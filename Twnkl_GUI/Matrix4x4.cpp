
#include <math.h>

#include "Matrix4x4.h"

// returns identity matrix
Matrix4x4::Matrix4x4()
{

}


// rotation x = 0, y = 1, z = 2
Matrix4x4::Matrix4x4(int axis, double r)
{
    switch (axis)
    {
    case 0:
        Data[1][1] = cos(r);
        Data[1][2] = -sin(r);
        Data[2][1] = sin(r);
        Data[2][2] = cos(r);
        break;
    case 1:
        Data[0][0] = cos(r);
        Data[0][2] = sin(r);
        Data[2][0] = -sin(r);
        Data[2][2] = cos(r);
        break;
    case 2:
        Data[0][0] = cos(r);
        Data[0][1] = -sin(r);
        Data[1][0] = sin(r);
        Data[1][1] = cos(r);
        break;
    }
}


// translation matrix
Matrix4x4::Matrix4x4(double x, double y, double z)
{
	Data[0][3] = x;
	Data[1][3] = y;
	Data[2][3] = z;
}


// shearing matrix
Matrix4x4::Matrix4x4(double xy, double xz, double yx, double yz, double zx, double zy)
{
    Data[0][1] = xy;
    Data[0][2] = xz;
    Data[1][0] = yx;
    Data[1][2] = yz;
    Data[2][0] = zx;
    Data[2][1] = zy;
}


Matrix4x4::Matrix4x4(double aa, double ab, double ac, double ad, 
    double ba, double bb, double bc, double bd, double ca, double cb, double cc, double cd, double da, double db, double dc, double dd)
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


double Matrix4x4::Determinant()
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


void Matrix4x4::Invert()
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
    det = 1.0f / det;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Data[i][j] = float(Result[i][j] * det);
        }
    }
}


bool Matrix4x4::Equals(Matrix4x4)
{
	return false;
}