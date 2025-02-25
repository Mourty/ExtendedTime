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
#include <Arduino.h>

#ifndef ExtendedTime_H
#define ExtendedTime_H

unsigned long long extendedMillis();
unsigned long long extendedMicros();

#endif // ExtendedTime