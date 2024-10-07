#ifndef MY_EXCEPTIONS_HPP
#define MY_EXCEPTIONS_HPP

#include <exception>
#include <string>

#define MY_EXCEPTION(arg, prev_exception) Utils::MyException(arg, prev_exception, __FILE__, (const char*)__FUNCTION__, __LINE__)

namespace Utils
{
    enum class ErrorCode : unsigned int
    {
        NONE            = 0,
        BAD_ALLOC       = 1,
        WRONG_ACCESS    = 2,
        UNKNOWN         = 3,
    };

    const char* const   BAD_ALLOC_MESSAGE       = "Memory allocation problem\n";
    const char* const   WRONG_ACCESS_MESSAGE    = "Access problem\n";

    class MyException : public std::exception
    {
    public:
         MyException(ErrorCode      code,  
                     MyException*   prev_exception, 
                     const char*    file,
                     const char*    function,
                     int            line                        ) noexcept(true);
         MyException(const char*    msg, 
                     MyException*   prev_exception,
                     const char*    file,
                     const char*    function,
                     int            line                        ) noexcept(true);
        ~MyException();

        void                What()      noexcept(true);
        const MyException*  GetPrev()   noexcept(true);

    private:
        MyException*    prev_exception_;
        const char*     message_;
        ErrorCode       code_;

        const char*     file_;
        const char*     function_;
        int             line_;

        void                PrintFileLocation();
        void                PrintError();
    };
} //namespace Utils

#endif //MY_EXCEPTIONS_HPP