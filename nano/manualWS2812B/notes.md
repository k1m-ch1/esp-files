# Wiring

- one 5V pin
- one data pin
- one GND pin

# Individual LED

An LED cell has the following labels:

```
VCC, DIN, GND
    LED
VCC, DO, GND
```

I assume that there's some sort of "shift-registery" circuitry going on. Let's see...

# Specs

- scan frequency not less than 400Hz/s (not sure what that means...)
- 30 FPS max
- data transmission at 800Kbps
- NRZ communication

Ok so it seems like, this is how it works

As an LED at $i$, I take the first thing that $i - 1$ gave to me, and then I give rest of the things that $i - 1$ gives to me to $i + 1$.

Apply that logic to all LED and it should work.

That's quite elegant... If we pass in too little data, then the guys at the back just don't light up. If we pass in too much data, it just gets cut off without side effects.

We should try to make this as fast as possible right? so when i transmit the first color, then the second color; the second LED should receive that second color in the same "interval" right? like, i'm not sure whether a singular cell even have the memory to remember like N - i or something colors right? there's probbaly some circuitry that just says "take the first color, then just pull a switch and make the rest of the colors go directly to D0" right?

Ok so max frame rate is $30Hz$, meaning that we have $1/30 s$ to transmit our data. That amounts to $0.06$ or $33ms$. Right now, from my logic analyzer, it seems like we can transmit one bit every $1.25 \mu s$, each LED gets one color which is $24 bits$, so we'll need $1.25 * 24 \mu s = 30 \mu s$ to transmit one color across. This means that in theory, there's a maximum of $33ms / 30 \mu s = 33/30 \times 10^{3} = 1100$ LED we can control at $30Hz$?

We also need to consider the reset time of at least $60 \mu s$. So really:

$
(33 - 60 \times 10^{-3})/(30) \times 10^{3} = 1097
$

So just round that down to 1000 LED.

# Data representation

So:

- 0 means: $400 \pm 150 ns$ HIGH, $800 \pm 150 ns$ LOW
- 1 means: $800 \pm 150 ns$ HIGH, $450 \pm 150 ns$ LOW
- Reset: over $50 000 ns$ of LOW

# Sending individual colors

So we send 24 bits of RGB data. we actually need to send it in GRB ordering, meaning we send G first, R second, B third.

Now, the timing is actually quite tight, and there isn't a `nanos()` function. In fact, the Arduino UNO or nano or like the atmega328p has a clock speed of 16MHz which means each cycle takes place in $6.25 \times 10^{-8} s =  62.5 ns $

So we need to count cycles to do the timing correctly... damn.

We need to simplify the $digitalWrite$ function. We'll use direct port manipulation

```
PORTB |= (1 << PB0);
```

Apparently, this takes 2 cycles as long as the compiler does what you expect it to do... 

Similarly, to set it to low without side effects:

|old bit|select|new bit|
|---|---|---|
|0|0|0|
|0|1|1|
|1|0|1|
|1|1|1|

This is just `new_bit = old_bit nor select_bit`

Notice:

```
~ (p | q) = ~p ^ ~q
```

```
PORTB &= ~(1 << PB0);
```

Let's recap what ports we actually need to manipulate

![](https://electronoobs.com/images/Arduino/tut_130/Arduino_ports.jpg)

This won't produce side effects to other pins (as in, it won't change the state of other pins) which is nice.

Now, too bad we kinda need to write direct assembly to say "do nothing on this cycle", but good thing we can embed assembly into our code.

```
asm("nop");
```

I assume a `nop` instruction means "no operation". But, compiler might be too smart and assume that the code does nothing, therefore, we need to put the `volatile` keyword to tell the compiler to leave this alone.

```
asm volatile ("nop");
```

This statement is very weird cuz `asm` is a `gcc` or a compiler specific keyword, meanwhile, `volatile` is a gcc keyword. So what exactly is `("nop")`? It's not an input to a function, there is no function. It's not a variable declaration. How do I make sense of this statement? What other statements follow this specific form?

The timing is as follows:

|cycles|delay|
|---|---|
|0|0.0|
|1|62.5|
|2|125.0|
|3|187.5|
|4|250.0|
|5|312.5|
|6|375.0|
|7|437.5|
|8|500.0|
|9|562.5|
|10|625.0|
|11|687.5|
|12|750.0|
|13|812.5|
|14|875.0|
|15|937.5|
|16|1000.0|
|17|1062.5|
|18|1125.0|
|19|1187.5|
