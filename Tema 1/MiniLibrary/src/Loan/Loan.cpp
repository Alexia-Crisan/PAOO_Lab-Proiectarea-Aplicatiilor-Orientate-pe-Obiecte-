#include "Loan/Loan.h"

#include <iostream>
#include <stdexcept>

Loan::Loan(const Book& book, const Member& member, int days)
    : book(book), member(member), days(days) {

    if (days <= 0) {
        throw std::invalid_argument("Loan duration must be positive");
    }

    std::cout << "[Loan] Constructor\n";
}

const Book& Loan::getBook() const {
    return book;
}

const Member& Loan::getMember() const {
    return member;
}

int Loan::getDays() const {
    return days;
}

void Loan::print() const {
    std::cout << member.getName()
              << " borrowed \"" << book.getTitle()
              << "\" for " << days << " days.\n";
}
