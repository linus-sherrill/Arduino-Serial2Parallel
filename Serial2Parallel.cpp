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

$Id:  $
----------------------------------------------------------- */


#include "Serial2Parallel.h"


// ------------------------------------------------------------------
/** Constructor.
*
* Create a new serial to parallel converter.
*
* @param[in] bits Number of bits to shift out to the device.
* @param[in] data Pin number for data signal.
* @param[in] clock Pin number for clock signal.
* @param[in] latch Pin number for latch signal.
*/

Serial2Parallel::
Serial2Parallel (int bits, int data, int clock, int latch)
  : m_dataPin(data),
    m_clockPin(clock),
    m_latchPin(latch),
    m_bitCount (bits)
{
	// Set pin modes
	pinMode (m_dataPin, OUTPUT);
	pinMode (m_clockPin, OUTPUT);
	pinMode (m_latchPin, OUTPUT);
	
	digitalWrite(m_dataPin, LOW);
	digitalWrite(m_clockPin, LOW);

	digitalWrite(m_latchPin, HIGH);
}


Serial2Parallel::
~Serial2Parallel ()
{
	
}


// ------------------------------------------------------------------
/** Shift data out to device.
*
* Data bit clocks in on rising edge of m_clockPin.
* Contents of shift register transfered to output on rising edge
* of m_latchPin.
*
* If more than 8 bits are configured, then the parameter must
* specify an array of bytes.
*
* @param[in] data_out Address of byte or bytes of data to output.
*/

void Serial2Parallel::
ShiftOut(char const* data_out)
 {
  // This shifts data bits out MSB first, 
  // on the rising edge of the clock,
  // clock idles low

  // internal function setup
  byte pin_state;
  byte local_data = *data_out;

  // clear everything out just in case to
  // prepare shift register for bit shifting
  digitalWrite(m_dataPin, LOW);
  digitalWrite(m_clockPin, LOW);

  // ground latchPin and hold low for as long as you are transmitting
  digitalWrite(m_latchPin, LOW);

  // Write out all the bits
  for (int i = 0; i < m_bitCount; i++)
    {
      digitalWrite(m_clockPin, LOW);

      // Set pin state from MSB
      pin_state = ((local_data & 0x80) != 0);

      // Shift to next bit
      local_data <<= 1;

      // Sets the pin to HIGH or LOW depending on pinState
      digitalWrite(m_dataPin, pin_state);
      
      // register shifts bits on upstroke of clock pin  
      digitalWrite(m_clockPin, HIGH);
      
      // zero the data pin after shift to prevent bleed through
      digitalWrite(m_dataPin, LOW);

      // Check to see if we went across a byte boundary
      if ( (i != 0) && ((i % 8) == 0))
        {
          data_out++; // to next byte
          local_data = *data_out;
        }
    } // end for

  // stop shifting
  digitalWrite(m_clockPin, LOW);

  // return the latch pin high to signal chip that it 
  // no longer needs to listen for information
  digitalWrite(m_latchPin, HIGH);
 }   

