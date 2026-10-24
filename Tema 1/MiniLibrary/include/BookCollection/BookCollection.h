#pragma once

#include <string>

class BookCollection
{
private:
    std::string *books;
    int size;
    int capacity;

public:
    explicit BookCollection(int capacity);

    ~BookCollection();

    BookCollection(const BookCollection &other);
    BookCollection(BookCollection &&other) noexcept;

    BookCollection &operator=(const BookCollection &) = delete;
    BookCollection &operator=(BookCollection &&) = delete;

    void addBook(const std::string &title);
    void print() const;

    int getSize() const;
    int getCapacity() const;
};
