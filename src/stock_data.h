#ifndef __STOCK_DATA_H__
#define __STOCK_DATA_H__

#include <string>
#include <map>
#include <iostream>
#include <iomanip>

namespace stock
{

typedef std::string stock_key_type;

class stock_data_type
{
public:
    enum type
    {
        COMMON    = 0,
        PREFERRED = 1
    };

public:
    stock_data_type( int ld, int pv, int fd =-1, type st =COMMON )
        : last_divident( ld )
        , par_value( pv )
        , fixed_divident( fd )
        , stock_type( st )
    {};

    double calc_divident_yield( int price ) const
    {
        double result = 0.0;
        if( stock_type == COMMON ) result = double( last_divident ) / price;
        else result = double( fixed_divident ) / 100 * par_value / price;
        return result;
    };

    double calc_PE_ratio( int price ) const
    {
        double result = 0.0;
        if( last_divident > 0 ) result = double( price ) / last_divident;
        return result;
    };

    int p() const
    {
        return par_value;
    };

    friend std::ostream& operator<<( std::ostream& os, const stock_data_type& data )
    {
        os << "type = [" << ( data.stock_type == PREFERRED ? "PRF" : "CMN" ) << "]";
        os << ", last devident = [" << std::setw(3) << data.last_divident << "]";
        os << ", fixed devident = [" << std::setw(2) << data.fixed_divident << "]";
        os << ", par value = [" << std::setw(3) << data.par_value << "]";
        return os;
    };

private:
    int last_divident = 0;
    int par_value = 0;
    int fixed_divident = -1;
    type stock_type = COMMON;
};


typedef std::map< stock_key_type, stock_data_type > stock_map;


inline std::ostream& operator<<( std::ostream& os, const stock_map& data )
{
    for( auto it : data ) std::cout << "[" << it.first << "]: " << it.second << std::endl;
    return os;
}

} // namespace

#endif
