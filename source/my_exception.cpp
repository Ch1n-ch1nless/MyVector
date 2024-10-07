#include "my_exception.hpp"

Utils::MyException::MyException(ErrorCode      code,  
                                MyException*   prev_exception, 
                                const char*    file,
                                const char*    function,
                                int            line              ) noexcept(true)                     
:
    prev_exception_ (prev_exception),
    message_         (nullptr),
    code_           (code),
    file_           (file),
    function_       (function),
    line_           (line)
{
}

Utils::MyException::MyException(const char*    msg,  
                                MyException*   prev_exception, 
                                const char*    file,
                                const char*    function,
                                int            line                ) noexcept(true)                 
:
    prev_exception_ (prev_exception),
    message_         (msg),
    code_           (Utils::ErrorCode::UNKNOWN),
    file_           (file),
    function_       (function),
    line_           (line)
{
}

Utils::MyException::~MyException() noexcept(true)
{
    if (prev_exception_) delete prev_exception_;
}

const Utils::MyException* Utils::MyException::GetPrev() noexcept(true)
{
    return prev_exception_;
}

void Utils::MyException::What() noexcept(true)
{
    PrintFileLocation();
    PrintError();

    if (prev_exception_ != nullptr) 
    {
        prev_exception_->What();
    }
}

void Utils::MyException::PrintFileLocation()
{
    fprintf(stderr, "in file: %s\nin function: %s\non line: %d\n", file_, function_, line_);
}

void Utils::MyException::PrintError()
{
    if (message_ != nullptr)
    {
        fprintf(stderr, "error_message: %s\n", message_);
        return;
    }

    switch (code_)
    {
    case Utils::ErrorCode::NONE :
        fprintf(stderr, "error_message: %s\n", "None");
        break;

    case Utils::ErrorCode::BAD_ALLOC :
        fprintf(stderr, "error_message: %s\n", BAD_ALLOC_MESSAGE);
        break;

    case Utils::ErrorCode::WRONG_ACCESS :
        fprintf(stderr, "error_message: %s\n", WRONG_ACCESS_MESSAGE);
        break;

    case Utils::ErrorCode::UNKNOWN :
        fprintf(stderr, "error_message: %s\n", "Unknown");
        break;
    
    default:
        fprintf(stderr, "ERROR!!!\n");
        break;
    }
}

