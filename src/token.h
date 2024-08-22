#ifndef __GM1_TOKEN_H__
#define __GM1_TOKEN_H__

#if !defined (__LIB_GO_H_INSIDE__) && !defined (LIBGO_COMPILATION)
#error "only libgo.h can be included directly."
#endif

#include "hash.h"

/* [SGF FF[4] - Smart Game Format]
FF[4] property index
This is an alphabetical index to all properties defined in FF[4].
New properties are marked with '*', changed properties are marked with '!'.

   ID   Description     property type    property value */
/* *AP  Application     root             composed simpletext ':' simpletext */
#define TKN_AP 0x7ad22001
/* *CA  Charset         root             simpletext */
#define TKN_CA 0x7d802001
/* FF   Fileformat      root	           number (range: 1-4) */
#define TKN_FF 0x83400101
/* GM   Game            root	           number (range: 1-5,7-16) */
#define TKN_GM 0x85800101
/* *ST  Style           root	           number (range: 0-3) */
#define TKN_ST 0x9bb00101
/* !SZ  Size            root	           (number | composed number ':' number) */
#define TKN_SZ 0x9c140101
/* AB   Add Black       setup            list of stone */
#define TKN_AB 0x79f50002
/* AE   Add Empty       setup            list of point */
#define TKN_AE 0x7a250002
/* AW   Add White       setup            list of stone */
#define TKN_AW 0x7b450002
/* PL   Player to play  setup            color */
#define TKN_PL 0x95c00802
/* AN   Annotation      game-info        simpletext */
#define TKN_AN 0x7ab02004
/* BR   Black rank      game-info        simpletext */
#define TKN_BR 0x7cc02004
/* BT   Black team      game-info        simpletext */
#define TKN_BT 0x7ce02004
/* CP   Copyright       game-info        simpletext */
#define TKN_CP 0x7e702004
/* !DT  Date            game-info        simpletext */
#define TKN_DT 0x80802004
/* EV   Event           game-info        simpletext */
#define TKN_EV 0x82702004
/* GN   Game name       game-info        simpletext */
#define TKN_GN 0x85902004
/* GC   Game comment    game-info        text */
#define TKN_GC 0x84e01004
/* ON   Opening         game-info        simpletext */
#define TKN_ON 0x94102004
/* *OT  Overtime        game-info        simpletext */
#define TKN_OT 0x94702004
/* PB   Player Black    game-info        simpletext */
#define TKN_PB 0x95202004
/* PC   Place           game-info        simpletext */
#define TKN_PC 0x95302004
/* PW   Player White    game-info        simpletext */
#define TKN_PW 0x96702004
/* !RE  Result          game-info        simpletext */
#define TKN_RE 0x98f02004
/* RO   Round           game-info        simpletext */
#define TKN_RO 0x99902004
/* HA   Handicap        game-info (Go)   number */
#define TKN_HA 0x86900104
/* KM   Komi            game-info (Go)   real */
#define TKN_KM 0x8cc00204
/* TB   Territory Black - (Go)           elist of point */
#define TKN_TB 0x9c654000
/* TW   Territory White - (Go)           elist of point */
#define TKN_TW 0x9db54000
/* B    Black           move             move */
#define TKN_B 0x4200008
/* KO   Ko              move             none */
#define TKN_KO 0x8ce04008
/* MN   set move number move             number */
#define TKN_MN 0x90700108
/* W    White           move             move */
#define TKN_W 0x5700008
/* C    Comment         -                text */
#define TKN_C 0x4301010
/* DM   Even position   -                double */
#define TKN_DM 0x80100410
/* GB   Good for Black  -                double */
#define TKN_GB 0x84d00410
/* GW   Good for White  -                double */
#define TKN_GW 0x86200410
/* HO   Hotspot         -                double */
#define TKN_HO 0x87700410
/* N    Nodename        -                simpletext */
#define TKN_N 0x4e02010
/* UC   Unclear pos     -                double */
#define TKN_UC 0x9e400410
/* V    Value           -                real */
#define TKN_V 0x5600210
/* BM   Bad move        move             double */
#define TKN_BM 0x7c700418
/* DO   Doubtful        move             none */
#define TKN_DO 0x80304018
/* IT   Interesting     move             none */
#define TKN_IT 0x89904018
/* TE   Tesuji          move             double */
#define TKN_TE 0x9c900418
/* *AR  Arrow           -                list of composed point ':' point */
#define TKN_AR 0x7af30020
/* CR   Circle          -                list of point */
#define TKN_CR 0x7e950020
/* *DD  Dim points      - (inherit)      elist of point */
#define TKN_DD 0x7f854020
/* !LB  Label           -                list of composed point ':' simpletext */
#define TKN_LB 0x8de32020
/* *LN  Line            -                list of composed point ':' point */
#define TKN_LN 0x8ea30020
/* MA   Mark            -                list of point */
#define TKN_MA 0x8fa50020
/* SL   Selected        -                list of point */
#define TKN_SL 0x9b350020
/* *SQ  Square          -                list of point */
#define TKN_SQ 0x9b850020
/* TR   Triangle        -                list of point */
#define TKN_TR 0x9d650020
/* BL   Black time left move             real */
#define TKN_BL 0x7c600208
/* OB   OtStones Black  move             number */
#define TKN_OB 0x93500108
/* OW   OtStones White  move             number */
#define TKN_OW 0x94a00108
/* WL   White time left move             real */
#define TKN_WL 0xa2700208
/* !FG  Figure          -                none | composed number ":" simpletext */
#define TKN_FG 0x83546100
/* *PM  Print move mode - (inherit)      number */
#define TKN_PM 0x95d00100
/* *VW  View            - (inherit)      elist of point */
#define TKN_VW 0xa1554000

#define TKN                                              \
  /* root */                                             \
  u(AP) u(CA) u(FF) u(GM) u(ST) u(SZ)                    \
  /* setup */                                            \
  u(AB) u(AE) u(AW) u(PL)                                \
  /* ginfo */                                            \
  u(AN) u(BR) u(BT) u(CP) u(DT) u(EV) u(GN)              \
  u(GC) u(ON) u(OT) u(PB) u(PC) u(PW) u(RE) u(RO)        \
  u(HA) u(KM) u(TB) u(TW)                                \
  /* move */                                             \
  u(B) u(KO) u(MN) u(W)                                  \
  /* node anno*/                                         \
  u(C) u(DM) u(GB) u(GW) u(HO) u(N) u(UC) u(V)           \
  /* move anno */                                        \
  u(BM) u(DO) u(IT) u(TE)                                \
  /* markup */                                           \
  u(AR) u(CR) u(DD) u(LB) u(LN) u(MA) u(SL) u(SQ) u(TR)  \
  /* timing */                                           \
  u(BL) u(OB) u(OW) u(WL)                                \
  /* misc */                                             \
  u(FG) u(PM) u(VW)

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

void tkn_list() {
#define u(token) //tkn_add(#token, TKN_##token)
  TKN
#undef u
}

#endif /* __GM1_TOKEN_H__ */
