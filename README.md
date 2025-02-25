# ExtendedTime

<br/>

This is a library for extending the millis() and micros() overflow timers for Ardunio.
The library modifies the existing timer0 overflow ISR to extend the maximum time for millis and micros
into a unsigned 64 bit number rather than a unsigned 32 bit number. To access the new values simply run
extendedMillis();, or extendedMicros();. These will stand in for the standard millis micros calls but return
a unsigned 64 bit number of milliseconds or microseconds respectively.

I hope this helps.

<br/>

## Installation
### I. Using Arduino Library Manager
Search for **ExtendedTime** in the Arduino Library Manager and install the latest version.

### II. Manual Installation

If you would like to install manually, you can follow these steps:

1. Download the latest release
2. Extract and place the folder in `~/Arduino/libraries/`

<br/>

## License
This library is licensed under the **GNU Lesser General Public License v2.1 or later (LGPL 2.1+).**  

This means you are free to use, modify, and distribute this library under the terms of the LGPL 2.1+.  
However, if you modify and distribute this library, you must also release the modified version under the same LGPL license.  

For more details, see the [LICENSE](LICENSE) file.  