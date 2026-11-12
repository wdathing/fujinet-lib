/**
 * @brief Read string to s from DriveWire with expected length l
 * @param s pointer to string buffer
 * @param l expected length of string (0-65535 bytes)
 * @return 1 = read successful, 0 = not successful
 */

#include <cmoc.h>
#include <coco.h>
#include "dw.h"

byte dwread(byte *s, int l)
{
    /* See dwwrite: save/restore U and DP across the ROM vector call. */
    asm
    {
        pshs x,y,u,dp
        ldx :s
        ldy :l
#ifdef DRAGON
        jsr [0xF9FE]
#else
        jsr [0xD93F]
#endif
        puls dp,u,y,x
        tfr cc,b
        lsrb
        lsrb
        andb #$01
    }
}
