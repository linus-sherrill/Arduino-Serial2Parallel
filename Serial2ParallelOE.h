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


#if !defined Serial2ParallelOE_H_
#define Serial2ParallelOE_H_

#include <Serial2Parallel.h>

// -----------------------------------------------------------
/** Serial to parallel converter.
 *
 * This class represents a serial to parallel converter that
 * supports output enable signal.
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

class Serial2ParallelOE
  : public Serial2Parallel
{
public:
  // -- CONSTRUCTORS --
  Serial2ParallelOE (int bits, int data, int clock, int latch);
  Serial2ParallelOE (int bits, int data, int clock, int latch, int enable);
  // ~Serial2ParallelOE () { }
  
  // -- ACCESSORS  --
  
  
  // -- MANIPULATORS --
  void EnableOutput();
  void DisableOutput();
  void ShiftOutOC(char const* buffer);
    
protected:
  
  
private:
  int m_enablePin;
};


#endif




