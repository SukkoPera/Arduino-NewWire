/*
  TwoWire.h - TWI/I2C library for Arduino & Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 2012 by Todd Krein (todd@krein.org) to implement repeated starts

  Modified 2020 by SukkoPera (software@sukkology.net) to make it abstract
*/

#ifndef AbstractWire_h
#define AbstractWire_h

#include <inttypes.h>
#include "Stream.h"

class AbstractWire : public Stream
{
  public:
    virtual void begin() = 0;
    virtual void begin(uint8_t) = 0;
    inline void begin(int address) { begin((uint8_t)address); }
    virtual void end() = 0;
    virtual void setClock(uint32_t) = 0;
    virtual void beginTransmission(uint8_t) = 0;
    virtual void beginTransmission(int address) { beginTransmission((uint8_t)address); }
    virtual uint8_t endTransmission(uint8_t sendStop) = 0;
    uint8_t endTransmission() { return endTransmission((uint8_t)true); }
	virtual uint8_t requestFrom(uint8_t address, uint8_t quantity, uint32_t iaddress, uint8_t isize, uint8_t sendStop) = 0;
    inline uint8_t requestFrom(uint8_t address, uint8_t quantity) {
		return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
	}
    inline uint8_t requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop) {
		return requestFrom((uint8_t)address, (uint8_t)quantity, (uint32_t)0, (uint8_t)0, (uint8_t)sendStop);
	}
    inline uint8_t requestFrom(int address, int quantity) {
		return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
	}
    inline uint8_t requestFrom(int address, int quantity, int sendStop) {
		return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
	}
    virtual size_t write(uint8_t) = 0;
    virtual size_t write(const uint8_t *, size_t) = 0;
    virtual int available(void) = 0;
    virtual int read(void) = 0;
    virtual int peek(void) = 0;
    virtual void flush(void) = 0;

    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;
};

#endif

