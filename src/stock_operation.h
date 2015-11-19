#ifndef __STOCK_OPERATION_H__
#define __STOCK_OPERATION_H__

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>

namespace stock
{

class stock_operation_type
{
public:
    using timestamp = std::chrono::time_point<std::chrono::system_clock>;
    enum indicator
    {
        BUY  = 0,
        SELL = 1
    };

public:
    stock_operation_type( const std::string& s, int p, int q, indicator i, timestamp t =std::chrono::system_clock::now() )
        : symbol( s )
        , price( p )
        , quantity( q )
        , ind( i )
        , ts( t )
    {};

    bool in_interval( const timestamp& start_time, const std::chrono::minutes& interval ) const
    {
        auto cutoff_time = start_time - interval;
        return cutoff_time <= ts && ts <= start_time;
    }

    int get_price() const       { return price; };
    int get_quantity() const    { return quantity; };

    friend std::ostream& operator<<( std::ostream& os, const stock_operation_type& data )
    {
        os << std::chrono::system_clock::to_time_t( data.ts ) << ": ";
        os << "[" << data.symbol << "]";
        os << ", price = [" << std::setw(3) << data.price << "]";
        os << ", quantity = [" << std::setw(2) << data.quantity << "]";
        os << ", type = [" << ( data.ind == BUY ? "BUY" : "SELL" ) << "]";
        return os;
    };

private:
    std::string symbol;
    int price = 0;
    int quantity = 0;
    indicator ind = BUY;
    timestamp ts;
};


typedef std::vector<stock_operation_type> operation_storage;


inline std::ostream& operator<<( std::ostream& os, const operation_storage& data )
{
    for( auto it : data ) std::cout << it << std::endl;
    return os;
}

} // namespace

#endif
