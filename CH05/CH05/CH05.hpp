#include <iostream>

using namespace std;

namespace BitManipulation
{

    int getBit( const int number, const int index )
    {
        return ( number & ( 1 << index ) ) == 0  ?  0 : 1;
    }
    
    int setBit( const int number, const int index )
    {
        return number | ( 1 << index );
    }
    
    int clearBit( const int number, const int index )
    {
        return number & ~( 1 << index );
    }

    /*

    5.1 Insertion: you are given two 32-bit numbers, N and M, and two bit positions,
    i and j.  Write a method to insert M into N such that M starts at bit j and ends at bit i.
    You can assume that the bits j through i have neough space to fit all of M.  That is, if
    M = 10011, you can assume that there are at least 5 bits between j and i.  You would not,
    fo example, have j = 3 and i = 2, because M could no fully fit between bit 3 and bit 2.

    */
    class Solution_5_1
    {
    public:
        
        void insertMintoN ( const int M, int& N, const int i, const int j ) const noexcept
        {
            for ( auto bitPos = i; bitPos <=j; ++bitPos)
            {
                auto bitM = getBit( M, bitPos - i );
                auto bitN = getBit( N, bitPos );
                
                if ( bitM < bitN )
                {
                    N = clearBit( N, bitPos );
                }
                if ( bitM > bitN )
                {
                    N = setBit( N, bitPos );
                }
            }
        }
    };

    /*

    5.2 Binary to String: Given a real number between 0 and 1 (e.g., 0.72) that is passed as a double
    print the binary representation.  If the number cannot be represented accurated in binary with at most
    32 characters, print "ERROR".

    Q: what does a non-integer number in binary look like?  By analogy to a decimal number,
    the binary number 0.101 would look like:

        0.101 = 1 * (1/2)  +  0 * (1/4)  +  1 * (1/8)

    */


    /*

    5.3 Flip Bit to Win: You have an integer and you can flip exactly one bit from a 0 to a 1.  Write code to
    find the length of the longest sequence of 1s you could create.

    EXAMPLE:

    Input:    1775   ( 11011101111 )
    Output:   8

    */


    /*

    5.4 Next Number: Given a positive integer, print the next smallest and the next largest number that
    have the same number of 1 bits in their binary representation

    */


    /*

    5.5 Debugger: Explain what the following code does: ( N & (N-1) ) == 0

    Answer: this ensures that exactly one bit is set ( i.e. N is a power of 2 )

    */
    class Solution_5_5
    {
    public:
        
        bool isPowerOfTwo ( const int N ) const noexcept
        {
            return ( N & (N-1) ) == 0;
        }
    };


    /*

    5.6 Conversion: Write a function to determine the number of bits you would need to flip to convert
    integer A to integer B
    
    EXAMPLE
    
    Input:    29 ( 11101 ),   15 ( 01111 )
    Output:   2
    
    */
    
    
    /*
    
    5.7 Pairwise Swap: Write a program to swap odd and even bits in an integer
    with as few instructions as possible.  (e.g., bit 0 and bit 1 are swapped,
                                                  bit 2 and bit 3 are swapped, etc )
    */
    
    
    /*
    
    5.8 Draw Line: A monochrome screen is stored as a single array of bytes, allowing eight consecutive
    pixels to be stored in one byte.  The screen has width w, where w is divisible by 8 ( that is, no byte
    will be split across rows ).  The height of the screen, of course, can be derived from the length
    of the array and the width.  Implement a function that draws a horizontal line from (x1, y) to (x2,y).
    The method signature should look something like:
    
    drawLine(byte[] screen, int width, int x1, int x2, int y)
    
    */
    
    
    /*
    
    
    
    */
    

} // namespace BitManipulation
