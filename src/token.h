#ifndef __GM1_TOKEN_H__
#define __GM1_TOKEN_H__

#if !defined (__LIB_GO_H_INSIDE__) && !defined (LIBGO_COMPILE)
#error "only libgo.h can be included directly."
#endif

#include "hash.h"

/* [SGF FF[4] - Smart Game Format]
FF[4] property index
This is an alphabetical index to all properties defined in FF[4].
New properties are marked with '*', changed properties are marked with '!'.

   ID   Description     property type    property value */
/* *AP  Application     root             composed simpletext ':' simpletext */
#define AP_TKN 0x7ad22001
/* *CA  Charset         root             simpletext */
#define CA_TKN 0x7d802001
/* FF   Fileformat      root	           number (range: 1-4) */
#define FF_TKN 0x83400101
/* GM   Game            root	           number (range: 1-5,7-16) */
#define GM_TKN 0x85800101
/* *ST  Style           root	           number (range: 0-3) */
#define ST_TKN 0x9bb00101
/* !SZ  Size            root	           (number | composed number ':' number) */
#define SZ_TKN 0x9c140101
/* AB   Add Black       setup            list of stone */
#define AB_TKN 0x79f50002
/* AE   Add Empty       setup            list of point */
#define AE_TKN 0x7a250002
/* AW   Add White       setup            list of stone */
#define AW_TKN 0x7b450002
/* PL   Player to play  setup            color */
#define PL_TKN 0x95c00802
/* AN   Annotation      game-info        simpletext */
#define AN_TKN 0x7ab02004
/* BR   Black rank      game-info        simpletext */
#define BR_TKN 0x7cc02004
/* BT   Black team      game-info        simpletext */
#define BT_TKN 0x7ce02004
/* CP   Copyright       game-info        simpletext */
#define CP_TKN 0x7e702004
/* !DT  Date            game-info        simpletext */
#define DT_TKN 0x80802004
/* EV   Event           game-info        simpletext */
#define EV_TKN 0x82702004
/* GN   Game name       game-info        simpletext */
#define GN_TKN 0x85902004
/* GC   Game comment    game-info        text */
#define GC_TKN 0x84e01004
/* ON   Opening         game-info        simpletext */
#define ON_TKN 0x94102004
/* *OT  Overtime        game-info        simpletext */
#define OT_TKN 0x94702004
/* PB   Player Black    game-info        simpletext */
#define PB_TKN 0x95202004
/* PC   Place           game-info        simpletext */
#define PC_TKN 0x95302004
/* PW   Player White    game-info        simpletext */
#define PW_TKN 0x96702004
/* !RE  Result          game-info        simpletext */
#define RE_TKN 0x98f02004
/* RO   Round           game-info        simpletext */
#define RO_TKN 0x99902004
/* HA   Handicap        game-info (Go)   number */
#define HA_TKN 0x86900104
/* KM   Komi            game-info (Go)   real */
#define KM_TKN 0x8cc00204
/* TB   Territory Black - (Go)           elist of point */
#define TB_TKN 0x9c654000
/* TW   Territory White - (Go)           elist of point */
#define TW_TKN 0x9db54000
/* B    Black           move             move */
#define B_TKN 0x4200008
/* KO   Ko              move             none */
#define KO_TKN 0x8ce04008
/* MN   set move number move             number */
#define MN_TKN 0x90700108
/* W    White           move             move */
#define W_TKN 0x5700008
/* C    Comment         -                text */
#define C_TKN 0x4301010
/* DM   Even position   -                double */
#define DM_TKN 0x80100410
/* GB   Good for Black  -                double */
#define GB_TKN 0x84d00410
/* GW   Good for White  -                double */
#define GW_TKN 0x86200410
/* HO   Hotspot         -                double */
#define HO_TKN 0x87700410
/* N    Nodename        -                simpletext */
#define N_TKN 0x4e02010
/* UC   Unclear pos     -                double */
#define UC_TKN 0x9e400410
/* V    Value           -                real */
#define V_TKN 0x5600210
/* BM   Bad move        move             double */
#define BM_TKN 0x7c700418
/* DO   Doubtful        move             none */
#define DO_TKN 0x80304018
/* IT   Interesting     move             none */
#define IT_TKN 0x89904018
/* TE   Tesuji          move             double */
#define TE_TKN 0x9c900418
/* *AR  Arrow           -                list of composed point ':' point */
#define AR_TKN 0x7af30020
/* CR   Circle          -                list of point */
#define CR_TKN 0x7e950020
/* *DD  Dim points      - (inherit)      elist of point */
#define DD_TKN 0x7f854020
/* !LB  Label           -                list of composed point ':' simpletext */
#define LB_TKN 0x8de32020
/* *LN  Line            -                list of composed point ':' point */
#define LN_TKN 0x8ea30020
/* MA   Mark            -                list of point */
#define MA_TKN 0x8fa50020
/* SL   Selected        -                list of point */
#define SL_TKN 0x9b350020
/* *SQ  Square          -                list of point */
#define SQ_TKN 0x9b850020
/* TR   Triangle        -                list of point */
#define TR_TKN 0x9d650020
/* BL   Black time left move             real */
#define BL_TKN 0x7c600208
/* OB   OtStones Black  move             number */
#define OB_TKN 0x93500108
/* OW   OtStones White  move             number */
#define OW_TKN 0x94a00108
/* WL   White time left move             real */
#define WL_TKN 0xa2700208
/* !FG  Figure          -                none | composed number ":" simpletext */
#define FG_TKN 0x83546100
/* *PM  Print move mode - (inherit)      number */
#define PM_TKN 0x95d00100
/* *VW  View            - (inherit)      elist of point */
#define VW_TKN 0xa1554000

#define UNKNOWN_TKN 0x0

#define TKN_INIT                                         \
  /* root */                                             \
  _(AP) _(CA) _(FF) _(GM) _(ST) _(SZ)                    \
  /* setup */                                            \
  _(AB) _(AE) _(AW) _(PL)                                \
  /* ginfo */                                            \
  _(AN) _(BR) _(BT) _(CP) _(DT) _(EV) _(GN)              \
  _(GC) _(ON) _(OT) _(PB) _(PC) _(PW) _(RE) _(RO)        \
  _(HA) _(KM) _(TB) _(TW)                                \
  /* move */                                             \
  _(B) _(KO) _(MN) _(W)                                  \
  /* node anno*/                                         \
  _(C) _(DM) _(GB) _(GW) _(HO) _(N) _(UC) _(V)           \
  /* move anno */                                        \
  _(BM) _(DO) _(IT) _(TE)                                \
  /* markup */                                           \
  _(AR) _(CR) _(DD) _(LB) _(LN) _(MA) _(SL) _(SQ) _(TR)  \
  /* timing */                                           \
  _(BL) _(OB) _(OW) _(WL)                                \
  /* misc */                                             \
  _(FG) _(PM) _(VW)

int max_bits(ulong n) {
  int c;
  for(c = 0; n; c++, n >>= 1);
  return c;
}

uint tkn_gen(char* id, uint type) {
  uint tkn = 0;
  ulong uid = 0;

  if (!id)
    return 0;
  
  uid = hash(id);
  
  if(max_bits(uid) > uid_bits) {
    tkn = (1 << uid_bit) | type;

    printf("unknown: %s, %ld, 0x%x\n",
           id, uid, tkn);
  }
  else
    tkn = (uid << uid_bit) | type;
  
  return tkn;
}

void tkn_init() {
  hprop_init();
#define _(token) hprop_add(#token, token##_TKN)
  TKN_INIT
#undef _
}

#endif /* __GM1_TOKEN_H__ */
