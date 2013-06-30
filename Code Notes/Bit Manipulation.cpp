//////////////////////////////////////////////////////////////////////////////
//BIT MANIPULATION
//////////////////////////////////////////////////////////////////////////////
/*
--------------------------------------------------------------------
For 8 bits in a byte:
Most values a byte can have: 0 -> (128+64+32+16+8+4+2+1) = 0 -> 255 = 256
Most values a signed byte can have: -128 -> 127 = 256
Lower values for signed due to last bit storing sign

    1   1   1   1   1   1   1   1
    2⁷  2⁶  2⁵  2⁴  2³  2²  2¹  2°
   128  64  32  16  8   4   2   1
--------------------------------------------------------------------*/

//COUNTING IN BINARY
0000    0001    0010    0011    0100    0101    0110    0111    
1000    1001    1010    1011    1100    1101    1110    1111

//BINARY->DECIMAL
1101 = 1x2³ + 1x2² + 0x2¹ + 1x2° = 13

//HEX->DECIMAL
A3F = 10x16² + 3x16¹ + 15x16° = 2623

//HEX->BINARY
0xC2 = binaryC binary2 = 1100 0010 = 11000010

//BINARY->HEX
11000010 = 1100 0010 = 0xC2

//////////////////////////////////////////////////////////////////////////////
//BIT OPERATORS
//////////////////////////////////////////////////////////////////////////////

/*----------------------------------------------------------------------------
~   bit NOT       returns opposite [used on single]   
|   bit OR        if either is 1, returns 1
&   bit AND       both must be 1 to return 1
^   bit XOR       if either is 1, returns 1; if both are 1 returns 0
<<  left shift    moves all bits to the left, drops the last 0 or 1 and adds 0 to the start
>>  right shift   moves all bits to the right, drops the first 0 or 1 and adds 0 to the end

~1 = 0      ~0 = 1
1 & 1 = 1   1 & 0 = 1
1 | 1 = 1   1 | 0 = 1
1 ^ 1 = 0   1 ^ 0 = 1
----------------------------------------------------------------------------*/

//USAGE EXAMPLES
//Operators work on integers/chars
//to use binary numbers, covert them to hex values using table (00000011 = 0000 0011 = 0x03)

//FLIPPING VALUES
unsigned int value = 2;
value = ~value; //value becomes 255-2 = 253

//MASKING BITS (&)
unsigned int value = 00000011 //0x03
unsigned int mask =  00000010
value &= mask  //values becomes 00000010, all bits but mask is turned off

//CHECKING BIT VALUES (&)
unsigned int value = 01100011
unsigned int mask =  00000001
if((value & mask) == mask){ /*bit 0 is turned on*/ }

//TURNING BITS ON (|)
unsigned int value = 00000011
value |= 00000100 //value becomes 00000111, bit 2 is turned on

//TURNING BITS OFF (~)
unsigned int value = 00000011
unsigned int mask =  00000010 //~mask = 11111101
value &= ~mask //value becomes 00000001, bit 1 is turned off, rest remain the same

//TOGGLING BITS (^)
unsigned int value = 00000011
unsigned int mask =  00000001
value ^= mask //value becomes 00000010, bit 0 is toggled
value ^= mask //value becomes 000000011 second time around, bit 0 is toggled again

//MULTIPLYING BY POWERS OF 2 (<<)
unsigned int value = 10000011
value <<= 3 //value becomes 00011000 and shifts bits 3 places 

unsigned int value = 2;
value <<= 3 //value becomes 16, same as value *= 2³ or value *= 8

//DIVIDING BY POWERS OF 2(>>)
unsigned int value = 10000011
value >>= 3 //value becomes 00010000, note, may need to mask as new bits on right aren't always 0
unsigned int value = 16
value >>= 3 //value becomes 2, same as value /= 2³ or value /= 8

//GETTING COLOR COMPONENTS VIA BIT SHIFTING
unsigned int c;
int r = c & 0xFF;
int g = (c>>8) & 0xFF;
int b = (c>>16) & 0xFF;
int a = (c>>24) & 0xFF;

//////////////////////////////////////////////////////////////////////////////
//BIT MASKING
//////////////////////////////////////////////////////////////////////////////

#define BIT(x) (1<<(x)) //does 1 *= 2ˣ
enum MASKS
{
    MASK1 = BIT(0), //value = 1    0x001
    MASK2 = BIT(1), //value = 2    0x002
    MASK3 = BIT(2), //value = 4    0x004
    MASK4 = BIT(4), //value = 8    0x008
    MASK5 = BIT(5), //value = 16   0x010
    MASK6 = BIT(6), //value = 32   0x020
    MASK7 = BIT(7), //value = 64   0x040
    MASK8 = BIT(8), //value = 128  0x080
}
 
//Amount of bytes minimally guaranteed determines amount of bit flags can be stored
unsigned char //Can have 8 (bytes) flags maximum
unsigned short //Can have 16 (bytes) flags maximum
unsigned int //Can have 16 (bytes) flags maximum 
unsigned long //Can have 32 (bytes) flags maximum

//initialise variable
unsigned char value = 0x00;

//include mask1,mask2
value = MASK1 | MASK2;

//turn off a mask
value &= ~MASK1; //turns off mask 1

//add a mask
value |= MASK3; //adds mask 3

//test for masking
if((value & MASK1) == MASK1){ /*mask1 is chosen*/ }


//////////////////////////////////////////////////////////////////////////////
//BIT CONTAINERS
//////////////////////////////////////////////////////////////////////////////

//STATIC BIT ARRAYS
#include <bitset>
bitset<numberOfbits> mb; //creates array with n bits; initialised to false

mybits[i];          //access bit
mybits.size();      //size of array
mybits.any();       //returns true if any bit is set to true
mybits.none();      //returns true if no bits are set to true
mybits.set();       //sets all to true
mybits.set(1);      //set bit 1 to true
mybits.reset();     //sets all to false
mybits.reset(1);    //set bit 1 to false
mybits.flip();      //flips all bits to opposite value
mybits.flip(1);     //flips bit 1 to opposite
mybits.count();     //returns number of true bits
mybits.to_string(); //converts bitset to string
mybits.to_ulong();  //converts bitset to unsigned long