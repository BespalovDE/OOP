#pragma once
#include "Automobile.h"
#include "map"
#include <functional>

class AutomobileInterface
{
    public:
        AutomobileInterface(Automobile &automobile, std::istream &input, std::ostream &output);
    	bool InterfaceCommand();
    private:
    	bool Info();
    	bool EngineOn();
    	bool EngineOff();
    	bool SetGear(std::istream &args);
    	bool SetSpeed(std::istream &args);
    
        Automobile &m_automobile;
    	std::istream &m_input;
    	std::ostream &m_output;
    	const std::map<std::string, std::function<bool(std::istream &args) >> m_actionMap;
};

