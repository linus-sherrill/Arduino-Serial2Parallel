// ----------------------------------------------------------
// The Design Works
//
// For Arduino project.
//
// Class for shifting data out to 74xx595 group of
// chips.
//
// $Id:  $
// -----------------------------------------------------------

#include "Serial2ParallelOE.h"

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

Serial2ParallelOE::
Serial2ParallelOE (int bits, int data, int clock, int latch)
  : Serial2Parallel(bits, data, clock, latch), 
    m_enablePin(-1)
{
}



// ------------------------------------------------------------------
/** Constructor.
*
* Create a new serial to parallel converter. Use this constructor if 
* the enable pin has been made available to us.
*
* This constructor disables the output, so you must enable it
* if you want any output to display.
*
* @param[in] bits Number of bits to shift out to the device.
* @param[in] data Pin number for data signal.
* @param[in] clock Pin number for clock signal.
* @param[in] latch Pin number for latch signal.
* @param[in] enab Pin number for clear signal.
*/

Serial2ParallelOE::
Serial2ParallelOE (int bits, int data, int clock, int latch, int enab)
  : Serial2Parallel (bits, data, clock, latch),
    m_enablePin(enab)
{
  pinMode (m_enablePin, OUTPUT);
  
  DisableOutput();	
}


// ------------------------------------------------------------------
/** Enable output.
 *
 *
 */

void Serial2ParallelOE::
EnableOutput()
{
  if (m_enablePin != -1)
    {
      digitalWrite(m_enablePin, 0);
    }
}


// ------------------------------------------------------------------
/** Disable output.
 *
 *
 */

void Serial2ParallelOE::
DisableOutput()
{
  if (m_enablePin != -1)
    {
      digitalWrite(m_enablePin, 1);
    }
}


// ------------------------------------------------------------------
/** Shift out data using output enables.
 *
 *
 */
void Serial2ParallelOE::
ShiftOutOC(char const* buffer)
{
    DisableOutput();
    ShiftOut(buffer);
    EnableOutput();
}


