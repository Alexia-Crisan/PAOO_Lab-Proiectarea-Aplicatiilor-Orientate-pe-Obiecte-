#pragma once

#include "Book/Book.h"
#include "Member/Member.h"

class Loan
{
private:
    Book book;
    Member member;
    int days;

public:
    Loan(const Book &book, const Member &member, int days);

    const Book &getBook() const;
    const Member &getMember() const;
    int getDays() const;

    void print() const;
};
