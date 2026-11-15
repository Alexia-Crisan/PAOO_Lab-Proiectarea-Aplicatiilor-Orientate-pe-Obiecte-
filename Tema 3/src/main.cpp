#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "IResource.hpp"
#include "UniqueBuffer.hpp"
#include "DeepCopyBuffer.hpp"
#include "SharedBuffer.hpp"

namespace res = resources;

namespace demo
{

    void info(const std::string &msg) // acelasi nume ca resources::info
    {
        std::cout << "[demo] " << msg << "\n";
    }

    void mayThrow()
    {
        throw std::runtime_error("eroare simulata");
    }

    // Item 13 - FARA RAII: pointer simplu + new/delete manual
    void withoutRaii()
    {
        res::IResource *r = new res::DeepCopyBuffer(3, 7);
        mayThrow();
        delete r;
    }

    // Item 13 - CU RAII: unique_ptr sterge singur obiectul
    void withRaii()
    {
        std::unique_ptr<res::IResource> r = std::make_unique<res::DeepCopyBuffer>(3, 7);
        mayThrow();
    }

    std::unique_ptr<res::IResource> makeResource(int kind)
    {
        switch (kind)
        {
        case 1:
            return std::make_unique<res::UniqueBuffer>(2, 1);
        case 2:
            return std::make_unique<res::DeepCopyBuffer>(2, 2);
        default:
            return std::make_unique<res::SharedBuffer>(2, 3);
        }
    }

} // namespace demo

int main()
{
    // ---------------------------------------------------------
    std::cout << "##### NAMESPACES #####\n";
    res::info("functia info din namespace-ul resources");
    demo::info("functia info din namespace-ul demo");

    // ---------------------------------------------------------
    std::cout << "\n##### ITEM 13: foloseste obiecte pentru a administra resurse #####\n";

    std::cout << "\n--- Fara RAII (pointer simplu) ---\n";
    try
    {
        demo::withoutRaii();
    }
    catch (const std::exception &e)
    {
        demo::info(std::string("exceptie prinsa: ") + e.what());
    }
    std::cout << "   => NU apare niciun mesaj 'destructor': memoria s-a pierdut (SCURGERE INTENTIONATA)\n";

    std::cout << "\n--- Cu RAII (unique_ptr) ---\n";
    try
    {
        demo::withRaii();
    }
    catch (const std::exception &e)
    {
        demo::info(std::string("exceptie prinsa: ") + e.what());
    }
    std::cout << "   => destructorul a rulat SINGUR, chiar daca s-a aruncat exceptie\n";

    std::cout << "\n--- Functii virtuale: aceeasi interfata, 3 clase diferite ---\n";
    {
        std::vector<std::unique_ptr<res::IResource>> all;
        all.push_back(demo::makeResource(1));
        all.push_back(demo::makeResource(2));
        all.push_back(demo::makeResource(3));

        for (const auto &r : all)
        {
            std::cout << "\n   operator<<: " << *r << "\n";
            r->use();
            r->describe();
        }
        std::cout << "\n";
    }

    // ---------------------------------------------------------
    std::cout << "\n##### ITEM 14, varianta 1: copiere interzisa, doar mutare #####\n";
    {
        res::UniqueBuffer u1(3, 1);
        // res::UniqueBuffer u2 = u1;      // EROARE DE COMPILARE: copy constructor sters
        // res::UniqueBuffer u3(2); u3 = u1; // EROARE DE COMPILARE: copy assignment sters

        std::cout << "\n   UniqueBuffer u2 = std::move(u1);\n";
        res::UniqueBuffer u2 = std::move(u1); // move constructor
        u1.use();                             // sursa a ramas goala
        u2.use();

        std::cout << "\n   u3 = std::move(u2);\n";
        res::UniqueBuffer u3(2, 5);
        u3 = std::move(u2); // move assignment
        u2.use();
        u3.use();
        std::cout << "\n";
    }

    // ---------------------------------------------------------
    std::cout << "\n##### ITEM 14, varianta 2: copie adanca #####\n";
    {
        res::DeepCopyBuffer d1(3, 10);

        std::cout << "\n   DeepCopyBuffer d2 = d1;\n";
        res::DeepCopyBuffer d2 = d1; // copy constructor
        d2[0] = 99;                  // modificam DOAR copia
        d1.use();
        d2.use();
        std::cout << "   => d1 nu s-a schimbat\n";

        std::cout << "\n   d3 = d1;\n";
        res::DeepCopyBuffer d3(1, 0);
        d3 = d1; // copy assignment
        d3.use();

        std::cout << "\n   d1 = d1;  (autoasignare)\n";
        d1 = d1;
        d1.use();

        std::cout << "\n   d3 = DeepCopyBuffer(2, 5);  (obiect temporar => move assignment)\n";
        d3 = res::DeepCopyBuffer(2, 5);
        d3.use();
        std::cout << "\n";
    }

    // ---------------------------------------------------------
    std::cout << "\n##### ITEM 14, varianta 3: partajare (reference counting) #####\n";
    {
        res::SharedBuffer s1(3, 1);
        std::cout << "   use_count = " << s1.useCount() << "\n";

        std::cout << "\n   SharedBuffer s2 = s1;\n";
        res::SharedBuffer s2 = s1; // copy constructor: partajam
        std::cout << "   use_count = " << s1.useCount() << "\n";

        s2[0] = 99; // modificam prin s2...
        s1.use();   // ...si se vede si in s1 (e acelasi array)
        s2.use();

        std::cout << "\n   SharedBuffer s3(1, 0); s3 = s1;\n";
        res::SharedBuffer s3(1, 0);
        s3 = s1; // copy assignment
        std::cout << "   use_count = " << s1.useCount() << "\n";

        std::cout << "\n   s4 = std::move(s3);\n";
        res::SharedBuffer s4(1, 0);
        s4 = std::move(s3); // move assignment: use_count nu creste
        std::cout << "   use_count = " << s1.useCount() << "\n";
        s3.use(); // s3 e acum gol
        std::cout << "\n";
    }

    std::cout << "\n##### SFARSIT #####\n";
    return 0;
}