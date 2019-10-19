/* ----------------------------------------------------------
 The Design Works

For Arduino project.
Class for shifting data out to a group of chips.

Copyright (c) 2009 Linus Sherrill.  All right reserved.

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

----------------------------------------------------------- */


#if !defined Serial2Parallel_H_
#define Serial2Parallel_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include <pins_arduino.h>
#endif

// -----------------------------------------------------------
/** Serial to parallel converter.
 *
 * This class represents a serial to parallel converter that
 * supports 74HC595 or similar devices.
 *
 * When the device is created, the number of bits to convert is
 * specified, in addition to the pin numbers for the control
 * signals.  The number of bits should match the device
 * size. Otherwise, the output patterns will skew.
 *
 * If the number of bits specified is more than 8, the data area
 * specified must be a byte array.
 *
 * The bits are shifted out starting with the MSB of
 * data_area[0] and continue for 8 bits. If more bits are
 * needed, they are taken from data_area[1].
 *
 */

class Serial2Parallel
{
public:
  // -- CONSTRUCTORS --
  Serial2Parallel(int bits, int data, int clock, int latch);
  virtual ~Serial2Parallel();

  // -- ACCESSORS  --


  // -- MANIPULATORS --
  void ShiftOut(char const* data_out);


protected:
  int m_dataPin;
  int m_clockPin;
  int m_latchPin;

 private:
  int m_bitCount;  ///< number of bits to output

};


#endif




