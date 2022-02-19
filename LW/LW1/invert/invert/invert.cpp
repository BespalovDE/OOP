// invert.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;
typedef double Matrix3x3[3][3];
typedef double Matrix2x2[2][2];

void ShowMatrix(const Matrix3x3& mat)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			std::cout.setf(std::ios::fixed);
			std::cout.precision(3);
			std::cout << mat[x][y] << " ";
		}
		cout << endl;
	}
}

bool GetMatrix(ifstream &inputFile, Matrix3x3& mat)
{
	int x = 0;
	int y = 0;
	string inputLine;
	int allMtrixPositions = 0;
	try
	{
		while (getline(inputFile, inputLine))
		{
			istringstream strm(inputLine);
			for (int x = 0; x < 3; x++)
			{
				string inputValue = "";
				strm >> inputValue;
				if (inputValue != "")
				{
					mat[x][y] = std::stod(inputValue);
					allMtrixPositions++;
				}
			}
			y++;
		}
		if (allMtrixPositions == 9)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	catch (const exception& error)
	{
		return false;
	}
}

double GetMinor(const Matrix3x3& inputMat, int x, int y)
{
	Matrix2x2 mat;
	int m = 0;
	for (int j = 0; j < 3; j++)
	{
		if (j != y)
		{
			int n = 0;
			for (int i = 0; i < 3; i++)
			{
				if (i != x)
				{
					mat[n][m] = inputMat[i][j] ;
					n++;
				}
			}
			m++;
		}
	}
	return mat[0][0] * mat[1][1] - mat[1][0] * mat[0][1];
}

void GetMinorMatrix(const Matrix3x3 &m, Matrix3x3 &minorMatrix)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			minorMatrix[x][y] = GetMinor(m,x,y);
		}
	}
}

void GetAlgAdditionsToMinorMatrixElements(Matrix3x3& algMatrix)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if ((x + y) % 2 > 0)
			{
				algMatrix[x][y] = -algMatrix[x][y];
			}
		}
	}
}

void TranspMatrix(Matrix3x3& tranMatrix)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (x > y)
			    swap(tranMatrix[y][x], tranMatrix[x][y]);
		}
	}
}

//void GetRevert(Matrix3x3& resultMat, const Matrix3x3& mat, double determinant)
//{
//	determinant = 1 / determinant;
//	for (int y = 0; y < 3; y++)
//	{
//		for (int x = 0; x < 3; x++)
//		{
//			resultMat[x][y] = mat[x][y] * determinant;
//		}
//	}
//}

double GetDeterminant3x3(const Matrix3x3& m)
{
	double determinantPlus = m[0][0] * m[1][1] * m[2][2] + m[0][2] * m[1][0] * m[2][1] + m[0][1] * m[1][2] * m[2][0];
	double determinantMinus = m[0][2] * m[1][1] * m[2][0] + m[0][0] * m[1][2] * m[2][1] + m[0][1] * m[1][0] * m[2][2];
	return determinantPlus - determinantMinus;
}

bool RevertMatrix(Matrix3x3& mat)
{
	double determinant = GetDeterminant3x3(mat);
	if (abs(determinant) < DBL_EPSILON)
	{
		return false;
	}
	Matrix3x3 minorMatrix;
	GetMinorMatrix(mat, minorMatrix);
	GetAlgAdditionsToMinorMatrixElements(minorMatrix);
	TranspMatrix(minorMatrix);
	determinant = 1 / determinant;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			mat[x][y] = minorMatrix[x][y] * determinant;
		}
	}
	return true;
}

int main(int argc, char* argv[])
{
	Matrix3x3 inputMat;
	if (argc != 2)
	{
		std::cout << "Not correct parametres!" << endl;
		return 1;
	}
	ifstream inputFile(argv[1]);
	if (!inputFile.is_open())
	{
		cout << "Failed to open file for reading!" << endl;
		return 1;
	}
	if (!GetMatrix(inputFile, inputMat))
	{
		std::cout << "Not correct data!" << std::endl;
		return 1;
	}
	if (!RevertMatrix(inputMat))
	{
		std::cout << "The matrix is expressed!" << endl;
		return 1;
	}
	ShowMatrix(inputMat);
}