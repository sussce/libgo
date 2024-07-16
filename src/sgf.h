#ifndef _SGF_H_
#define _SGF_H_

#include "predef.h"

/* ffff ffff ffff ffff ffff ffff ffff ffff */

#define root_t 0x1u
#define setup_t 0x2u
#define ginfo_t 0x4u
#define move_t 0x8u

#define number_t 0x100u
#define real_t 0x200u
/* #define list */
/* #define compose */
/* #define compress */

#define black
#define white

#define uid_mask 0b11111111111100000000000000000000
#define uid_bit  20
#define uid_bits 12
#define UID(tkn) (((tkn) & uid_mask) >> uid_bit)

#endif /* _SGF_H_ */
