#include <util/delay.h>
#include <avr/io.h>

#include "servo.h"

inline void delay_us(unsigned long int i) {
  while (i--)
    _delay_us(1);
}

int main() {
  DDRD |= (1 << 2) | (1 << 3);

  Servo servos[2];
  servos[0] = Servo(&PORTD, 2);
  servos[1] = Servo(&PORTD, 3);
  unsigned int delta = 0;
  servos[0].MoveTo(1500, 50);
  servos[1].MoveTo(1500, 40);
  while (true) {
    delta = Servo::DispatchServos(servos, servos + 2, delta);
    
    if (servos[0].angle() == 1500)
      servos[0].MoveTo(0);
    else if (servos[0].angle() == 0)
      servos[0].MoveTo(1500);

    if (servos[1].angle() == 1500)
      servos[1].MoveTo(0);
    else if (servos[1].angle() == 0)
      servos[1].MoveTo(1500);
    delay_us(delta);
  }
}
