/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-2017
 * (c) NXP Semiconductors 2013-2017
 * Linker script memory definitions
 * Created from LinkMemoryTemplate
 * By LPCXpresso v7.8.0 [Build 426] [2015-05-28]  on Thu Nov 30 14:10:54 GMT 2017)
*/

MEMORY
{
  /* Define each memory region */
  MFlash512 (rx) : ORIGIN = 0x0, LENGTH = 0x2000 /* 8K bytes */
  /**** NOTE: MFlash512 (512k) restricted to 8k by license type ****/ 
  RamLoc32 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x8000 /* 32K bytes */
  RamAHB32 (rwx) : ORIGIN = 0x2007c000, LENGTH = 0x8000 /* 32K bytes */


}
  /* Define a symbol for the top of each memory region */
  __top_MFlash512 = 0x0 + 0x80000;
  __top_RamLoc32 = 0x10000000 + 0x8000;
  __top_RamAHB32 = 0x2007c000 + 0x8000;



