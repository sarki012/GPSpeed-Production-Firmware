/*
 * File:   parse.c
 * Author: eriks
 *
 * Created on May 28, 2020, 8:58 PM
 */

#include <xc.h>
#include <stdio.h>
#include <pic18f4520.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int nmea_speed = 0, decimal_flag = 0, decimal_flag2 = 0;
int average_buffer[5] = {0}; 
int average = 0;


void display_slow(int);
void display_fast(int);
int parse(char *nmea_string)
{
    int fix_status = 0;
    for(int b = 0; b < 73; b++)
    {
        nmea_string++;
        if(*nmea_string == 'W')
        {
            nmea_string++;
            nmea_string++;
            switch (*nmea_string)
            {
                case '0': nmea_speed = 0;
                break;
                case '1': nmea_speed = 100;
                break;
                case '2': nmea_speed = 200;
                break;
                case '3': nmea_speed = 300;
                break;
                case '4': nmea_speed = 400;
                break;
                case '5': nmea_speed = 500;
                break;
                case '6': nmea_speed = 600;
                break;
                case '7': nmea_speed = 700;
                break;
                case '8': nmea_speed = 800;
                break;
                case '9': nmea_speed = 900;
                break;
                default : nmea_speed = 0;
                break;
            } 
            nmea_string++;
            if(*nmea_string == '.')
            {
                nmea_string++;
                decimal_flag = 1;
            }
            switch (*nmea_string)
            {

                case '0': nmea_speed += 0;
                break;
                case '1': nmea_speed += 10;
                break;
                case '2': nmea_speed += 20;
                break;
                case '3': nmea_speed += 30;
                break;
                case '4': nmea_speed += 40;
                break;
                case '5': nmea_speed += 50;
                break;
                case '6': nmea_speed += 60;
                break;
                case '7': nmea_speed += 70;
                break;
                case '8': nmea_speed += 80;
                break;
                case '9': nmea_speed += 90;
                break;
                default : nmea_speed += 0;
                break;
            } 
            nmea_string++;
            if(*nmea_string == '.')
            {
                nmea_string++;
                decimal_flag2 = 1;
            }
            switch (*nmea_string)
            {

                case '0': nmea_speed += 0;
                break;
                case '1': nmea_speed += 1;
                break;
                case '2': nmea_speed += 2;
                break;
                case '3': nmea_speed += 3;
                break;
                case '4': nmea_speed += 4;
                break;
                case '5': nmea_speed += 5;
                break;
                case '6': nmea_speed += 6;
                break;
                case '7': nmea_speed += 7;
                break;
                case '8': nmea_speed += 8;
                break;
                case '9': nmea_speed += 9;
                break;
                default : nmea_speed += 0;
                break;
            } 
            nmea_speed = (int)(nmea_speed * 1.15076);   //knots to mph
            average_buffer[0] = nmea_speed;
            average_buffer[4] = average_buffer[3];
            average_buffer[3] = average_buffer[2];
            average_buffer[2] = average_buffer[1];
            average_buffer[1] = average_buffer[0];
            average = (average_buffer[0] + average_buffer[1] + average_buffer[2] + average_buffer[3] + average_buffer[4]) / 5;
            if(decimal_flag)
            {
                fix_status = 1;
                if (average <= 50)
                {
                    display_slow(0);
                }
                else
                {
                    display_slow(average);   //show digits with decimal point
                }
                decimal_flag = 0;
            }
            else if(decimal_flag2)
            {
                display_fast(average);   //show digits
                decimal_flag2 = 0;
                fix_status = 10;
            }
            return fix_status;
        }
    }
    return fix_status;
}