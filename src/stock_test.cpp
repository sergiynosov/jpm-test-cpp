
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "stock_test.h"


std::vector<std::string> generate_test_symbols()
{
    std::vector<std::string> test_symbols = { "TEA", "POP", "ALE", "GIN", "JOE", "XXX" };
    return test_symbols;
}

std::vector<int> generate_test_price( int num = 5, bool rnd =false )
{
    std::vector<int> test_price( num );
    if( rnd ) std::srand( std::time( 0 ) );
    std::generate( test_price.begin(), test_price.end(), [](){ return std::rand() % 100 + 1; } );
    return test_price;
}


void stock::populate_stock_map_data( stock::stock_map& sm )
{
    sm.insert( std::make_pair<stock_key_type,stock_data_type>( "TEA", stock_data_type(  0, 100 ) ) );
    sm.insert( std::make_pair<stock_key_type,stock_data_type>( "POP", stock_data_type(  8, 100 ) ) );
    sm.insert( std::make_pair<stock_key_type,stock_data_type>( "ALE", stock_data_type( 23,  60 ) ) );
    sm.insert( std::make_pair<stock_key_type,stock_data_type>( "GIN", stock_data_type(  8, 100, 2, stock_data_type::PREFERRED ) ) );
    sm.insert( std::make_pair<stock_key_type,stock_data_type>( "JOE", stock_data_type( 13, 250 ) ) );

    std::cout << "GBCE data:" << std::endl;
    std::cout << sm << std::endl;
}

void stock::populate_operations( stock::operation_storage& operations )
{
    std::vector<std::string>&& test_symbols = generate_test_symbols();
    std::vector<int>&& test_price = generate_test_price();

    auto op_time = std::chrono::system_clock::now() - std::chrono::minutes( 20 );
    for( int i = 0; i < 10; ++i )
    {
        for( auto s : test_symbols )
        {
            for( int p : test_price )
            {
                int q = std::rand() % 10 + 1;
                stock_operation_type::indicator ind = i % 2 ? stock_operation_type::BUY : stock_operation_type::SELL;
                operations.push_back( stock_operation_type( s, p, q, ind, op_time ) );
            }
        }
        op_time += std::chrono::seconds( 60 );
    }

    std::cout << "Trade data:" << std::endl;
    std::cout << operations << std::endl;
}


void stock::test_divident_yield( const stock::stock_map& sm )
{
    std::vector<std::string>&& test_symbols = generate_test_symbols();
    std::vector<int>&& test_price = generate_test_price();

    try
    {
        for( auto s : test_symbols )
        {
            for( int p : test_price )
            {
                double y = calc_divident_yield( sm, s, p );

                std::cout << "stock symbol = [" << s << "], ";
                std::cout << "price = " << std::setw(3) << p << "p, ";
                std::cout << "divident yield = " << std::fixed << std::setprecision(3) << y << std::endl;
            }
        }
    }
    catch( stock_exception& e )
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    catch( ... )
    {
        std::cerr << "ERROR: unknown" << std::endl;
    }
    std::cout << std::endl;
}

void stock::test_PE_ratio( const stock::stock_map& sm )
{
    std::vector<std::string>&& test_symbols = generate_test_symbols();
    std::vector<int>&& test_price = generate_test_price();

    try
    {
        for( auto s : test_symbols )
        {
            for( int p : test_price )
            {
                double pe = calc_PE_ratio( sm, s, p );

                std::cout << "stock symbol = [" << s << "], ";
                std::cout << "price = " << std::setw(3) << p << "p, ";
                std::cout << "P/E Ratio = " << std::fixed << std::setw(6) << std::setprecision(3) << pe << std::endl;
            }
        }
    }
    catch( stock_exception& e )
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    catch( ... )
    {
        std::cerr << "ERROR: unknown" << std::endl;
    }
    std::cout << std::endl;
}

void stock::test_VWSP( const stock::operation_storage& operations )
{
    try
    {
        double vwsp = calc_VWSP( operations, std::chrono::minutes( 15 ) );
        std::cout << "Volume Weighted Stock Price = " << vwsp << std::endl;
    }
    catch( stock_exception& e )
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    catch( ... )
    {
        std::cerr << "ERROR: unknown" << std::endl;
    }
    std::cout << std::endl;
}

void stock::test_geometric_mean( const stock::stock_map& sm )
{
    try
    {
        double gm = calc_geometric_mean( sm );
        std::cout << "GBCE All Share Index = " << gm << std::endl;
    }
    catch( stock_exception& e )
    {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    catch( ... )
    {
        std::cerr << "ERROR: unknown" << std::endl;
    }
    std::cout << std::endl;
}
