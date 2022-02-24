// fill.cpp
// "$(ProjectDir)test.bat" "$(TargetPath)"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack> 
#include <queue>

using namespace std;
const int maxWidth = 100;
const int maxHeight = 100;

typedef char FieldMas[100][100];

struct Point
{
	int height = 0;
	int width = 0;
};

bool GetInputData(ifstream &inputFile, stack <Point> &startPoints, FieldMas &fieldMas)
{
	string inputLine;
	bool existsString = true;
	for (int stringsCount = 0; stringsCount < maxHeight; stringsCount++)
	{
		if (existsString)
		{
			if (!getline(inputFile, inputLine))
				existsString = false;
		}
		for (int i = 0; i < maxWidth; i++)
		{
			char inputChar = ' ';
			if (existsString)
			{
				if (inputLine.length() > 0 && inputLine.length() - 1 >= i)
				{
					inputChar = inputLine[i];
					switch (inputChar)
					{
					case ' ':
					case '#':
						break;
					case 'O':
						startPoints.push({ stringsCount, i });
						break;
					default:
						return 1;
					}
				}
			}
			fieldMas[stringsCount][i] = inputChar;
		}
	}
	return 0;
}

void SetTopPoint(queue <Point>& tempPoints, FieldMas& fieldMas, Point point)
{
	if (point.height > 0 && fieldMas[point.height - 1][point.width] == ' ')
	{
		fieldMas[point.height - 1][point.width] = '.';
		tempPoints.push({ point.height - 1, point.width });
	}
}

void SetBotPoint(queue <Point>& tempPoints, FieldMas& fieldMas, Point point)
{
	if (point.height < maxHeight - 1 && fieldMas[point.height + 1][point.width] == ' ')
	{
		fieldMas[point.height + 1][point.width] = '.';
		tempPoints.push({ point.height + 1, point.width });
	}
}

void SetLeftPoint(queue <Point>& tempPoints, FieldMas& fieldMas, Point point)
{
	if (point.width > 0 && fieldMas[point.height][point.width - 1] == ' ')
	{
		fieldMas[point.height][point.width - 1] = '.';
		tempPoints.push({ point.height, point.width - 1 });
	}
}

void SetRightPoint(queue <Point>& tempPoints, FieldMas& fieldMas, Point point)
{
	if (point.width < maxWidth - 1 && fieldMas[point.height][point.width + 1] == ' ')
	{
		fieldMas[point.height][point.width + 1] = '.';
		tempPoints.push({ point.height, point.width + 1 });
	}
}

void SetPointsAround(queue <Point> &tempPoints, FieldMas& fieldMas, Point point)
{
	SetTopPoint(tempPoints, fieldMas, point);
	SetBotPoint(tempPoints, fieldMas, point);
	SetLeftPoint(tempPoints, fieldMas, point);
	SetRightPoint(tempPoints, fieldMas, point);
}

void Fill(stack <Point>& startPoints, FieldMas& fieldMas)
{
	while (!startPoints.empty())
	{
		queue <Point> tempPoints;
		Point startPoint = startPoints.top();
		startPoints.pop();
		SetPointsAround(tempPoints, fieldMas, startPoint);
		while (!tempPoints.empty())
		{
			startPoint = tempPoints.front();
			tempPoints.pop();
			SetPointsAround(tempPoints, fieldMas, startPoint);
		}
	}
}

void ShowResult(ofstream &outputFile, const FieldMas &fieldMas)
{
	for (int y = 0; y < maxHeight; y++)
	{
		if (y > 0)
			outputFile << '\n';
		for (int x = 0; x < maxWidth; x++)
		{
			outputFile << fieldMas[y][x];
		}
	}
}

bool FileIsExist(string filePath)
{
	bool isExist = false;
	ifstream fin(filePath.c_str());
	if (fin.is_open())
		isExist = true;
	fin.close();
	return isExist;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Not correct parametres!" << endl;
		return 1;
	}
	if (!FileIsExist(argv[1]))
	{
		cout << "Failed to open file for reading!" << endl;
		return 1;
	}
	if (!FileIsExist(argv[2]))
	{
		cout << "Failed to open file for writing!" << endl;
		return 1;
	}
	ifstream inputFile(argv[1]);
	ofstream outputFile(argv[2]);
	if (!inputFile.is_open())
	{
		cout << "Failed to open file for reading!" << endl;
		return 1;
	}
	if (!outputFile.is_open())
	{
		cout << "Failed to open file for writing!" << endl;
		return 1;
	}
	stack <Point> startPoints;
	FieldMas fieldMas;
	if (GetInputData(inputFile, startPoints, fieldMas))
	{
		cout << "Input file has the not correct symbol!" << endl;
		return 1;
	}
	if (!startPoints.empty())
	{ 
		Fill(startPoints, fieldMas);
	}
	ShowResult(outputFile, fieldMas);
	outputFile.close();
}