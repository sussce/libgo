#ifndef _TOKEN_H_
#define _TOKEN_H_

/*
  [SGF FF[4] - Smart Game Format]
  FF[4] property index
  This is an alphabetical index to all properties defined in FF[4].
  New properties are marked with '*', changed properties are marked with '!'.

  ID   Description     property type    property value
*/
/* *AP  Application     root	            composed simpletext ':' simpletext */
#define TKN_AP
#define TKN_CA
#define TKN_FF 0x83400101
#define TKN_GM
#define TKN_ST
#define TKN_SZ
/* AB   Add Black       setup            list of stone */
#define TKN_AB
#define TKN_AE
#define TKN_AW
#define TKN_PL
/* AN   Annotation      game-info        simpletext */
#define TKN_AN
#define TKN_BR
#define TKN_BT
#define TKN_CP
#define TKN_DT
#define TKN_EV
#define TKN_GN

#define TKN_GC
#define TKN_ON
#define TKN_OT
#define TKN_PB
#define TKN_PC
#define TKN_PW
#define TKN_RE
#define TKN_RO

#define TKN_HA
#define TKN_KM
#define TKN_TB
#define TKN_TW
/* B    Black           move             move */
#define TKN_B
#define TKN_KO
#define TKN_MN
#define TKN_W
/* C    Comment         -                text */
#define TKN_C
#define TKN_DM
#define TKN_GB
#define TKN_GW
#define TKN_HO
#define TKN_N
#define TKN_UC
#define TKN_V
/* BM   Bad move        move             double */
#define TKN_BM
#define TKN_DO
#define TKN_IT
#define TKN_TE
/* *AR  Arrow           -                list of composed point ':' point */
#define TKN_AR
#define TKN_CR
#define TKN_DD
#define TKN_LB
#define TKN_LN
#define TKN_MA
#define TKN_SL
#define TKN_SQ
#define TKN_TR
/* BL   Black time left move             real */
#define TKN_BL
#define TKN_OB
#define TKN_OW
#define TKN_WL
/* !FG  Figure          -                none | composed number ":" simpletext */
#define TKN_FG
#define TKN_PM
#define TKN_VW

#define TKN                                             \
  /* root */                                            \
  x(AP) x(CA) x(FF) x(GM) x(ST) x(SZ)                   \
  /* setup */                                           \
  x(AB) x(AE) x(AW) x(PL)                               \
  /* ginfo */                                           \
  x(AN) x(BR) x(BT) x(CP) x(DT) x(EV) x(GN)             \
  x(GC) x(ON) x(OT) x(PB) x(PC) x(PW) x(RE) x(RO)       \
  x(HA) x(KM) x(TB) x(TW)                               \
  /* move */                                            \
  x(B) x(KO) x(MN) x(W)                                 \
  /* node anno*/                                        \
  x(C) x(DM) x(GB) x(GW) x(HO) x(N) x(UC) x(V)          \
  /* move anno */                                       \
  x(BM) x(DO) x(IT) x(TE)                               \
  /* markup */                                          \
  x(AR) x(CR) x(DD) x(LB) x(LN) x(MA) x(SL) x(SQ) x(TR) \
  /* timing */                                          \
  x(BL) x(OB) x(OW) x(WL)                               \
  /* misc */                                            \
  x(FG) x(PM) x(VW)

int max_bits(unsigned long n) {
  int c;
  for(c = 0; n; c++, n >>= 1 );
  return c;
}

unsigned int tkn_gen(char* id, int type) {
  unsigned int tkn = 0;
  unsigned long uid = 0;

  if (!id)
    return 0;
  
  uid = hash(id);
  
  if(max_bits(uid) > uid_bits)
    tkn = (1 << uid_bit) | type;
  else
    tkn = (uid << uid_bit) | type;
  
  return tkn;
}

void tkn_gen () {
#define x(token) hash_add(#token, TKN_##token)
  TKN
#undef x
}

#endif
