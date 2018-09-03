#include "TestHarness.h"
#include "CH05.hpp"

using namespace BitManipulation;

TEST( _4bit1, Solution_5_1 )
{
    int N = 8; // 1000
    int M = 4; // 0100
    
               // 3210
    int i = 0; //    i
    int j = 3; // j
    
    Solution_5_1 solution;
    solution.insertMintoN( M, N, i, j);
    
    CHECK( N == 4 ); // 0100
}

TEST( _4bit2, Solution_5_1 )
{
    int N = 128; // 1000 0000
    int M = 4;   // 0000 0100
    
                 // 7654 3210
    int i = 4;   //    i
    int j = 6;   //  j
    
    Solution_5_1 solution;
    solution.insertMintoN( M, N, i, j);
    
    CHECK( N == 128 + 64 ); // 1100 0000
}

TEST( powerOfTwoPositiveNumbers, Solution_5_5 )
{
    Solution_5_5 solution;
    CHECK( solution.isPowerOfTwo( 1 ) );
    CHECK( solution.isPowerOfTwo( 2 ) );
    CHECK( solution.isPowerOfTwo( 4 ) );
    CHECK( solution.isPowerOfTwo( 8 ) );
    CHECK( solution.isPowerOfTwo( 16 ) );
    CHECK( solution.isPowerOfTwo( 32 ) );
    CHECK( solution.isPowerOfTwo( 64 ) );
}
