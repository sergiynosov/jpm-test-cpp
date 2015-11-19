#ifndef __STOCK_TEST_H__
#define __STOCK_TEST_H__

#include "stock_algorithm.h"

namespace stock
{

void populate_stock_map_data( stock_map& sm );
void populate_operations( operation_storage& operations );

void test_divident_yield( const stock_map& sm );
void test_PE_ratio( const stock_map& sm );
void test_VWSP( const operation_storage& operations );
void test_geometric_mean( const stock_map& sm );

} //namespace

#endif
