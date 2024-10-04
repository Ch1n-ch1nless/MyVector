#ifndef MY_BIT_VECTOR_HPP
#define MY_BIT_VECTOR_HPP

#include "my_vector.hpp"
#include <cstring>

namespace Containers
{
    template<>
    class Vector<bool>
    {
    public:
        class BitRef
        {
        public:
            BitRef(uint8_t& cur_byte, uint8_t bit_mask) :
                cur_byte_   (cur_byte),
                bit_mask_   (bit_mask)
            {
            }

            operator bool() const
            {  
                return ((cur_byte_ & bit_mask_) != 0) ? true : false;
            }

            const BitRef& operator= (bool bit)
            {
                if (bit)
                {
                    cur_byte_ |= bit_mask_;
                }
                else
                { 
                    cur_byte_ &= ~bit_mask_;
                }

                return *this;
            }

            const BitRef& operator= (const BitRef& other)
            {
                return this->operator=(bool(other));
            }

        private:
            uint8_t&    cur_byte_;
            uint8_t     bit_mask_;  
        };

         Vector();
         Vector(const Vector& other);
        ~Vector();

        Vector& operator= (const Vector& other);

        bool    operator[](std::size_t index) const;

        BitRef  operator[](std::size_t index);

        BitRef          Front       ();
        const BitRef    Front       () const;
        BitRef          Back        ();
        const BitRef    Back        ()  const;

        void            Insert      (const bool& elem, std::size_t index);
        void            PushFront   (const bool& elem);
        void            PushBack    (const bool& elem);

        void            Erase       (std::size_t index);
        void            PopFront    ();
        void            PopBack     ();

        void            Clear       ();
 
        std::size_t     Size        () const;
        std::size_t     Capacity    () const;

        bool            Empty       () const; 

    private:
        uint8_t*    pointer_    = nullptr;
        std::size_t size_       = 0;
        std::size_t capacity_   = 8;

        std::size_t RoundToBytes(std::size_t bits_number);
        void        ReAlloc     (std::size_t new_size);

        void        SetBit      (std::size_t index, bool value);
        bool        GetBit      (std::size_t index);
    };
} // namespace Containers

#endif //MY_BIT_VECTOR_HPP