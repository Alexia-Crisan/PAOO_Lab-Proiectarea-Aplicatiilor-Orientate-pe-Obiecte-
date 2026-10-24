#pragma once

#include <string>

class Member
{
private:
    std::string name;
    int memberId;

public:
    Member(const std::string &name, int memberId);

    const std::string &getName() const;
    int getMemberId() const;

    void print() const;
};
