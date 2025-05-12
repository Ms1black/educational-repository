#pragma once
#include <iostream>

class IDisplayable {
public:
    virtual ~IDisplayable() = default; 
    virtual void display(std::ostream& os) const = 0; 
};

inline std::ostream& operator<<(std::ostream& os, const IDisplayable& obj) {
    obj.display(os);
    return os;
}