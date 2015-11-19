#ifndef __STOCK_EXCEPTION_H__
#define __STOCK_EXCEPTION_H__

#include <string>
#include <exception>
#include <iostream>

namespace stock
{

class stock_exception : public std::exception
{
public:
    stock_exception( const std::string& msg ="" ) noexcept
        : message( msg )
    {};

    stock_exception( std::string&& msg ) noexcept
        : message( msg )
    {};

    const char* what() const noexcept
    {
        return message.c_str();
    };

private:
    std::string message;
};

} // namespace

#endif
