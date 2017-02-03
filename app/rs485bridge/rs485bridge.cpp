/*
 * Copyright 2012-2013 BrewPi/Elco Jacobs.
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

#include "Ticks.h"
#include "RS485.h"


SYSTEM_MODE(SEMI_AUTOMATIC);

void setup(void);
void loop (void);

/* Configure the counter and delay timer. The actual type of these will vary depending upon the environment.
 * They are non-virtual to keep code size minimal, so typedefs and preprocessing are used to select the actual compile-time type used. */
TicksImpl ticks = TicksImpl(TICKS_IMPL_CONFIG);
DelayImpl wait = DelayImpl(DELAY_IMPL_CONFIG);

void setup()
{
    boardInit();

    Serial.begin(57600);
    rs485.init();
}


uint32_t UsbReadLn(char * result, const uint16_t maxLen, const uint16_t timeout){
    uint16_t timer = 0;
    uint16_t len = 0;
    while(timer < timeout){
        int16_t inByte = Serial.read();
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

void loop()
{
    if(rs485.available()){
        char line[64];
        uint16_t received = rs485.readLn(line, 64, 10); // read line until \n is received, timeout 10 ms
        if(received > 0){
            Serial.print("Received:\t");
            Serial.print(line);
        }
    }

    if(Serial.available()){
        char line[64];
        uint16_t received = UsbReadLn(line, 64, 10); // read line until \n is received, timeout 10 ms
        if(received > 0){
            Serial.print("Sending:\t");
            Serial.print(line);
            rs485.print(line);
        }
    }
}
