/* This program is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. */

#ifndef _LIB_GO_H_
#define _LIB_GO_H_

/* EBNF
  Collection = GameTree { GameTree }
  GameTree   = "(" Sequence { GameTree } ")"
  Sequence   = Node { Node }
  Node       = ";" { Property }
  Property   = PropIdent PropValue { PropValue }
  PropIdent  = UcLetter { UcLetter }
  PropValue  = "[" CValueType "]"
  CValueType = (ValueType | Compose)
  ValueType  = (None | Number | Real | Double | Color | SimpleText |
		Text | Point  | Move | Stone)

White space (space, tab, carriage return, line feed, vertical tab and so on) may appear anywhere between PropValues, Properties, Nodes, Sequences and GameTrees.
There are two types of property lists: 'list of' and 'elist of'.

'list of':    PropValue { PropValue }
'elist of':   ((PropValue { PropValue }) | None)
              In other words elist is list or "[]". */

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

typedef struct _Game Game;

struct _Game {
  char* ru;
  float km;
  int ha;
  char* re;
  char* pb;
  char* pw;
  char* br;
  char* wr;
  char* gn;
  char* dt;
  int sz;
  
  int turn;
  int ko;
  int mn;
};

#endif /* _LIB_GO_H_ */
