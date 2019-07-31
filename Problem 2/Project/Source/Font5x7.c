/***************************************************************************//**
 *
 * @file		Font5x7.c
 * @brief		Source file for a 5 x 7 font
 * @author		Embedded Artists AB
 * @author		Geoffrey Daniels
 * @version		1.0
 * @date		14 March. 2012
 *
 * Copyright (c) 2006 Embedded Artists AB
 * www.embeddedartists.com
 *
*******************************************************************************/

// Includes
#include "Font5x7.h"

//------------------------------------------------------------------------------

// Defines and typedefs
#define ________    0x00
#define _______X    0x01
#define ______X_    0x02
#define ______XX    0x03
#define _____X__    0x04
#define _____X_X    0x05
#define _____XX_    0x06
#define _____XXX    0x07
#define ____X___    0x08
#define ____X__X    0x09
#define ____X_X_    0x0a
#define ____X_XX    0x0b
#define ____XX__    0x0c
#define ____XX_X    0x0d
#define ____XXX_    0x0e
#define ____XXXX    0x0f
#define ___X____    0x10
#define ___X___X    0x11
#define ___X__X_    0x12
#define ___X__XX    0x13
#define ___X_X__    0x14
#define ___X_X_X    0x15
#define ___X_XX_    0x16
#define ___X_XXX    0x17
#define ___XX___    0x18
#define ___XX__X    0x19
#define ___XX_X_    0x1a
#define ___XX_XX    0x1b
#define ___XXX__    0x1c
#define ___XXX_X    0x1d
#define ___XXXX_    0x1e
#define ___XXXXX    0x1f
#define __X_____    0x20
#define __X____X    0x21
#define __X___X_    0x22
#define __X___XX    0x23
#define __X__X__    0x24
#define __X__X_X    0x25
#define __X__XX_    0x26
#define __X__XXX    0x27
#define __X_X___    0x28
#define __X_X__X    0x29
#define __X_X_X_    0x2a
#define __X_X_XX    0x2b
#define __X_XX__    0x2c
#define __X_XX_X    0x2d
#define __X_XXX_    0x2e
#define __X_XXXX    0x2f
#define __XX____    0x30
#define __XX___X    0x31
#define __XX__X_    0x32
#define __XX__XX    0x33
#define __XX_X__    0x34
#define __XX_X_X    0x35
#define __XX_XX_    0x36
#define __XX_XXX    0x37
#define __XXX___    0x38
#define __XXX__X    0x39
#define __XXX_X_    0x3a
#define __XXX_XX    0x3b
#define __XXXX__    0x3c
#define __XXXX_X    0x3d
#define __XXXXX_    0x3e
#define __XXXXXX    0x3f
#define _X______    0x40
#define _X_____X    0x41
#define _X____X_    0x42
#define _X____XX    0x43
#define _X___X__    0x44
#define _X___X_X    0x45
#define _X___XX_    0x46
#define _X___XXX    0x47
#define _X__X___    0x48
#define _X__X__X    0x49
#define _X__X_X_    0x4a
#define _X__X_XX    0x4b
#define _X__XX__    0x4c
#define _X__XX_X    0x4d
#define _X__XXX_    0x4e
#define _X__XXXX    0x4f
#define _X_X____    0x50
#define _X_X___X    0x51
#define _X_X__X_    0x52
#define _X_X__XX    0x53
#define _X_X_X__    0x54
#define _X_X_X_X    0x55
#define _X_X_XX_    0x56
#define _X_X_XXX    0x57
#define _X_XX___    0x58
#define _X_XX__X    0x59
#define _X_XX_X_    0x5a
#define _X_XX_XX    0x5b
#define _X_XXX__    0x5c
#define _X_XXX_X    0x5d
#define _X_XXXX_    0x5e
#define _X_XXXXX    0x5f
#define _XX_____    0x60
#define _XX____X    0x61
#define _XX___X_    0x62
#define _XX___XX    0x63
#define _XX__X__    0x64
#define _XX__X_X    0x65
#define _XX__XX_    0x66
#define _XX__XXX    0x67
#define _XX_X___    0x68
#define _XX_X__X    0x69
#define _XX_X_X_    0x6a
#define _XX_X_XX    0x6b
#define _XX_XX__    0x6c
#define _XX_XX_X    0x6d
#define _XX_XXX_    0x6e
#define _XX_XXXX    0x6f
#define _XXX____    0x70
#define _XXX___X    0x71
#define _XXX__X_    0x72
#define _XXX__XX    0x73
#define _XXX_X__    0x74
#define _XXX_X_X    0x75
#define _XXX_XX_    0x76
#define _XXX_XXX    0x77
#define _XXXX___    0x78
#define _XXXX__X    0x79
#define _XXXX_X_    0x7a
#define _XXXX_XX    0x7b
#define _XXXXX__    0x7c
#define _XXXXX_X    0x7d
#define _XXXXXX_    0x7e
#define _XXXXXXX    0x7f
#define X_______    0x80
#define X______X    0x81
#define X_____X_    0x82
#define X_____XX    0x83
#define X____X__    0x84
#define X____X_X    0x85
#define X____XX_    0x86
#define X____XXX    0x87
#define X___X___    0x88
#define X___X__X    0x89
#define X___X_X_    0x8a
#define X___X_XX    0x8b
#define X___XX__    0x8c
#define X___XX_X    0x8d
#define X___XXX_    0x8e
#define X___XXXX    0x8f
#define X__X____    0x90
#define X__X___X    0x91
#define X__X__X_    0x92
#define X__X__XX    0x93
#define X__X_X__    0x94
#define X__X_X_X    0x95
#define X__X_XX_    0x96
#define X__X_XXX    0x97
#define X__XX___    0x98
#define X__XX__X    0x99
#define X__XX_X_    0x9a
#define X__XX_XX    0x9b
#define X__XXX__    0x9c
#define X__XXX_X    0x9d
#define X__XXXX_    0x9e
#define X__XXXXX    0x9f
#define X_X_____    0xa0
#define X_X____X    0xa1
#define X_X___X_    0xa2
#define X_X___XX    0xa3
#define X_X__X__    0xa4
#define X_X__X_X    0xa5
#define X_X__XX_    0xa6
#define X_X__XXX    0xa7
#define X_X_X___    0xa8
#define X_X_X__X    0xa9
#define X_X_X_X_    0xaa
#define X_X_X_XX    0xab
#define X_X_XX__    0xac
#define X_X_XX_X    0xad
#define X_X_XXX_    0xae
#define X_X_XXXX    0xaf
#define X_XX____    0xb0
#define X_XX___X    0xb1
#define X_XX__X_    0xb2
#define X_XX__XX    0xb3
#define X_XX_X__    0xb4
#define X_XX_X_X    0xb5
#define X_XX_XX_    0xb6
#define X_XX_XXX    0xb7
#define X_XXX___    0xb8
#define X_XXX__X    0xb9
#define X_XXX_X_    0xba
#define X_XXX_XX    0xbb
#define X_XXXX__    0xbc
#define X_XXXX_X    0xbd
#define X_XXXXX_    0xbe
#define X_XXXXXX    0xbf
#define XX______    0xc0
#define XX_____X    0xc1
#define XX____X_    0xc2
#define XX____XX    0xc3
#define XX___X__    0xc4
#define XX___X_X    0xc5
#define XX___XX_    0xc6
#define XX___XXX    0xc7
#define XX__X___    0xc8
#define XX__X__X    0xc9
#define XX__X_X_    0xca
#define XX__X_XX    0xcb
#define XX__XX__    0xcc
#define XX__XX_X    0xcd
#define XX__XXX_    0xce
#define XX__XXXX    0xcf
#define XX_X____    0xd0
#define XX_X___X    0xd1
#define XX_X__X_    0xd2
#define XX_X__XX    0xd3
#define XX_X_X__    0xd4
#define XX_X_X_X    0xd5
#define XX_X_XX_    0xd6
#define XX_X_XXX    0xd7
#define XX_XX___    0xd8
#define XX_XX__X    0xd9
#define XX_XX_X_    0xda
#define XX_XX_XX    0xdb
#define XX_XXX__    0xdc
#define XX_XXX_X    0xdd
#define XX_XXXX_    0xde
#define XX_XXXXX    0xdf
#define XXX_____    0xe0
#define XXX____X    0xe1
#define XXX___X_    0xe2
#define XXX___XX    0xe3
#define XXX__X__    0xe4
#define XXX__X_X    0xe5
#define XXX__XX_    0xe6
#define XXX__XXX    0xe7
#define XXX_X___    0xe8
#define XXX_X__X    0xe9
#define XXX_X_X_    0xea
#define XXX_X_XX    0xeb
#define XXX_XX__    0xec
#define XXX_XX_X    0xed
#define XXX_XXX_    0xee
#define XXX_XXXX    0xef
#define XXXX____    0xf0
#define XXXX___X    0xf1
#define XXXX__X_    0xf2
#define XXXX__XX    0xf3
#define XXXX_X__    0xf4
#define XXXX_X_X    0xf5
#define XXXX_XX_    0xf6
#define XXXX_XXX    0xf7
#define XXXXX___    0xf8
#define XXXXX__X    0xf9
#define XXXXX_X_    0xfa
#define XXXXX_XX    0xfb
#define XXXXXX__    0xfc
#define XXXXXX_X    0xfd
#define XXXXXXX_    0xfe
#define XXXXXXXX    0xff

//------------------------------------------------------------------------------

// External global variables
const unsigned char Font5x7[][8] =
{
/* space */
  {
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}

/*  !  */
 ,{
   X_______,
   X_______,
   X_______,
   X_______,
   X_______,
   ________,
   X_______,
   ________}


/*  "  */
 ,{
   X_X_____,
   X_X_____,
   X_X_____,
   ________,
   ________,
   ________,
   ________,
   ________}

/* #  */
 ,{
   _X_X____,
   _X_X____,
   XXXXX___,
   _X_X____,
   XXXXX___,
   _X_X____,
   _X_X____,
   ________}

/*  $  */
 ,{
   __X_____,
   _XXXX___,
   X_X_____,
   _XXX____,
   __X_X___,
   XXXX____,
   __X_____}

/*  %  */
 ,{
   XX______,
   XX__X___,
   ___X____,
   __X_____,
   _X______,
   X__XX___,
   ___XX___,
   ________}

/*  &  */
 ,{
   _XX_____,
   X__X____,
   X_X_____,
   _X______,
   X_X_X___,
   X__X____,
   _XX_X___,
   ________}

/*  '  */
 ,{
   XX______,
   _X______,
   X_______,
   ________,
   ________,
   ________,
   ________,
   ________}

/*  (  */
 ,{
   __X_____,
   _X______,
   X_______,
   X_______,
   X_______,
   _X______,
   __X_____,
   ________}

/*  )  */
 ,{
   X_______,
   _X______,
   __X_____,
   __X_____,
   __X_____,
   _X______,
   X_______,
   ________}

/*  *  */
 ,{
   ________,
   _X_X____,
   __X_____,
   XXXXX___,
   __X_____,
   _X_X____,
   ________,
   ________}

 ,{
   ________,
   __X_____,
   __X_____,
   XXXXX___,
   __X_____,
   __X_____,
   ________,
   ________}

 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   XX______,
   _X______,
   X_______}

 ,{
   ________,
   ________,
   ________,
   XXXXX___,
   ________,
   ________,
   ________,
   ________}

 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   XX______,
   XX______,
   ________}

 ,{
   ________,
   ____X___,
   ___X____,
   __X_____,
   _X______,
   X_______,
   ________,
   ________}

/* 0 */
 ,{
   _XXX____,
   X___X___,
   X__XX___,
   X_X_X___,
   XX__X___,
   X___X___,
   _XXX____,
   ________}

/* 1 */
 ,{
   __X_____,
   _XX_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   _XXX____,
   ________}

/* 2 */
 ,{
   _XXX____,
   X___X___,
   ____X___,
   __XX____,
   _X______,
   X_______,
   XXXXX___,
   ________}

/* 3 */
 ,{
   _XXX____,
   X___X___,
   ____X___,
   __XX____,
   ____X___,
   X___X___,
   _XXX____,
   ________}

/* 4 */
 ,{
   ___X____,
   __XX____,
   _X_X____,
   X__X____,
   XXXXX___,
   ___X____,
   ___X____,
   ________}

/* 5 */
 ,{
   XXXXX___,
   X_______,
   XXXX____,
   ____X___,
   ____X___,
   X___X___,
   _XXX____,
   ________}

/* 6 */
 ,{
   __XX____,
   _X______,
   X_______,
   XXXX____,
   X___X___,
   X___X___,
   _XXX____,
   ________}

/* 7 */
 ,{
   XXXXX___,
   ____X___,
   ___X____,
   __X_____,
   _X______,
   _X______,
   _X______,
   ________}

/* 8 */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   _XXX____,
   X___X___,
   X___X___,
   _XXX____,
   ________}

/* 9 */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   _XXXX___,
   ____X___,
   ___X____,
   _XX_____,
   ________}

/* ':' 3a */
 ,{
   ________,
   XX______,
   XX______,
   ________,
   XX______,
   XX______,
   ________,
   ________}

/* ';' 3b */
 ,{
   ________,
   ________,
   XX______,
   XX______,
   ________,
   XX______,
   _X______,
   X_______}


/* '<' 3c */
 ,{
   ___X____,
   __X_____,
   _X______,
   X_______,
   _X______,
   __X_____,
   ___X____,
   ________}

/* '=' 3d */
 ,{
   ________,
   ________,
   XXXXX___,
   ________,
   XXXXX___,
   ________,
   ________,
   ________}

/* '>' */
 ,{
   X_______,
   _X______,
   __X_____,
   ___X____,
   __X_____,
   _X______,
   X_______,
   ________}

/* '?' */
 ,{
   _XXX____,
   X___X___,
   ____X___,
   ___X____,
   __X_____,
   ________,
   __X_____,
   ________}

/* @ */
 ,{
   _XXX____,
   X___X___,
   ____X___,
   _XX_X___,
   X_X_X___,
   X_X_X___,
   _XXX____,
   ________}

/* A */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   XXXXX___,
   X___X___,
   X___X___,
   X___X___,
   ________}

/* B */
 ,{
   XXXX____,
   X___X___,
   X___X___,
   XXXX____,
   X___X___,
   X___X___,
   XXXX____,
   ________}

/* C */
 ,{
   _XXX____,
   X___X___,
   X_______,
   X_______,
   X_______,
   X___X___,
   _XXX____,
   ________}

/* D */
 ,{
   XXX_____,
   X__X____,
   X___X___,
   X___X___,
   X___X___,
   X__X____,
   XXX_____,
   ________}

/* E */
 ,{
   XXXXX___,
   X_______,
   X_______,
   XXXX____,
   X_______,
   X_______,
   XXXXX___,
   ________}

/* F */
 ,{
   XXXXX___,
   X_______,
   X_______,
   XXXX____,
   X_______,
   X_______,
   X_______,
   ________}

/* G */
 ,{
   _XXX____,
   X___X___,
   X_______,
   X_______,
   X__XX___,
   X___X___,
   _XXXX___,
   ________}

/* H */
 ,{
   X___X___,
   X___X___,
   X___X___,
   XXXXX___,
   X___X___,
   X___X___,
   X___X___,
   ________}

/* I */
 ,{
   XXX_____,
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   XXX_____,
   ________}

/* J */
 ,{
   __XXX___,
   ___X____,
   ___X____,
   ___X____,
   ___X____,
   X__X____,
   _XX_____,
   ________}

/* K */
 ,{
   X___X___,
   X__X____,
   X_X_____,
   XX______,
   X_X_____,
   X__X____,
   X___X___,
   ________}

/* L */
 ,{
   X_______,
   X_______,
   X_______,
   X_______,
   X_______,
   X_______,
   XXXXX___,
   ________}

/* M */
 ,{
   X___X___,
   XX_XX___,
   X_X_X___,
   X_X_X___,
   X___X___,
   X___X___,
   X___X___,
   ________}

/* N */
 ,{
   X___X___,
   X___X___,
   XX__X___,
   X_X_X___,
   X__XX___,
   X___X___,
   X___X___,
   ________}

/* O */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   _XXX____,
   ________}

/* P */
 ,{
   XXXX____,
   X___X___,
   X___X___,
   XXXX____,
   X_______,
   X_______,
   X_______,
   ________}

/* Q */
 ,{
   _XXX____,
   X___X___,
   X___X___,
   X___X___,
   X_X_X___,
   X__X____,
   _XX_X___,
   ________}

/* R */
 ,{
   XXXX____,
   X___X___,
   X___X___,
   XXXX____,
   X_X_____,
   X__X____,
   X___X___,
   ________}

/* S */
 ,{
   _XXX____,
   X___X___,
   X_______,
   _XXX____,
   ____X___,
   X___X___,
   _XXX____,
   ________}

/* T */
 ,{
   XXXXX___,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   ________}

/* U */
 ,{
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   _XXX____,
   ________}

/* V */
 ,{
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   X___X___,
   _X_X____,
   __X_____,
   ________}

/* W */
 ,{
   X___X___,
   X___X___,
   X___X___,
   X_X_X___,
   X_X_X___,
   X_X_X___,
   _X_X____,
   ________}

/* X */
 ,{
   X___X___,
   X___X___,
   _X_X____,
   __X_____,
   _X_X____,
   X___X___,
   X___X___,
   ________}

/* Y */
 ,{
   X___X___,
   X___X___,
   _X_X____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   ________}

/* Z */
 ,{
   XXXXX___,
   ____X___,
   ___X____,
   __X_____,
   _X______,
   X_______,
   XXXXX___,
   ________}

/* 5b */
 ,{
   XXX_____,
   X_______,
   X_______,
   X_______,
   X_______,
   X_______,
   XXX_____,
   ________}

/* 5c */
 ,{
   ________,
   X_______,
   _X______,
   __X_____,
   ___X____,
   ____X___,
   ________,
   ________}

/* 5d */
 ,{
   XXX_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   XXX_____,
   ________}

/* 5e */
 ,{
   __X_____,
   _X_X____,
   X___X___,
   ________,
   ________,
   ________,
   ________,
   ________}

/* 5f */
 ,{
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________,
   XXXXX___}

/* 60 */
 ,{
   X_______,
   _X______,
   __X_____,
   ________,
   ________,
   ________,
   ________,
   ________}

/* a */
 ,{
   ________,
   ________,
   _XXX____,
   ____X___,
   _XXXX___,
   X___X___,
   _XXXX___,
   ________}

/* b */
 ,{
   X_______,
   X_______,
   X_XX____,
   XX__X___,
   X___X___,
   X___X___,
   XXXX____,
   ________}

/* c */
 ,{
   ________,
   ________,
   _XX_____,
   X__X____,
   X_______,
   X__X____,
   _XX_____,
   ________}

/* d */
 ,{
   ____X___,
   ____X___,
   _XX_X___,
   X__XX___,
   X___X___,
   X___X___,
   _XXXX___,
   ________}

/* e */
 ,{
   ________,
   ________,
   _XXX____,
   X___X___,
   XXXXX___,
   X_______,
   _XXX____,
   ________}

/* f */
 ,{
   __X_____,
   _X_X____,
   _X______,
   XXX_____,
   _X______,
   _X______,
   _X______,
   ________}

/* g */
 ,{
   ________,
   ________,
   _XXXX___,
   X___X___,
   X___X___,
   _XXXX___,
   ____X___,
   _XXX____}

/* h */
 ,{
   X_______,
   X_______,
   X_XX____,
   XX__X___,
   X___X___,
   X___X___,
   X___X___,
   ________}

/* i */
 ,{
   _X______,
   ________,
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   ________}

/* j */
 ,{
   __X_____,
   ________,
   _XX_____,
   __X_____,
   __X_____,
   __X_____,
   __X_____,
   XX______}

/* k */
 ,{
   X_______,
   X_______,
   X__X____,
   X_X_____,
   XX______,
   X_X_____,
   X__X____,
   ________}

/* l */
 ,{
   XX______,
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   XXX_____,
   ________}

/* m */
 ,{
   ________,
   ________,
   XX_X____,
   X_X_X___,
   X_X_X___,
   X___X___,
   X___X___,
   ________}

/* n */
 ,{
   ________,
   ________,
   X_XX____,
   XX_X____,
   X__X____,
   X__X____,
   X__X____,
   ________}

/* o */
 ,{
   ________,
   ________,
   _XX_____,
   X__X____,
   X__X____,
   X__X____,
   _XX_____,
   ________}

/* p */
 ,{
   ________,
   ________,
   XXX_____,
   X__X____,
   X__X____,
   XXX_____,
   X_______,
   X_______}

/* q */
 ,{
   ________,
   ________,
   _XXX____,
   X__X____,
   X__X____,
   _XXX____,
   ___X____,
   ___X____}

/* r */
 ,{
   ________,
   ________,
   _X_X____,
   _XX_____,
   _X______,
   _X______,
   _X______,
   ________}

/* s */
 ,{
   ________,
   ________,
   _XXX____,
   X_______,
   _XX_____,
   ___X____,
   XXX_____,
   ________}

/* t */
 ,{
   _X______,
   _X______,
   XXX_____,
   _X______,
   _X______,
   _X______,
   _XX_____,
   ________}

/* u */
 ,{
   ________,
   ________,
   X__X____,
   X__X____,
   X__X____,
   X__X____,
   _XXX____,
   ________}

/* v */
 ,{
   ________,
   ________,
   X___X___,
   X___X___,
   X___X___,
   _X_X____,
   __X_____,
   ________}

/* w */
 ,{
   ________,
   ________,
   X___X___,
   X___X___,
   X_X_X___,
   X_X_X___,
   _X_X____,
   ________}

/* X */
 ,{
   ________,
   ________,
   X___X___,
   _X_X____,
   __X_____,
   _X_X____,
   X___X___,
   ________}

/* y */
 ,{
   ________,
   ________,
   X__X____,
   X__X____,
   X__X____,
   _XXX____,
   ___X____,
   _XX_____}

/* z */
 ,{
   ________,
   ________,
   XXXXX___,
   ___X____,
   __X_____,
   _X______,
   XXXXX___,
   ________}

/* 0x7b */
 ,{
   __X_____,
   _X______,
   _X______,
   X_______,
   _X______,
   _X______,
   __X_____,
   ________}

/* 0x7c */
 ,{
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   _X______,
   ________}

/* 0x7d */
 ,{
   X_______,
   _X______,
   _X______,
   __X_____,
   _X______,
   _X______,
   X_______,
   ________}

/* 0x7e */
 ,{
   _XX_X___,
   X__X____,
   ________,
   ________,
   ________,
   ________,
   ________,
   ________}

/* 0x7f */
 ,{
   XXXXX___,
   XXXXX___,
   XXXXX___,
   XXXXX___,
   XXXXX___,
   XXXXX___,
   XXXXX___,
   ________}

};

//------------------------------------------------------------------------------

// Local variables
//...

//------------------------------------------------------------------------------

// Local Functions
//...

//------------------------------------------------------------------------------

// Public Functions
//...
