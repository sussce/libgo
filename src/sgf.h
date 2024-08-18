#ifndef _SGF_H_
#define _SGF_H_

/* EBNF
prop     : id value+
id       : UcLetter+
value    : [cvtype]

UcLetter : A..Z
cvtype   : vtype | compose

compose  : vtype : vtype
vtype    : none |
           number | real |
           double | color |
           text | simple |
           point | move | stone

list of  : value+
elist of : value+ | none

real   : float
double : 1 | 2
color  : B | W
text   : formatted string. whitespace other than linebreak are converted to space (e.g. no tab, vertical tab, ..).
simple : simple string. whitespace other than space are converted to space, i.e. no newline.

point  :
move   :
stone  :

list of point : list of (point | (point : point)) */

/* token, 32-bits
   uuuu uuuu uuuu vvvv vvvv vvvv tttt tttt */

/* type */
#define ROOT 0x1u
#define SETUP 0x2u
#define GINFO 0x4u
#define MOVE 0x8u
#define ANNO 0x10u
#define MARKUP 0x20u

/* vtype */
#define NUMBER 0x100u
#define REAL 0x200u
#define DOUBLE 0x400u
#define COLOR 0x800u
#define TEXT 0x1000u
#define SIMPLE 0x2000u
#define NONE 0x4000u
#define POINT 0x8000u

#define LIST 0x10000u
#define COMPOSE 0x20000u
#define WEAK 0x40000u

#define CLIST LIST|WEAK
#define ELIST LIST|WEAK|NONE

/*
FF[4]                                root	          number (range: 1-4)        root|number
HA[4]                                ginfo (Go)     number                     ginfo|number
KM[6.5]                              ginfo (Go)     real                       ginfo|real
PL[B] [W]                            setup          color                      color
BR[9d]                               ginfo          simple                     ginfo|simple
MN[10]                               move           number                     move|number
KO[]                                 move           none                       move|none

B[dd]                                move           move                       
W[dd]                                move           move                       

SZ[9] [9:9]                          root           number | number : number   root|weak|number
AP[goban:1.0]                        root           simple : simple            root|compose|simple
FG[n:diagram]                        -              none | number : simple     weak|number|simple|none

AW[ab][ac][ad][nn] [ab:ad][nn]       setup          list of stone              setup|list|weak
AE[ab][ac][ad][nn] [ab:ad][nn]       setup          list of point              setup|list|weak
VW[ab][ac][ad][nn] [ab:ad][nn] []    - (inherit)    elist of point             list|weak|none

//markup
AR[aa:bb][cc:dd]                     -              list of point : point      markup|list|compose
LN[aa:bb][cc:dd]                     -              list of point : point      markup|list|compose
LB[aa:A][bb:B]                       -              list of point : simple     markup|list|compose|simple
CR   Circle                          -              list of point              markup|list|weak
*DD  Dim points                      - (inherit)    elist of point             markup|list|weak|none
MA   Mark                            -              list of point              markup|list|weak
SL   Selected                        -              list of point              markup|list|weak
*SQ  Square                          -              list of point              markup|list|weak
TR   Triangle                        -              list of point              markup|list|weak

//move anno
BM   Bad move                        move           double                     move|anno|double
TE   Good move                       move           double                     move|anno|double
DO   Doubtful                        move           none                       move|anno|none
IT   Interesting                     move           none                       move|anno|none

//node anno
GB   Good for Black                  -              double                     anno|double
GW   Good for White                  -              double                     anno|double
DM   Even position                   -              double                     anno|double
HO   Hotspot                         -              double                     anno|double
UC   Unclear pos                     -              double                     anno|double
C    Comment                         -              text                       anno|text
N    Nodename                        -              simpletext                 anno|simple
V    Value                           -              real                       anno|real
*/

/* uid */
#define uid_mask 0xfff00000
#define uid_bit  20
#define uid_bits 12
#define UID(tkn) (((tkn) & uid_mask) >> uid_bit)

#define EMPTY
#define BLACK
#define WHITE

enum _markup {
  ar_m, cr_m, dd_m, lb_m,
  ln_m, ma_m, sl_m, sq_m, tr_m
};

enum _annotation {
  bm_an, te_an, do_an, it_an,
  gb_an, gw_an, dm_an, ho_an,
  uc_an, c_an, n_an, v_an
};

struct _ {
  int sz;
  char* ru;
  float km;
  int ha;
  char* re;
  char* pb;
  char* pw;
};

struct _ {
  int sz;
  uchar board[];
};

struct _ {
  Node* root;
  Node* curr;
};

int check_*(uint token);
int load_header(struct _*, Node* node);
int next_move();

#endif /* _SGF_H_ */
