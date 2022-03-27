#pragma once
#include <string>
#include <set>
#include <iostream>
#include <optional>
#include <algorithm>

struct Args
{
	std::string fileName;
};

std::optional<Args> ParseArgs(int argc, char *argv[], std::ostream &outStream);
bool FillFilterSet(std::ifstream &inputStream, std::set <std::string> &filterSet, std::ostream &outStream);
void ProcessingIncomingLine(const std::set <std::string> &filterSet, std::istream &inStream, std::ostream &outStream);
