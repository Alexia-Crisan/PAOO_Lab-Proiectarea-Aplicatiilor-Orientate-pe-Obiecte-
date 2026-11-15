#pragma once
#include <iostream>
#include <string>

class Book
{
private:
    std::string *title; // alocat cu new
    int year;

public:
    Book(const std::string &t = "Necunoscut", int y = 0)
        : title(new std::string(t)), year(y) {}

    Book(const Book &other)
        : title(new std::string(*other.title)), year(other.year)
    {
        std::cout << "   [Book] copy constructor\n";
    }

    ~Book()
    {
        std::cout << "   [Book] destructor: " << *title << "\n";
        delete title;
    }

    // ----- Item 10 + Item 11 + Item 12 -----
    Book &operator=(const Book &rhs) // Item 10: returneaza Book&
    {
        std::cout << "   [Book] operator=\n";

        // Item 11: autoasignare
        if (this == &rhs)
        {
            std::cout << "   [Book] autoasignare - nu fac nimic\n";
            return *this;
        }

        delete title;
        title = new std::string(*rhs.title);
        year = rhs.year; // Item 12: copiem toate campurile

        return *this; // Item 10: permite a = b = c
    }

    void print(const std::string &label) const
    {
        std::cout << "   " << label << " -> " << *title << " (" << year << ")\n";
    }
};

// ===========================================================
// Item 12: Copy all parts of an object.
// ===========================================================

// Varianta CORECTA
class EBook : public Book
{
private:
    double sizeMb;

public:
    EBook(const std::string &t, int y, double mb)
        : Book(t, y), sizeMb(mb) {}

    EBook(const EBook &other)
        : Book(other), sizeMb(other.sizeMb)
    {
    }

    EBook &operator=(const EBook &rhs)
    {
        Book::operator=(rhs); // copiaza partea de baza
        sizeMb = rhs.sizeMb;
        return *this;
    }

    void printEBook(const std::string &label) const
    {
        print(label);
        std::cout << "      dimensiune: " << sizeMb << " MB\n";
    }
};