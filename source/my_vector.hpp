#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <cassert>
#include <cstdint>
#include <cstddef>

#include "my_exception.hpp"

namespace Containers
{
    const std::size_t INIT_CAPACITY = 1024;

    template <typename T>
    void Swap(T& elem1, T& elem2)
    {
        T temp_elem = elem1;
        elem1 = elem2;
        elem2 = temp_elem;
    }

    template <typename T>
    class Vector
    {
    public:
         Vector();
         Vector(std::size_t len);
         Vector(std::size_t, const T& init_value);
         Vector(const Vector& other_vector);

        ~Vector();

        Vector&  operator= (const Vector& other);
              T& operator[](std::size_t index);
        const T& operator[](std::size_t index) const; 

              T&    Front       ();
        const T&    Front       () const;
              T&    Back        ();
        const T&    Back        ()  const;

        void        Insert      (const T& elem, std::size_t index);
        void        PushFront   (const T& elem);
        void        PushBack    (const T& elem);

        void        Erase       (std::size_t index);
        void        PopFront    ();
        void        PopBack     ();

        void        Clear       ();
 
        std::size_t Size        () const;
        std::size_t Capacity    () const;

        bool        Empty       () const; 

    private:
        T*          pointer_    = nullptr;
        std::size_t size_       = 0;
        std::size_t capacity_   = 1024;

        void ReAlloc(std::size_t new_size);
    };

    template <typename T>
    Vector<T>::Vector()
    {
        pointer_ = new T[capacity_];
        size_    = 0;
    }

    template <typename T>
    Vector<T>::Vector(std::size_t size)
    {
        pointer_ = new T[capacity_];
        size_    = size;   

        ReAlloc(size_);
    }

    template <typename T>
    Vector<T>::Vector(std::size_t size, const T& init_elem)
    {
        pointer_ = new T[capacity_];
        size_    = size;   

        ReAlloc(size_);

        T* temp_ptr = pointer_;

        for (std::size_t i = 0; i < size_; ++i)
        {
            *temp_ptr++ = init_elem;
        }
    }

    template <typename T>
    Vector<T>::Vector(const Vector& vector)
    {
        size_       = vector.size_;
        capacity_   = vector.capacity_;

        pointer_    = new T[capacity_];
        T* src_ptr  = pointer_;
        T* dest_ptr = vector.pointer_;

        for (std::size_t i = 0; i < size_; ++i)
        {
            *src_ptr++ = *dest_ptr++;
        }
    }

    template<typename T>
    Vector<T>::~Vector()
    {
        delete[] pointer_;

        size_       = 0;
        capacity_   = 0;
        pointer_    = nullptr;
    }

    template<typename T>
    Vector<T>& Vector<T>::operator= (const Vector<T>& other_vector)  
    {
        if (this != &other_vector)
        {
            size_     = other_vector.size_;
            capacity_ = other_vector.capacity_;

            if (pointer_ != nullptr) delete[] pointer_;

            pointer_  = new T[capacity_];

            T* src_ptr  = pointer_;
            T* dest_ptr = other_vector.pointer_;

            for (std::size_t i = 0; i < size_; ++i)
            {
                *src_ptr++ = *dest_ptr++;
            }
        }
    }

    template<typename T>
    T& Vector<T>::operator[] (std::size_t index)
    {
        if (index >= size_) throw new WRONG_ACCESS_EXCEPTION(nullptr);
        return *(pointer_ + index);
    }

    template<typename T>
    const T& Vector<T>::operator[] (std::size_t index) const
    {
        if (index >= size_) throw new WRONG_ACCESS_EXCEPTION(nullptr);
        return *(pointer_ + index);
    }

    template<typename T>
    T& Vector<T>::Front()
    {
        return *(pointer_);
    }

    template<typename T>
    const T& Vector<T>::Front() const
    {
        return *(pointer_);
    }

    template<typename T>
    T& Vector<T>::Back()
    {
        return *(pointer_ + size_ - 1);
    }

    template<typename T>
    const T& Vector<T>::Back() const
    {
        return *(pointer_ + size_ - 1);
    }

    template<typename T>
    void Vector<T>::Insert(const T& elem, std::size_t index)
    {
        if (index >= size_) throw new WRONG_ACCESS_EXCEPTION(nullptr);

        ReAlloc(size_ + 1);

        T temp_elem = elem;

        for (std::size_t i = index; i < size_; ++i)
        {
            Swap(temp_elem, *(pointer_ + i));
        }
    }

    template<typename T>
    void Vector<T>::PushFront(const T& elem)
    {
        Insert(elem, 0);
    }

    template<typename T>
    void Vector<T>::PushBack(const T& elem)
    {
        ReAlloc(size_ + 1);
        *(pointer_ + size_ - 1) = elem;
    }

    template<typename T>
    void Vector<T>::Erase(std::size_t index)
    {
        if (index >= size_) throw new WRONG_ACCESS_EXCEPTION(nullptr);

        ReAlloc(size_ - 1);

        for (std::size_t i = index; i < size_; ++i)
        {
            Swap(*(pointer_ + i), *(pointer_ + i + 1));
        }
    }

    template<typename T>
    void Vector<T>::PopFront()
    {
        Erase(0);
    }

    template<typename T>
    void Vector<T>::PopBack()
    {
        if (size_ == 0) return;
        ReAlloc(size_ - 1);
    }

    template<typename T>
    void Vector<T>::Clear()
    {
        size_ = 0;
    }

    template<typename T>
    std::size_t Vector<T>::Size() const
    {   
        return size_;
    }

    template<typename T>
    std::size_t Vector<T>::Capacity() const
    {
        return capacity_;
    }

    template<typename T>
    bool Vector<T>::Empty() const
    {
        return (size_ == 0);
    }

    template<typename T>
    void Vector<T>::ReAlloc(std::size_t new_size)
    {
        std::size_t new_capacity = 0;

        if (new_size > capacity_)
        {
            new_capacity = capacity_ * 2;
        }
        else if (new_size <= (capacity_ / 4))
        {
            new_capacity = capacity_ / 2;
        }
        else
        {
            size_ = new_size;
            return;
        }

        T* new_ptr = new T[new_capacity];

        for (std::size_t i = 0; i < size_; ++i)
        {
            new_ptr[i] = pointer_[i];
        }

        delete[] pointer_;

        pointer_    = new_ptr;
        capacity_   = new_capacity;
        size_       = new_size;
    }

} //namespace Containers

#endif //MY_VECTOR_HPP