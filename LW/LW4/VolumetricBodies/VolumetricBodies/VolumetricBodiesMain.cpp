#include <iostream>
#include "VolumetricSpace.h"

int main()
{
	VolumetricSpace volumetricSpace(std::cin, std::cout);
	std::string command;
	while (!std::cin.eof() && !std::cin.fail())
	{
		if (!volumetricSpace.HandleCommand() && !std::cin.eof())
		{
			std::cout << "Wrong command\n";
		}
	}
	volumetricSpace.PrintBodiesInfo();
	volumetricSpace.PrintMaxMassBody();
	volumetricSpace.PrintBodyWithLeastWeightInWater();
	return 0;
}
