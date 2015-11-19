#ifndef __STOCK_ALGORITHM_H__
#define __STOCK_ALGORITHM_H__

#include <cmath>

#include "stock_data.h"
#include "stock_operation.h"
#include "stock_exception.h"

namespace stock
{

inline double calc_divident_yield( const stock_map& sm, const std::string& stock_symbol, int price )
{
    double result = 0.0;
    auto it = sm.find( stock_symbol );
    if( it != sm.end() ) result = it->second.calc_divident_yield( price );
    else throw stock_exception( std::string("Stock Symbol [") + stock_symbol + "] not found" );
    return result;
}

inline double calc_PE_ratio( const stock_map& sm, const std::string& stock_symbol, int price )
{
    double result = 0.0;
    auto it = sm.find( stock_symbol );
    if( it != sm.end() ) result = it->second.calc_PE_ratio( price );
    else throw stock_exception( std::string("Stock Symbol [") + stock_symbol + "] not found" );
    return result;
}

inline double calc_VWSP( const operation_storage& operations, const std::chrono::minutes& interval )
{
    auto cur_time = std::chrono::system_clock::now();
    double numerator = 0.0;
    int denominator = 0.0;
    for( auto it = operations.rbegin(); it != operations.rend(); ++it )
    {
        if( !it->in_interval( cur_time, interval ) ) break;
        //std::cout << "DEBUG: " << __func__ << ": " << *it << std::endl;
        numerator += double( it->get_price() ) * it->get_quantity();
        denominator += it->get_quantity();
    }
    double result = denominator > 0 ? numerator / denominator : 0.0;
    return result;
}

inline double calc_geometric_mean( const stock_map& sm )
{
    double r = 1.0;
    for( auto it = sm.begin(); it != sm.end(); ++it ) r *= it->second.p();
    double n = double( 1 ) / sm.size();
    return std::pow( r, n );
}

} //namespace

#endif
