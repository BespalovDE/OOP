// fill.cpp баллы 0.6
//Приложение fill.exe, выполняющее заливку контуров, заданных в текстовом файле начиная с указанных начальных точек (O).

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;
const int MAX_WIDTH = 100;
const int MAX_HEIGHT = 100;

typedef char FieldMas[100][100];

struct Point
{
	int height = 0;
	int width = 0;
};

bool GetInputField(ifstream &inputFile, queue <Point> &startPoints, FieldMas &fieldMas)
{
	string inputLine;
	bool existsString = true;
	for (int stringsCount = 0; stringsCount < MAX_HEIGHT; stringsCount++)
	{
		if (existsString)
		{
			if (!getline(inputFile, inputLine))
				existsString = false;
		}
		for (int i = 0; i < MAX_WIDTH; i++)
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
						return false;
					}
				}
			}
			fieldMas[stringsCount][i] = inputChar;
		}
	}
	return true;
}

bool CheckPointByFieldLimits(const Point &point)
{
	if (point.height < 0 || point.height >= MAX_HEIGHT)
		return false;
	if (point.width < 0 || point.width >= MAX_WIDTH)
		return false;
	return true;
}

void SetPoint(queue <Point>& queuePoints, FieldMas& fieldMas, Point point)
{
	if (CheckPointByFieldLimits(point) && fieldMas[point.height][point.width] == ' ')
	{
		fieldMas[point.height][point.width] = '.';
		queuePoints.push({ point.height, point.width });
	}
}

void SetPointsAround(queue <Point> &queuePoints, FieldMas& fieldMas, Point point)
{
	SetPoint(queuePoints, fieldMas, { point.height - 1, point.width });
	SetPoint(queuePoints, fieldMas, { point.height, point.width - 1 });
	SetPoint(queuePoints, fieldMas, { point.height + 1, point.width });
	SetPoint(queuePoints, fieldMas, { point.height, point.width + 1 });
}

void Fill(queue <Point>& startPoints, FieldMas& fieldMas)
{
	while (!startPoints.empty())
	{
		queue <Point> queuePoints;
		Point startPoint = startPoints.front();
		startPoints.pop();
		SetPointsAround(queuePoints, fieldMas, startPoint);
		while (!queuePoints.empty())
		{
			startPoint = queuePoints.front();
			queuePoints.pop();
			SetPointsAround(queuePoints, fieldMas, startPoint);
		}
	}
}

void PrintField(ofstream &outputFile, const FieldMas &fieldMas)
{
	for (int y = 0; y < MAX_HEIGHT; y++)
	{
		if (y > 0)
			outputFile << '\n';
		for (int x = 0; x < MAX_WIDTH; x++)
		{
			outputFile << fieldMas[y][x];
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Not correct parametres!" << endl;
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
	queue <Point> startPoints;
	FieldMas fieldMas;
	if (!GetInputField(inputFile, startPoints, fieldMas))
	{
		cout << "Input file has the not correct symbol!" << endl;
		return 1;
	}
	if (!startPoints.empty())
	{ 
		Fill(startPoints, fieldMas);
	}
	PrintField(outputFile, fieldMas);
	outputFile.close();
}