/**
 * @brief Write string at s to DriveWire with length l
 * @param s pointer to string buffer
 * @param l length of string (0-65535 bytes)
 * @return error code
 */

#include <cmoc.h>
#include <coco.h>
#include "dw.h"

byte dwwrite(byte *s, int l)
{
    /* U is the caller's CMOC frame pointer and DP is assumed constant by
     * every direct-addressed global CMOC emits, but the DriveWire ROM
     * vector is not CMOC code and gives no guarantee it leaves either
     * alone. Save and restore both so a clobber in the ROM can't corrupt
     * the caller's stack frame or misdirect its global accesses. */
    asm
    {
        pshs x,y,u,dp
        ldx :s
        ldy :l
#ifdef DRAGON
        jsr [0xFA00]
#else
        jsr [0xD941]
#endif
        tfr cc,d
        puls dp,u,y,x
    }
}
