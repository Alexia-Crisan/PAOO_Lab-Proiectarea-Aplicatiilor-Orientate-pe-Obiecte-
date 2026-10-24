#pragma once

#include "Book/Book.h"
#include "BookCollection/BookCollection.h"
#include "Loan/Loan.h"
#include "Member/Member.h"

#include <vector>

class Library
{
private:
    BookCollection collection;
    std::vector<Book> books;
    std::vector<Member> members;
    std::vector<Loan> loans;

public:
    explicit Library(int capacity);

    void addBook(const Book &book);
    void addMember(const Member &member);

    void createLoan(int bookIndex, int memberIndex, int days);

    void printCatalog() const;
    void printMembers() const;
    void printLoans() const;
};
