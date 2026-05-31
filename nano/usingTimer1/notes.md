
The Arduino nano has 3 timers, but really, we mostly use timer 1 since timer 0 is reserved for `millis` and `micros`. Idk about timer 2 but it's only 8-bit. Timer 1 is 16-bit.

We have the following registers we need to know:

- `TCCR1A`: stands for Timer/Counter Control Register; contains settings for timer 1
- `TCCR1B`: also contains settings for timer 1
- `TCNT1`: stands for Timer Count. It's the counter
- `OCR1A`: stands for Output Compare Register. It's the value we need to compare against I bet. There's also a B.
- `TIMSK1`: Timer Interrupt Mask Register; not part of the timer, but for the CPU itself, that is, it specifies what event should be allowed to interrupt the CPU. Like, maybe an overflow should interrupt the CPU, maybe if the counter hits OCR1A, it should do stuff, etc...

There's also this thing:

```c
ISR(TIMER1_COMPA_vect){
  // some interrupt service routine goes here...
}
```

Now by itself, this is invalid `c` code, but this is basically a macros provided by `avr-gcc`.





