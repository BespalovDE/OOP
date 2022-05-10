#pragma once
#include "CBody.h"

class CCompound final: 
    public CBody,
    public std::enable_shared_from_this<CCompound> // ќбъекты, производные от enable_shared_from_this, могут использовать методы shared_from_this в функци€х-членах 
                                                   // дл€ создани€ владельцев shared_ptr экземпл€ра, которые владеют им совместно с существующими владельцами shared_ptr
{
    public:
        double GetDensity() const override;
        double GetVolume() const override;
        double GetMass() const override;
        std::string GetName() const override;
        bool AddChildBody(std::shared_ptr<CBody> childPtr);
    private:
        void SetParentPtr(std::shared_ptr<CBody> parentPtr);
        std::weak_ptr<CBody> GetParentPtr() const;
        std::vector<std::shared_ptr<CBody>> m_children;
        std::vector<int> m_level;
        std::weak_ptr<CBody> m_parent_ptr;
};

