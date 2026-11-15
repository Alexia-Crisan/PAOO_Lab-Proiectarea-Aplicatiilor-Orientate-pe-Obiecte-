#pragma once
#include "IResource.hpp"

namespace resources
{

    // Item 13: constructorul ia resursa (new[]), destructorul o elibereaza (delete[])
    //
    // Item 14, INTERZICEM copierea (un singur proprietar).
    //          Permitem doar MUTAREA = transfer de proprietate.
    class UniqueBuffer : public IResource
    {
    private:
        int *data;
        std::size_t size;

    public:
        explicit UniqueBuffer(std::size_t n, int fill = 0)
            : data(new int[n]), size(n)
        {
            for (std::size_t i = 0; i < size; ++i)
            {
                data[i] = fill;
            }
            std::cout << "   [UniqueBuffer] constructor: " << size << " elemente\n";
        }

        ~UniqueBuffer() override
        {
            std::cout << "   [UniqueBuffer] destructor: delete[] (" << size << " elemente)\n";
            delete[] data;
        }

        // Copierea este interzisa
        UniqueBuffer(const UniqueBuffer &) = delete;
        UniqueBuffer &operator=(const UniqueBuffer &) = delete;

        // Move constructor
        UniqueBuffer(UniqueBuffer &&other) noexcept
            : data(other.data), size(other.size)
        {
            other.data = nullptr;
            other.size = 0;
            std::cout << "   [UniqueBuffer] move constructor\n";
        }

        // Move assignment: elibereaza ce avea, apoi preia resursa
        UniqueBuffer &operator=(UniqueBuffer &&rhs) noexcept
        {
            std::cout << "   [UniqueBuffer] move assignment\n";
            if (this != &rhs)
            {
                delete[] data;
                data = rhs.data;
                size = rhs.size;
                rhs.data = nullptr;
                rhs.size = 0;
            }
            return *this;
        }

        void use() const override
        {
            std::cout << "   [UniqueBuffer] contine: ";
            printArray(data, size);
            std::cout << "\n";
        }

        std::string name() const override { return "UniqueBuffer"; }
        std::string copyPolicy() const override { return "copiere interzisa, doar mutare"; }
    };

}