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
        char*       pointer_    = nullptr;
        std::size_t size_       = 0;
        std::size_t capacity_   = 1024;

        void        ReAlloc     (std::size_t new_size);

        T*          GetPointer  (std::size_t offset) const;
        void        DestroyObj  (T* obj_ptr);
        void        DestroyObj  (T* obj_ptr, std::size_t obj_number);
        void        InitObj     (T* obj_ptr);
        void        InitObj     (T* obj_ptr, std::size_t obj_number);

        void        DecCapacity (std::size_t new_size);
        void        IncCapacity (std::size_t new_size);
    };

/*----------------------------< Public Functions >----------------------------*/

    template <typename T>
    Vector<T>::Vector()
    {
        pointer_ = new char[capacity_ * sizeof(T)];
        size_    = 0;
    }

    template <typename T>
    Vector<T>::Vector(std::size_t size)
    {
        pointer_ = new char[capacity_ * sizeof(T)];
        size_    = size;   

        InitObj(GetPointer(0), size_);
    }

    template <typename T>
    Vector<T>::Vector(std::size_t size, const T& init_elem)
    {
        pointer_ = new char[capacity_ * sizeof(T)];
        size_    = size;

        T* init_ptr = GetPointer(0);

        for (std::size_t i = 0; i < size_; ++i)
        {
            init_ptr = new(init_ptr) T(init_elem);
            init_ptr++;
        }
    }

    template <typename T>
    Vector<T>::Vector(const Vector& vector)
    {
        size_       = vector.size_;
        capacity_   = vector.capacity_;

        pointer_    = new char[capacity_ * sizeof(T)];
        T* src_ptr  = reinterpret_cast<T*>(pointer_);
        T* dest_ptr = reinterpret_cast<T*>(vector.pointer_);

        for (std::size_t i = 0; i < size_; ++i)
        {
            //TODO: Is it correct way to init objects?
            src_ptr = new(src_ptr) T(*dest_ptr);
            src_ptr++;
            dest_ptr++;
        }
    }

    template<typename T>
    Vector<T>::~Vector()
    {
        DestroyObj(GetPointer(0), size_);
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

            pointer_  = new char[capacity_ * sizeof(T)];

            T* src_ptr  = reinterpret_cast<T*>(pointer_);
            T* dest_ptr = reinterpret_cast<T*>(other_vector.pointer_);

            for (std::size_t i = 0; i < size_; ++i)
            {
                //TODO: Is it correct way to init objects?
                src_ptr = new(src_ptr) T(*dest_ptr);
                src_ptr++;
                dest_ptr++;
            }
        }
    }

    template<typename T>
    T& Vector<T>::operator[] (std::size_t index)
    {
        if (index >= size_) throw new WRONG_ACCESS_EXCEPTION(nullptr);
        return *(GetPointer(index));
    }

    template<typename T>
    const T& Vector<T>::operator[] (std::size_t index) const
    {
        if (index >= size_) throw new WRONG_ACCESS_EXCEPTION(nullptr);
        return *(GetPointer(index));
    }

    template<typename T>
    T& Vector<T>::Front()
    {
        return *(GetPointer(0));
    }

    template<typename T>
    const T& Vector<T>::Front() const
    {
        return *(GetPointer(0));
    }

    template<typename T>
    T& Vector<T>::Back()
    {
        return *(GetPointer(size_-1));
    }

    template<typename T>
    const T& Vector<T>::Back() const
    {
        return *(GetPointer(size_-1));
    }

    template<typename T>
    void Vector<T>::Insert(const T& elem, std::size_t index)
    {
        if (index >= size_) throw new WRONG_ACCESS_EXCEPTION(nullptr);

        ReAlloc(size_ + 1);

        T temp_elem = elem;

        for (std::size_t i = index; i < size_; ++i)
        {
            Swap(temp_elem, *(GetPointer(i)));
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
        *(GetPointer(size_-1)) = elem;
    }

    template<typename T>
    void Vector<T>::Erase(std::size_t index)
    {
        if (index >= size_) throw new WRONG_ACCESS_EXCEPTION(nullptr);

        ReAlloc(size_ - 1);

        for (std::size_t i = index; i < size_; ++i)
        {
            Swap(*(GetPointer(i)), *(GetPointer(i+1)));
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
        DestroyObj(GetPointer(0), size_);
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

/*----------------------------------------------------------------------------*/

/*----------------------------< Private Functions >---------------------------*/

    template<typename T>
    void Vector<T>::ReAlloc(std::size_t new_size)
    {
        if (new_size > capacity_)
        {
            IncCapacity(new_size);
        }
        else if (new_size <= (capacity_ / 4))
        {
            DecCapacity(new_size);
        }
        else
        {
            if (new_size >= size_) 
            {
                InitObj(GetPointer(size_), new_size - size_);
            }
            else
            {
                DestroyObj(GetPointer(new_size), size_ - new_size);
            } 
            size_ = new_size;
            return;
        }
    }

    template<typename T>
    void Vector<T>::DecCapacity(std::size_t new_size)
    {
        size_t new_capacity = capacity_ / 2;

        char* new_ptr = new char[new_capacity * sizeof(T)];
        
        T* dest_ptr = reinterpret_cast<T*>(new_ptr);
        T* src_ptr  = reinterpret_cast<T*>(pointer_);

        for (std::size_t i = 0; i < new_size; ++i)
        {
            InitObj(dest_ptr);
            //TODO: Is the next line good idea? Maybe we have more effective way!
            *dest_ptr++ = *src_ptr++;               
        }

        DestroyObj(GetPointer(0), size_);
        delete[] pointer_;

        pointer_    = new_ptr;
        size_       = new_size;
        capacity_   = new_capacity;
    }

    template <typename T>
    void Vector<T>::IncCapacity(std::size_t new_size)
    {
        size_t new_capacity = capacity_ * 2;

        char* new_ptr = new char[new_capacity * sizeof(T)];
        
        T* dest_ptr = reinterpret_cast<T*>(new_ptr);
        T* src_ptr  = reinterpret_cast<T*>(pointer_);

        for (std::size_t i = 0; i < size_; ++i)
        {
            InitObj(dest_ptr);
            //TODO: Is the next line good idea? Maybe we have more effective way!
            *dest_ptr++ = *src_ptr++;               
        }

        for (std::size_t i = size_; i < new_size; ++i)
        {
            InitObj(dest_ptr);
            ++dest_ptr;
        }

        DestroyObj(GetPointer(0), size_);
        delete[] pointer_;

        pointer_    = new_ptr;
        size_       = new_size;
        capacity_   = new_capacity;
    }

    template <typename T>
    T* Vector<T>::GetPointer(std::size_t offset) const
    {
        return reinterpret_cast<T*>(pointer_) + offset;
    }

    template <typename T>
    void Vector<T>::DestroyObj(T* obj_ptr)
    {
        obj_ptr->~T();
    }

    template <typename T>
    void Vector<T>::DestroyObj(T* obj_ptr, std::size_t obj_number)
    {
        for (size_t i = 0; i < obj_number; ++i)
        {
            obj_ptr->~T();
            ++obj_ptr;
        }
    }

    template <typename T>
    void Vector<T>::InitObj(T* obj_ptr)
    {
        obj_ptr = new(obj_ptr) T();
    }

    template <typename T>
    void Vector<T>::InitObj(T* obj_ptr, std::size_t obj_number)
    {
        for (size_t i = 0; i < obj_number; ++i)
        {
            obj_ptr = new(obj_ptr) T();
            ++obj_ptr;
        } 
    }

/*----------------------------------------------------------------------------*/

} //namespace Containers

#endif //MY_VECTOR_HPP