#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H

#include <iostream>

class IDisplayable {
public:
    virtual void display(std::ostream& os) const = 0;
    virtual ~IDisplayable() = default;
};

#endif // IDISPLAYABLE_H