
#include <iostream>
#include "stock_test.h"

using namespace stock;

int main( int argc, char** argv )
{
    stock_map sm;
    populate_stock_map_data( sm );

    operation_storage operations;
    populate_operations( operations );

    test_divident_yield( sm );
    test_PE_ratio( sm );
    test_VWSP( operations );
    test_geometric_mean( sm );

    return 0;
}
