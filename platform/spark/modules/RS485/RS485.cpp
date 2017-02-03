/*
 * Copyright 2017 BrewPi/Elco Jacobs.
 *
 * This file is part of BrewPi.
 *
 * BrewPi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BrewPi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BrewPi.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "RS485.h"

uint16_t RS485::readLn(char * result, const uint16_t maxLen, const uint16_t timeout){
    uint16_t timer = 0;
    uint16_t len = 0;
    while(timer < timeout){
        int16_t inByte = read();
        if(inByte != -1){
            result[len] = inByte;
            timer = 0;
            len++;
            if(inByte == '\n' || len >= maxLen - 1){ // leave space for null termination
                break;
            }
        }
        else{
            timer++;
            delay(1);
        }
    }
    result[len+1] = 0; // null terminate string
    return len;
}

RS485 rs485;
