#include "my_vector.hpp"
#include "my_bit_vector.hpp"

#include <iostream>

template <typename T>
void PrintVectorInfo(const Containers::Vector<T>& vector);

void Test1();
void Test2();
void Test3();

void TestBoolVector();

int main()
{
    try 
    {
        Test1();
        Test2();
        Test3();

        TestBoolVector();
    }
    catch(std::exception* exception)
    {
        std::cerr << exception->what();
        delete exception;
        return -1;
    }

    return 0;
}

void Test1()
{
    std::cout << "-------<1>------\n";

    Containers::Vector<int> vector;

    vector.PushBack(1);
    vector.PushBack(2);
    vector.PushBack(3);

    std::cout << vector[0] << " " << vector[1] << " " << vector[2] << '\n';

    vector[2] = 10;

    std::cout << "vector[2] = 10: " << vector[0] << " " << vector[1] << " " << vector[2] << '\n';

    vector.PopBack();

    std::cout << "vector.PopBack(): " << vector[0] << " " << vector[1] << '\n';

    vector.PopFront();

    std::cout << "vector.PopFront(): " << vector[0] << '\n';

    std::cout << "----------------\n\n";
}

void Test2()
{
    std::cout << "-------<2>------\n";

    Containers::Vector<char> vector;

    PrintVectorInfo(vector);

    vector.PushBack('a');

    PrintVectorInfo(vector);

    for (std::size_t i = 0; i < 10; ++i)
    {
        vector.PushBack(static_cast<char>('b' + i));
    }

    PrintVectorInfo(vector);

    vector.PopBack();
    PrintVectorInfo(vector);

    vector.Erase(5);
    PrintVectorInfo(vector);

    vector.PopFront();
    PrintVectorInfo(vector);

    std::cout << "----------------\n\n";
}

void Test3()
{
    std::cout << "-------<3>------\n";

    Containers::Vector<double> kek(12, 52.5252);

    std::cout << "Is empty: "<< kek.Empty() << '\n';

    PrintVectorInfo(kek);

    kek.Clear();

    std::cout << "Is empty: "<< kek.Empty() << '\n';

    PrintVectorInfo(kek);

    kek.PushBack(42.0);

    std::cout << "Is empty: "<< kek.Empty() << '\n';

    PrintVectorInfo(kek);

    std::cout << "----------------\n\n";
}

template <typename T>
void PrintVectorInfo(const Containers::Vector<T>& vector)
{
    std::cout << ">----<\n";

    std::cout << "Size is     " << vector.Size() << '\n';
    std::cout << "Capacity is " << vector.Capacity() << '\n';
    std::cout << "Elements := { ";
    for (std::size_t i = 0; i < vector.Size(); ++i)
    {
        std::cout << vector[i] << ' ';
    }
    std::cout << "}\n";

    std::cout << ">----<\n\n";
}

void TestBoolVector()
{
    Containers::Vector<bool> bit_set;

    PrintVectorInfo(bit_set);

    bit_set.PushBack(true);
    PrintVectorInfo(bit_set);

    bit_set.PushBack(false);
    PrintVectorInfo(bit_set);

    bit_set.PushBack(true);
    PrintVectorInfo(bit_set);

    bit_set[2] = false;
    PrintVectorInfo(bit_set);

    bit_set.PopFront();
    PrintVectorInfo(bit_set);

    bit_set.Insert(true, 1);
    PrintVectorInfo(bit_set);

    bit_set.PushFront(true);
    PrintVectorInfo(bit_set);
}