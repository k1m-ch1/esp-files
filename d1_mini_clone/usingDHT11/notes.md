# Protocol

## initialization

- When MCU starts, no reading data, set the output pin to HIGH

## start signal

- MCU sends a start signal from HIGH to LOW for at least 18 milliseconds
- pull back to HIGH (releases the bus, meaning setting the pin to input mode)
- wait 40 microseconds
- switch the pin to input mode


### Dilemma

I have a problem with the DHT11 initialization protocol.

So when we're doing nothing, we're stating that our pin should be an output pin, and we should pull it high, and we're assuming that the dht11 is currently in "input mode" so no short.

Now when we start it, we pull it low, and i assume the DHT11 is still in "input mode", so no short.

Now here's the problem, we pull it back high for 40 microseconds and then we set out pin to input pin. and then what comes next is a low, meaning that after that 40 microseconds, the DHT11 has routed the signal through the 5k resistor to ground, meanign that we read a LOW. now, if during that 40 microseconds, the DHT11 decides to switch to output mode, and it pulls that whole circuit to ground, there's a short right? like our MCU pin is output mode, HIGH, then the DHT11 decides to switch to "output mode" and pull it to ground. So is the DHT11 smart where it will detect when we'll switch to "input mode" and then it will now switch to output mode to drive the bus?

Ok so it's like this:

- during idle time, our MCU is in INPUT mode. Both sides will read HIGH because of the pull up resistor
- when initializing, we actively take control, setting out pin to OUTPUT, then pulling it LOW for at least 18 milliseconds. Then we let go by setting our pin to INPUT mode.
- We wait until the DHT11 responds by actively taking control of the bus, then either pulling it HIGH or LOW based on the data. We read parse that data while in INPUT mode.
- the DHT sends out a response, which is 80 microseconds LOW, 80 microseconds HIGH. Once it pulls it back to LOW, we begin data transmission

## reading input

### 0 and 1 representation

At first, the DHT11 keeps the voltage LOW for 50 microseconds

After that, it pull it HIGH

- a 0 means, it pulls it HIGH for 26 to 28 microseconds, then back to LOW
- a 1 means, it pulls it HIGH for 70 microseconds

```
(27 + 70)/2 = 48.5
```

Let's say that anywhere below 48.5 is 0, otherwise is considered HIGH

- complete data transmission is 40 bits
- one communication process is 40 ms

```
[8bit integral RH data][8bit decimal RH data][8bie integral T data][8bit decimal T data][8bit check sum]
```

checksum is computed like:

```
(0x41 + 0x07 + 0x21 + 0x01) & ((1 << 9) - 1)
```


