#include "Library/Library.h"

#include <iostream>
#include <stdexcept>

Library::Library(int capacity)
    : collection(capacity)
{
    std::cout << "[Library] Constructor\n";
}

void Library::addBook(const Book &book)
{
    collection.addBook(book.getTitle());
    books.push_back(book);
}

void Library::addMember(const Member &member)
{
    for (const Member &existing : members)
    {
        if (existing.getMemberId() == member.getMemberId())
        {
            throw std::invalid_argument("Duplicate member ID");
        }
    }

    members.push_back(member);
}

void Library::createLoan(int bookIndex, int memberIndex, int days)
{
    if (bookIndex < 0 ||
        bookIndex >= static_cast<int>(books.size()))
    {
        throw std::out_of_range("Invalid book index");
    }

    if (memberIndex < 0 ||
        memberIndex >= static_cast<int>(members.size()))
    {
        throw std::out_of_range("Invalid member index");
    }

    loans.emplace_back(books[bookIndex], members[memberIndex], days);
}

void Library::printCatalog() const
{
    std::cout << "\n=== Library catalog ===\n";
    collection.print();
}

void Library::printMembers() const
{
    std::cout << "\n=== Library members ===\n";

    for (const Member &member : members)
    {
        member.print();
    }
}

void Library::printLoans() const
{
    std::cout << "\n=== Current loans ===\n";

    for (const Loan &loan : loans)
    {
        loan.print();
    }
}
