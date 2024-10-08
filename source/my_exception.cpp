#include "my_exception.hpp"

#include <cstring>
#include <cmath>
#include <iostream>

static const char* const FILE_LOCATION_MESSAGE = "in file: %s\nin function: %s\non line: %d\n";
static const char* const ERROR_MESSAGE         = "error_message: %s\n";

Utils::MyException::MyException(ErrorCode      code,  
                                MyException*   prev_exception, 
                                const char*    file,
                                const char*    function,
                                int            line              ) noexcept(true)                     
:
    prev_exception_ (prev_exception),
    message_        (),
    code_           (code),
    file_           (file),
    function_       (function),
    line_           (line)
{
    GetFileLocation();
    GetErrorInfo(nullptr);
}

Utils::MyException::MyException(const char*    msg,  
                                MyException*   prev_exception, 
                                const char*    file,
                                const char*    function,
                                int            line                ) noexcept(true)                 
:
    prev_exception_ (prev_exception),
    message_        (),
    code_           (Utils::ErrorCode::UNKNOWN),
    file_           (file),
    function_       (function),
    line_           (line)
{
    GetFileLocation();
    GetErrorInfo(msg);
}

Utils::MyException::~MyException() noexcept(true)
{
    if (prev_exception_) delete prev_exception_;
}

const Utils::MyException* Utils::MyException::GetPrev() const noexcept(true)
{
    return prev_exception_;
}

const char* Utils::MyException::what() const noexcept(true)
{
    return message_.c_str();
}

void Utils::MyException::GetFileLocation()
{
    std::size_t len = static_cast<std::size_t>(log10(static_cast<double>(line_))) + 1;
    len += std::strlen(file_) + std::strlen(function_) + std::strlen(FILE_LOCATION_MESSAGE);

    char* new_str = new char[len];

    snprintf(new_str, len, FILE_LOCATION_MESSAGE, file_, function_, line_);

    message_ += new_str;
    delete[] new_str;
}

void Utils::MyException::GetErrorInfo(const char* error_msg)
{
    if (error_msg == nullptr)
    {
        switch (code_)
        {
        case Utils::ErrorCode::NONE :
            error_msg = "None";
            break;

        case Utils::ErrorCode::BAD_ALLOC :
            error_msg = BAD_ALLOC_MESSAGE;
            break;

        case Utils::ErrorCode::WRONG_ACCESS :
            error_msg = WRONG_ACCESS_MESSAGE;
            break;

        case Utils::ErrorCode::UNKNOWN :
            error_msg = "Unknown";
            break;
        
        default:
            fprintf(stderr, "ERROR!!!\n");
            break;
        }   
    }

    std::size_t len = std::strlen(ERROR_MESSAGE) + std::strlen(error_msg);
    
    char* new_str = new char[len];
    snprintf(new_str, len, ERROR_MESSAGE, error_msg);

    message_ += new_str;
    delete[] new_str;
}

Utils::BadAllocException::BadAllocException(MyException*   prev_exception,
                                            const char* file, const char* function, int line) noexcept(true) :
    MyException(Utils::ErrorCode::BAD_ALLOC, prev_exception, file, function, line)
{
}

Utils::BadAllocException::~BadAllocException() noexcept(true)
{
}

Utils::WrongAccessException::WrongAccessException(  MyException*   prev_exception,
                                                    const char* file, const char* function, int line) noexcept(true) :
    MyException(Utils::ErrorCode::WRONG_ACCESS, prev_exception, file, function, line)
{
}

Utils::WrongAccessException::~WrongAccessException() noexcept(true)
{
}