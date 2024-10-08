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

        virtual ~MyException() noexcept(true);

        virtual const char* what()      const noexcept(true) override;
        const MyException*  GetPrev()   const noexcept(true);

    private:
        MyException*    prev_exception_;
        std::string     message_;
        ErrorCode       code_;

        const char*     file_;
        const char*     function_;
        int             line_;

        void                GetFileLocation();
        void                GetErrorInfo   (const char* error_msg);
    };

    #define BAD_ALLOC_EXCEPTION(prev_exception) Utils::BadAllocException(prev_exception, __FILE__, (const char*)__FUNCTION__, __LINE__)

    class BadAllocException : public MyException
    {
    public:
         BadAllocException( MyException*   prev_exception,
                            const char* file,
                            const char* function,
                            int         line                ) noexcept(true);

        ~BadAllocException() noexcept(true) override;
    };

    #define WRONG_ACCESS_EXCEPTION(prev_exception) Utils::WrongAccessException(prev_exception, __FILE__, (const char*)__FUNCTION__, __LINE__)

    class WrongAccessException : public MyException
    {
    public: 
         WrongAccessException(  MyException*   prev_exception,
                                const char* file,
                                const char* function,
                                int         line                ) noexcept(true);

        virtual ~WrongAccessException() noexcept(true) override;
    };
} //namespace Utils

#endif //MY_EXCEPTIONS_HPP