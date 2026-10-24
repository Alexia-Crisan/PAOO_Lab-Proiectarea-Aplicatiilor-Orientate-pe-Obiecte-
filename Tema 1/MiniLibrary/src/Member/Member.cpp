#include "Member/Member.h"

#include <iostream>
#include <stdexcept>

Member::Member(const std::string &name, int memberId)
    : name(name), memberId(memberId)
{

    if (name.empty())
    {
        throw std::invalid_argument("Member name cannot be empty");
    }

    if (memberId <= 0)
    {
        throw std::invalid_argument("Member ID must be positive");
    }

    std::cout << "[Member] Constructor: " << this->name << '\n';
}

const std::string &Member::getName() const
{
    return name;
}

int Member::getMemberId() const
{
    return memberId;
}

void Member::print() const
{
    std::cout << name << " (ID: " << memberId << ")\n";
}
