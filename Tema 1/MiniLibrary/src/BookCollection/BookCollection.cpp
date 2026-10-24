#include "BookCollection/BookCollection.h"

#include <iostream>
#include <stdexcept>

BookCollection::BookCollection(int capacity)
    : books(nullptr), size(0), capacity(capacity)
{

    if (capacity < 0)
    {
        throw std::invalid_argument("Capacity cannot be negative");
    }

    if (capacity > 0)
    {
        books = new std::string[capacity];
    }

    std::cout << "[BookCollection] Constructor\n";
}

BookCollection::~BookCollection()
{
    delete[] books;

    std::cout << "[BookCollection] Destructor\n";
}

BookCollection::BookCollection(const BookCollection &other)
    : books(other.capacity > 0
                ? new std::string[other.capacity]
                : nullptr),
      size(other.size),
      capacity(other.capacity)
{

    for (int i = 0; i < size; ++i)
    {
        books[i] = other.books[i];
    }

    std::cout << "[BookCollection] Copy constructor\n";
}

BookCollection::BookCollection(BookCollection &&other) noexcept
    : books(other.books),
      size(other.size),
      capacity(other.capacity)
{

    other.books = nullptr;
    other.size = 0;
    other.capacity = 0;

    std::cout << "[BookCollection] Move constructor\n";
}

void BookCollection::addBook(const std::string &title)
{
    if (size >= capacity)
    {
        throw std::length_error("Book collection is full");
    }

    books[size] = title;
    ++size;
}

void BookCollection::print() const
{
    std::cout << "Books in collection: " << size << '\n';

    for (int i = 0; i < size; ++i)
    {
        std::cout << " - " << books[i] << '\n';
    }
}

int BookCollection::getSize() const
{
    return size;
}

int BookCollection::getCapacity() const
{
    return capacity;
}
