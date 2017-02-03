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

#pragma once
#include "platform.h"
#include "Board.h"
#include <stdint.h>

class RS485 {
public:
    RS485() = default;
    ~RS485() = default;
    /**
     * Initialize the RS485 transceiver.
     */
    static inline void init(){
        Serial1.begin(57600);
        // Serial1.halfduplex(true);
    }

    /**
     * Set the transceiver in receive mode
     */
    static inline void receiveMode(){
        digitalWrite(PIN_RS485_TX_EN, LOW);
        delay(1);
    }

    /**
     * Set the transceiver in send mode
     */
    static inline void sendMode(){
        digitalWrite(PIN_RS485_TX_EN, HIGH);
        delay(1);
    }

    /**
     * Read a single character
     */
    static inline ssize_t read(){
        return Serial1.read();
    }

    /**
     * Write a single character
     */
    static inline ssize_t write(int c){
        sendMode();
        ssize_t written = Serial1.write(c);
        Serial1.flush(); // wait for outgoing serial data to complete
        receiveMode();
        return written;
    }

    /**
     * Send a string
     */
    static void print(const char * s){
        sendMode();
        Serial1.print(s);
        Serial1.flush(); // wait for outgoing serial data to complete
        receiveMode();
    }

    /**
     * Get number of available characters
     */
    static inline int available(){
        return Serial1.available();
    }

    static uint16_t readLn(char * result, const uint16_t maxLen, const uint16_t timeout);

};

extern RS485 rs485;
