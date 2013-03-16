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

#include "Serial2Parallel74xx595.h"

// ------------------------------------------------------------------
/** Constructor.
*
* Create a new serial to parallel converter. Use this constructor if 
* the clear pin has been made available to us.
*
* @param[in] bits Number of bits to shift out to the device.
* @param[in] data Pin number for data signal.
* @param[in] clock Pin number for clock signal.
* @param[in] latch Pin number for latch signal.
* @param[in] clear Pin number for clear signal.
*/

Serial2Parallel74xx595::
Serial2Parallel74xx595 (int bits, int data, int clock, int latch, int clr)
  : Serial2Parallel (bits, data, clock, latch),
    m_clearPin(clr)
{
  pinMode (m_clearPin, OUTPUT);
  
  digitalWrite(m_clearPin, 1);	
}


// ------------------------------------------------------------------
/** Clear shift register.
 *
 *
 */

int Serial2Parallel74xx595::
Clear()
{
  if (m_clearPin != -1)
    {
      digitalWrite(m_latchPin, 0);
      digitalWrite(m_clearPin, 0);
      digitalWrite(m_latchPin, 1);
      digitalWrite(m_clearPin, 1);

      return (0);
    }
  else
    {
      return (-1);
    }
}

