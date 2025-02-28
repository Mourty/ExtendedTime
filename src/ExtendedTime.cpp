/*
  ExtendedTime - Longer running millis and micros for Arduino.
  Copyright (c) [2025] [Mourty]

  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this library; if not, see <https://www.gnu.org/licenses/>.
*/
/*
  Modified Timer0 Overflow ISR, millis function, and micros function for ExtendedTime.
  I wanted to properly credit the original author. If this isn't sufficient citing
  please let me know. I will fix it as soon as possible. My email can be found in the
  properties file under maintainer.
  Based on the original Arduino wiring.c implementation.

  Original Author: David A. Mellis
  Modified by: Mourty
  Date: 2025

  Original notice in wiring.c

  wiring.c - Partial implementation of the Wiring API for the ATmega8.
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
  This ISR and functions are licensed under the GNU Lesser General Public License v2.1
  or later. See LICENSE file for more details.
*/

#include "ExtendedTime.h"

#include <Arduino.h>
volatile unsigned long epoch = 0;
extern volatile unsigned long timer0_overflow_count;
extern volatile unsigned long timer0_millis;
extern volatile unsigned char timer0_fract;
extern const unsigned char FRACT_INC;
extern const unsigned char FRACT_MAX;
extern const unsigned long MILLIS_INC;
#if defined(TIM0_OVF_vect)
extern "C" void TIM0_OVF_vect(void) __attribute__((weak, alias("custom_tim0_ovf_isr")));
extern "C" void custom_tim0_ovf_isr()
#else
extern "C" void TIMER0_OVF_vect(void) __attribute__((weak, alias("custom_timer0_ovf_isr")));
extern "C" void custom_timer0_ovf_isr()
#endif
{
    unsigned long m = timer0_millis;
    unsigned char f = timer0_fract;

    m += MILLIS_INC;
    f += FRACT_INC;
    if (f >= FRACT_MAX)
    {
        f -= FRACT_MAX;
        m += 1;
    }

    timer0_fract = f;
    timer0_millis = m;
    timer0_overflow_count++;

    // Handle epoch increment
    if (timer0_overflow_count == 0)
    {
        epoch++;
    }
}

unsigned long long extendedMillis()
{
    unsigned long m;
    unsigned long e;
    uint8_t oldSREG = SREG;

    // disable interrupts while we read timer0_millis or we might get an
    // inconsistent value (e.g. in the middle of a write to timer0_millis)
    cli();
    m = timer0_millis;
    e = epoch;
    SREG = oldSREG;
    unsigned long long epochMilliseconds =
        (unsigned long long)e * ((1ULL << 32) * (clockCyclesToMicroseconds(256 * 64))) / 1000;
    return (m + epochMilliseconds);
}

unsigned long long extendedMicros()
{
    unsigned long long m;
    unsigned long e;
    uint8_t oldSREG = SREG, t;
    cli();
    m = timer0_overflow_count;
    e = epoch;
#if defined(TCNT0)
    t = TCNT0;
#elif defined(TCNT0L)
    t = TCNT0L;
#else
#error TIMER 0 not defined
#endif

#ifdef TIFR0
    if ((TIFR0 & _BV(TOV0)) && (t < 255))
        m++;
#else
    if ((TIFR & _BV(TOV0)) && (t < 255))
        m++;
#endif

    SREG = oldSREG;
    unsigned long long microseconds = ((m << 8) + t) * (64 / clockCyclesPerMicrosecond());
    unsigned long long epochMicroseconds = (unsigned long long)e * ((1ULL << 32) * clockCyclesToMicroseconds(256 * 64));
    return (epochMicroseconds + microseconds);
}
