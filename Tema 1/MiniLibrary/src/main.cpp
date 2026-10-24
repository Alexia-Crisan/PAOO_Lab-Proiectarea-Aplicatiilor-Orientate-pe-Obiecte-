#include "Book/Book.h"
#include "Member/Member.h"
#include "BookCollection/BookCollection.h"
#include "Loan/Loan.h"
#include "Library/Library.h"

#include <iostream>
#include <utility>
#include <exception>

int main()
{
    try
    {
        std::cout << "\n========== COPY AND MOVE DEMO ==========\n";

        {
            BookCollection original(5);
            original.addBook("Dune");
            original.addBook("Foundation");

            std::cout << "\nOriginal collection:\n";
            original.print();

            // COPY: creates a separate array
            BookCollection copied(original);
            copied.addBook("Neuromancer");

            std::cout << "\nCopied collection:\n";
            copied.print();

            std::cout << "\nOriginal remains unchanged:\n";
            original.print();

            // MOVE: transfers ownership of the array
            BookCollection moved(std::move(original));

            std::cout << "\nMoved collection:\n";
            moved.print();

            std::cout << "\nOriginal after move: "
                      << original.getSize() << " books\n";
        }

        std::cout << "\n========== LIBRARY DEMO ==========\n";

        {
            Library library(10);

            Book book1("Dune", "Frank Herbert", 1965);
            Book book2("1984", "George Orwell", 1949);

            Member member1("Alice", 101);
            Member member2("Bob", 102);

            library.addBook(book1);
            library.addBook(book2);

            library.addMember(member1);
            library.addMember(member2);

            library.createLoan(0, 0, 14);
            library.createLoan(1, 1, 7);

            library.printCatalog();
            library.printMembers();
            library.printLoans();
        }

        std::cout << "\n========== PROGRAM FINISHED ==========\n";
    }
    catch (const std::exception &error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
