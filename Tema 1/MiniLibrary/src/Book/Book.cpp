#include "Book/Book.h"

#include <iostream>
#include <stdexcept>

Book::Book(const std::string &title,
           const std::string &author,
           int year)
    : title(title), author(author), year(year)
{

    if (title.empty())
    {
        throw std::invalid_argument("Book title cannot be empty");
    }

    if (author.empty())
    {
        throw std::invalid_argument("Author cannot be empty");
    }

    if (year <= 0)
    {
        throw std::invalid_argument("Year must be positive");
    }

    std::cout << "[Book] Constructor: " << this->title << '\n';
}

const std::string &Book::getTitle() const
{
    return title;
}

const std::string &Book::getAuthor() const
{
    return author;
}

int Book::getYear() const
{
    return year;
}

void Book::print() const
{
    std::cout << title << " by " << author
              << " (" << year << ")\n";
}
