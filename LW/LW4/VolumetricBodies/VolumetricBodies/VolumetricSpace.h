#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include "CBody.h"
#include "CCompound.h"

class VolumetricSpace
{
	public:
		const std::string leastWeightWater = "The Boby that has the least weight in the water is :";
		const std::string biggestMass = "The Body that has the most biggest mass is:";
		VolumetricSpace(std::istream &input, std::ostream &output);
		bool HandleCommand();
		void PrintBodiesInfo();
		void PrintMaxMassBody() const;
		void PrintBodyWithLeastWeightInWater() const;
	private:
		using Handler = std::function<bool(std::istream &args)>;
		using ActionMap = std::map<std::string, Handler>;
		bool AddSphere(std::istream &inputArgs);
		bool AddParallelepiped(std::istream &inputArgs);
		bool AddCone(std::istream &inputArgs);
		bool AddCylinder(std::istream &inputArgs);
		bool AddCompound(std::istream &inputArgs);
		bool RemoveLastCompoundPtr(std::istream &inputArgs);
		bool Info(std::istream &inputArgs);
		const ActionMap m_actionMap;
		std::istream &m_input;
		std::ostream &m_output;
		std::vector<std::shared_ptr<CBody>> m_bodies;
		std::vector<std::weak_ptr<CCompound>> m_compounds;
};

