#ifndef STG_H
#define STG_H

/** This is the driver for an Servo-To-Go Model I board.
    The board includes 8 channels of quadrature encoder input,
    8 channels of analog input and output, 32 bits digital I/O,
    and an interval timer with interrupt.
**/

/** Copyright (C) 2005 Alex Joni
                       <alex DOT joni AT robcon DOT ro>
**/

/** This program is free software; you can redistribute it and/or
    modify it under the terms of version 2.1 of the GNU General
    Public License as published by the Free Software Foundation.
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111 USA

    THE AUTHORS OF THIS LIBRARY ACCEPT ABSOLUTELY NO LIABILITY FOR
    ANY HARM OR LOSS RESULTING FROM ITS USE.  IT IS _EXTREMELY_ UNWISE
    TO RELY ON SOFTWARE ALONE FOR SAFETY.  Any machinery capable of
    harming persons must have provisions for completely removing power
    from all motors, etc, before persons enter any danger area.  All
    machinery must be designed to comply with local and national safety
    codes, and the authors of this software can not, and do not, take
    any responsibility for such compliance.

    This code was written as part of the EMC HAL project.  For more
    information, go to www.linuxcnc.org.
**/

/*
    Servo To Go board decls
*/

#define CNT0_D     0x00
#define CNT1_D     0x01
#define CNT0_C     0x02
#define CNT1_C     0x03
#define CNT2_D     0x04
#define CNT3_D     0x05
#define CNT2_C     0x06
#define CNT3_C     0x07
#define CNT4_D     0x08
#define CNT5_D     0x09
#define CNT4_C     0x0a
#define CNT5_C     0x0b
#define CNT6_D     0x0c
#define CNT7_D     0x0d
#define CNT6_C     0x0e
#define CNT7_C     0x0f
#define DAC_0      0x10
#define DAC_1      0x12
#define DAC_2      0x14
#define DAC_3      0x16
#define DAC_4      0x18
#define DAC_5      0x1a
#define DAC_6      0x1c
#define DAC_7      0x1e
#define ADC_0      0x410
#define ADC_1      0x412
#define ADC_2      0x414
#define ADC_3      0x416
#define ADC_4      0x418
#define ADC_5      0x41a
#define ADC_6      0x41c
#define ADC_7      0x41e
#define DIO_A      0x400
#define DIO_B      0x402
#define BRDTST     0x403
#define DIO_C      0x404
#define MIO_1      0x406
#define DIO_D      0x401
#define INTC       0x405
#define MIO_2      0x407
#define ODDRST     0x407
#define TIMER_0    0x408
#define TIMER_1    0x40a
#define TIMER_2    0x40c
#define TMRCMD     0x40e
#define ICW1       0x409
#define ICW2       0x40b
#define OCW1       0x40b
#define OCW2       0x409
#define OCW3       0x409
#define IRR        0x409
#define ISR        0x409
#define IMR        0x40b

#endif
