#ifndef _SGF_H_
#define _SGF_H_

#include "predef.h"

/* EBNF def
prop     : id value+
id       : UcLetter+
value    : [cvtype]

UcLetter : A..Z
cvtype   : vtype | compose

compose  : vtype : vtype
vtype    : none |
           number | real |
           double | color |
           simple | text |
           point | move | stone

list of  : value+
elist of : value+ | none */

/* EBNF def: vtype
real   : float

double : 1 | 2
color  : B | W

text   : formatted string. whitespace other than linebreak are converted to space (e.g. no tab, vertical tab, ..).
simple : simple string. whitespace other than space are converted to space, i.e. no newline.

point  :
move   :
stone  :

list of point : list of (point | (point : point)) */

/* flag, 32-bits
   uuuu uuuu uuuu vvvv vvvv vvvv tttt tttt */

/* markup anno */

/* type */
#define root 0x1u
#define setup 0x2u
#define ginfo 0x4u
#define move 0x8u

/* vtype */
#define number 0x100u
#define real

#define double
#define color

#define text
#define simple

#define point

#define list
#define compose
#define weak
#define compress

#define none

/*
HA[4]                                ginfo (Go)     number                     number
KM[6.5]                              ginfo (Go)     real                       real

GB[1] [2]                            -              double                     double
PL[B] [W]                            setup          color                      color

C[comment]                           -              text                       text
BR[9d]                               ginfo          simple                     simple

B[dd]                                move           move                       move

KO[]                                 move           none                       none

SZ[9] [9:9]                          root           number | number : number   compose|weak
AP[goban:1.0]                        root           simple : simple            compose    
FG[n:diagram]                        -              none | number : simple     none|compose|weak

AW[ab][ac][ad][nn] [ab:ad][nn]       setup          list of stone              compose|weak|compress
AE[ab][ac][ad][nn] [ab:ad][nn]       setup          list of point              compose|weak
VW[ab][ac][ad][nn] [ab:ad][nn] []    - (inherit)    elist of point             none|compose|weak

//markup
AR[aa:bb][cc:dd]                     -              list of point : point      compose
LN[aa:bb][cc:dd]                     -              list of point : point      compose
LB[aa:A][bb:B]                       -              list of point : simple     compose
CR   Circle          -                list of point
*DD  Dim points      - (inherit)      elist of point
MA   Mark            -                list of point
SL   Selected        -                list of point
*SQ  Square          -                list of point
TR   Triangle        -                list of point

//move anno
BM   Bad move        move             double
TE   Good move       move             double
DO   Doubtful        move             none
IT   Interesting     move             none

//node anno
GB   Good for Black  -                double
GW   Good for White  -                double
DM   Even position   -                double
HO   Hotspot         -                double
UC   Unclear pos     -                double
C    Comment         -                text
N    Nodename        -                simpletext
V    Value           -                real

*/

#define black
#define white

/* uid */
#define uid_mask 0xfff00000
#define uid_bit  20
#define uid_bits 12
#define UID(tkn) (((tkn) & uid_mask) >> uid_bit)

#define anno
#define markup

enum {
  ar_m, cr_m, dd_m, lb_m,
  ln_m, ma_m, sl_m, sq_m, tr_m
};

enum {
  bm_an, te_an, do_an, it_an,
  gb_an, gw_an, dm_an, ho_an,
  uc_an, c_an, n_an, v_an
};

int check_*(uint token);

int check_root();
int check_number_real();
int check_double_color();
int check_text_simple();
int check_point_move_stone_pos();
int check_compose();
int check_none();

int do_move();
int do_anno();
int do_markup(int arg);
int do_view();

#endif /* _SGF_H_ */
