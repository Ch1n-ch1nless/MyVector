#include "my_bit_vector.hpp"

#include <cmath>

Containers::Vector<bool>::Vector()
{
    pointer_    = new uint8_t[capacity_];
    size_       = 0;
}

Containers::Vector<bool>::Vector(const Containers::Vector<bool>& other) :
    size_       (other.size_),
    capacity_   (other.capacity_)
{
    pointer_ = new uint8_t[capacity_];
    std::memcpy(pointer_, other.pointer_, capacity_);
}

Containers::Vector<bool>::~Vector()
{
    delete[] pointer_;
    pointer_    = nullptr;
    size_       = 0;
    capacity_   = 0;
}

Containers::Vector<bool>& Containers::Vector<bool>::operator= (const Containers::Vector<bool>& other)
{
    if (this != &other)
    {
        delete pointer_;

        capacity_   = other.capacity_;
        size_       = other.size_;

        pointer_    = new uint8_t[capacity_];
        std::memcpy(pointer_, other.pointer_, capacity_);
    }

    return *this;
}

bool Containers::Vector<bool>::operator[](std::size_t index) const
{
    //TODO: assert -> exception
    assert((index <= size_) && "ERROR!!! Index is out of range!\n");

    std::size_t byte_num = index << 3;
    std::size_t bit_num  = index & 7;
    uint8_t     bit_mask = 1 << bit_num;

    return (pointer_[byte_num] & bit_mask) ? true : false;
}

Containers::Vector<bool>::BitRef Containers::Vector<bool>::operator[](std::size_t index)
{
    //TODO: assert -> exception
    assert((index <= size_) && "ERROR!!! Index is out of range!\n");

    std::size_t byte_num = index << 3;
    std::size_t bit_num  = index & 7;
    uint8_t     bit_mask = 1 << bit_num;

    return BitRef(pointer_[byte_num], bit_mask);
}

Containers::Vector<bool>::BitRef Containers::Vector<bool>::Front()
{
    return BitRef(pointer_[0], 1);
}

const Containers::Vector<bool>::BitRef Containers::Vector<bool>::Front() const
{
    return BitRef(pointer_[0], 1);
}

Containers::Vector<bool>::BitRef Containers::Vector<bool>::Back()
{
    std::size_t byte_index  = size_ << 3;
    std::size_t bit_index   = size_ % 8;

    return BitRef(pointer_[byte_index], 1 << bit_index);
}

const Containers::Vector<bool>::BitRef Containers::Vector<bool>::Back()  const
{
    std::size_t byte_index  = size_ << 3;
    std::size_t bit_index   = size_ % 8;

    return BitRef(pointer_[byte_index], 1 << bit_index);
}

void Containers::Vector<bool>::Insert(const bool& elem, std::size_t index)
{
    //TODO: assert -> exception
    assert(index < size_ && "ERROR!!! Index is out of range!\n");

    ReAlloc(size_ + 1);

    for (std::size_t i = size_; i > index; --i)
    {
        SetBit(i, GetBit(i-1));
    }

    SetBit(index, elem);
}

void Containers::Vector<bool>::PushFront(const bool& elem)
{
    Insert(elem, 0);
}

void Containers::Vector<bool>::PushBack(const bool& elem)
{
   ReAlloc(size_ + 1);

    SetBit(size_-1, elem);
}

void Containers::Vector<bool>::Erase(std::size_t index)
{
    //TODO: assert -> exception
    assert(index < size_ && "ERROR!!! Index is out of range!\n");

    ReAlloc(size_ - 1);

    for (std::size_t i = index; i < size_; ++i)
    {
        SetBit(i, GetBit(i+1));
    }
}

void Containers::Vector<bool>::PopFront()
{
    Erase(0);
}

void Containers::Vector<bool>::PopBack()
{
    ReAlloc(size_ - 1);

    SetBit(size_, bool(0));
}

void Containers::Vector<bool>::Clear()
{
    size_ = 0;
}

std::size_t Containers::Vector<bool>::Size() const
{
    return size_;
}
std::size_t Containers::Vector<bool>::Capacity() const
{
    return capacity_;
}

bool Containers::Vector<bool>::Empty() const
{
    return (size_ == 0) ? true : false;
} 

std::size_t Containers::Vector<bool>::RoundToBytes(std::size_t bits_number)
{
    return (bits_number + 7) << 3;
}

void Containers::Vector<bool>::ReAlloc(std::size_t new_size)
{
    std::size_t new_capacity = capacity_;

    if (RoundToBytes(new_size) > capacity_)
    {
        new_capacity >>= 1;
    }
    else if (RoundToBytes(new_size) <= (capacity_ / 4))
    {
        new_capacity <<= 1;
    }
    else 
    {
        size_ = new_size;
        return;
    }

    uint8_t* new_ptr = new uint8_t[new_capacity];
    std::memcpy(new_ptr, pointer_, std::min(capacity_, new_capacity));

    delete[] pointer_;

    pointer_    = new_ptr;
    capacity_   = new_capacity;
    size_       = new_size;
}

void Containers::Vector<bool>::SetBit(std::size_t index, bool value)
{
    if (value) 
    {
        pointer_[index / 8] |= (1 << (index % 8));
    } 
    else 
    {
        pointer_[index / 8] &= static_cast<uint8_t>(~(1 << (index % 8)));
    }
}

bool Containers::Vector<bool>::GetBit(std::size_t index)
{
    return (pointer_[index / 8] & static_cast<uint8_t>((1 << (index % 8)))) != 0;
}