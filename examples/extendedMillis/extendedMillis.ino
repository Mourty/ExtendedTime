/*
Simply use extendedMillis as you would millis, but the returned type is unsigned long long. Other than that, it will work the same, but not roll over for much, much longer.
Enjoy
*/

#include <ExtendedTime.h>
int LED = LED_BUILTIN;
unsigned long long now;
void setup() {
  pinMode(LED, OUTPUT);
  now = extendedMillis();
}

void loop() {
  if (extendedMillis() - now > 1000)
  {
    digitalWrite(LED, !digitalRead(LED));
    now = extendedMillis();
  }

}
