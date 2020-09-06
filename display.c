/*
 * File:   display.c
 * Author: eriks
 *
 * Created on July 28, 2020, 1:03 PM
 */

#include <xc.h>
#include <stdio.h>
#include <pic18f4520.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*
*RD4 = ID3 RD3 = ID2 RD2 = ID1 RD1 = ID0 RD0 = DP         
*/
#define ZERO_DECIMAL 0b000000000
#define ONE_DECIMAL 0b00000010
#define TWO_DECIMAL 0b00000100
#define THREE_DECIMAL 0b00000110
#define FOUR_DECIMAL 0b00001000
#define FIVE_DECIMAL 0b000001010
#define SIX_DECIMAL 0b000001100
#define SEVEN_DECIMAL 0b000001110
#define EIGHT_DECIMAL 0b000010000
#define NINE_DECIMAL 0b000010010

#define ZERO 0b00000001
#define ONE 0b00000011
#define TWO 0b00000101
#define THREE 0b00000111
#define FOUR 0b00001001
#define FIVE 0b00001011
#define SIX 0b00001101
#define SEVEN 0b00001111
#define EIGHT 0b00010001
#define NINE 0b00010011
#define BLANK 0b00011111

/*
 * DA0 = RA0 DA1 = RA1 DA2 = RA2
 * D1  D2  D3  D4
 * 8 . 8 . 8 . 8
 */
#define DIGIT1 0b00000000
#define DIGIT2 0b00000001
#define DIGIT3 0b00000010
#define DIGIT4 0b00000011

void delay2(void);
void display_slow(int display_speed)
{
    int display_digit4 = display_speed % 10;
    int display_digit3 = ((int)(display_speed / 10)) % 10;
    int display_digit2 = ((int)(display_speed / 100));
    LATEbits.LATE1 = 0;         //Toggle Write
    LATA = DIGIT1;              //Right digit
    LATD = BLANK;
    delay2();
    LATEbits.LATE1 = 1;         //Toggle Write
    delay2();
    switch (display_digit2)
    {
        case 0:
        LATEbits.LATE1 = 0;         //Toggle Write
        LATA = DIGIT2;              //Right digit
        LATD = ZERO_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;         //Toggle Write
        delay2();
        break;
        case 1:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = ONE_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 2:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = TWO_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 3:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = THREE_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 4:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = FOUR_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 5:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = FIVE_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 6:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = SIX_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 7:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = SEVEN_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        case 8:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = EIGHT_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 9:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = NINE_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        default :
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
    }
    
    switch (display_digit3)
    {
        case 0:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 1:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = ONE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 2:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = TWO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 3:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = THREE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 4:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = FOUR;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 5:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = FIVE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 6:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = SIX;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 7:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = SEVEN;
        delay2();
        LATEbits.LATE1 = 1; 
        delay2();
        break;
        case 8:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = EIGHT;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        case 9:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = NINE;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        default :
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
    }
    LATEbits.LATE1 = 0;  
    LATA = DIGIT4;            
    LATD = BLANK;
    delay2();
    LATEbits.LATE1 = 1;  
    delay2();
return;
}

void display_fast(int display_speed)
{
    int display_digit4 = display_speed % 10;
    int display_digit3 = ((int)(display_speed / 10)) % 10;
    int display_digit2 = ((int)(display_speed / 100));
    LATEbits.LATE1 = 0;         //Toggle Write
    LATA = DIGIT1;              //Right digit
    LATD = BLANK;
    delay2();
    LATEbits.LATE1 = 1;         //Toggle Write
    delay2();
    switch (display_digit2)
    {
        case 0:
        LATEbits.LATE1 = 0;         //Toggle Write
        LATA = DIGIT2;              //Right digit
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;         //Toggle Write
        delay2();
        break;
        case 1:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = ONE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 2:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = TWO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 3:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = THREE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 4:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = FOUR;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 5:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = FIVE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 6:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = SIX;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 7:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = SEVEN;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        case 8:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = EIGHT;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 9:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = NINE;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        default :
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
    }
    switch (display_digit3)
    {
        case 0:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;
        LATD = ZERO_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 1:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = ONE_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 2:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = TWO_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 3:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = THREE_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 4:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = FOUR_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 5:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = FIVE_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 6:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = SIX_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 7:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = SEVEN_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1; 
        delay2();
        break;
        case 8:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = EIGHT_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        case 9:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = NINE_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        default :
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = ZERO_DECIMAL;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
    }
    switch (display_digit4)
    {
        case 0:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 1:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = ONE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 2:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = TWO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 3:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = THREE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 4:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = FOUR;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 5:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = FIVE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 6:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = SIX;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 7:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = SEVEN;
        delay2();
        LATEbits.LATE1 = 1; 
        delay2();
        break;
        case 8:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = EIGHT;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        case 9:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = NINE;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        default :
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
    }
    return;
}
void display(int display_speed)
{
    int display_digit4 = display_speed % 10;
    int display_digit3 = ((int)(display_speed / 10)) % 10;
    int display_digit2 = ((int)(display_speed / 100)) %10;
    int display_digit1 = (int)(display_speed / 1000);
    switch (display_digit1)
    {
        case 0:
        LATEbits.LATE1 = 0;         //Toggle Write
        LATA = DIGIT1;              //Right digit
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;         //Toggle Write
        delay2();
        break;
        case 1:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT1;            
        LATD = ONE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 2:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT1;            
        LATD = TWO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 3:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT1;            
        LATD = THREE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 4:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT1;            
        LATD = FOUR;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 5:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT1;            
        LATD = FIVE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 6:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT1;            
        LATD = SIX;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 7:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT1;            
        LATD = SEVEN;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        case 8:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT1;            
        LATD = EIGHT;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 9:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT1;            
        LATD = NINE;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        default :
        LATEbits.LATE1 = 0;  
        LATA = DIGIT1;            
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
    }
    switch (display_digit2)
    {
        case 0:
        LATEbits.LATE1 = 0;         //Toggle Write
        LATA = DIGIT2;              //Right digit
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;         //Toggle Write
        delay2();
        break;
        case 1:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = ONE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 2:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = TWO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 3:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = THREE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 4:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = FOUR;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 5:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = FIVE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 6:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = SIX;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 7:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = SEVEN;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        case 8:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = EIGHT;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 9:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = NINE;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        default :
        LATEbits.LATE1 = 0;  
        LATA = DIGIT2;            
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
    }
    switch (display_digit3)
    {
        case 0:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 1:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = ONE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 2:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = TWO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 3:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = THREE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 4:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = FOUR;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 5:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = FIVE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 6:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = SIX;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 7:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = SEVEN;
        delay2();
        LATEbits.LATE1 = 1; 
        delay2();
        break;
        case 8:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = EIGHT;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        case 9:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = NINE;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        default :
        LATEbits.LATE1 = 0;  
        LATA = DIGIT3;            
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
    }
    switch (display_digit4)
    {
        case 0:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 1:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = ONE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 2:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = TWO;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 3:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = THREE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 4:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = FOUR;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 5:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = FIVE;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 6:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = SIX;
        delay2();
        LATEbits.LATE1 = 1;
        delay2();
        break;
        case 7:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = SEVEN;
        delay2();
        LATEbits.LATE1 = 1; 
        delay2();
        break;
        case 8:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = EIGHT;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        case 9:
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = NINE;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
        default :
        LATEbits.LATE1 = 0;  
        LATA = DIGIT4;            
        LATD = ZERO;
        delay2();
        LATEbits.LATE1 = 1;  
        delay2();
        break;
    }
    return;
}
void display_blank(void)
{
    LATEbits.LATE1 = 0;  
    LATA = DIGIT4;            
    LATD = BLANK;
    delay2();
    LATEbits.LATE1 = 1;  
    delay2();
    LATEbits.LATE1 = 0;  
    LATA = DIGIT3;            
    LATD = BLANK;
    delay2();
    LATEbits.LATE1 = 1;  
    delay2();
    LATEbits.LATE1 = 0;
    LATA = DIGIT2;            
    LATD = BLANK;
    delay2();
    LATEbits.LATE1 = 1;  
    delay2();
    LATEbits.LATE1 = 0;
    LATA = DIGIT1;            
    LATD = BLANK;
    delay2();
    LATEbits.LATE1 = 1;  
    delay2();
    LATEbits.LATE1 = 0;
    return;
}
void delay2(void)
{
    for(int h = 0; h < 3; h++);
    return;
}
