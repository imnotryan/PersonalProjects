# Welcome to my Water Level Sensor project!
Thank you Naziul Jeead and Daniel Jahren for helping me come up with this project idea, and for draw.io as they have excellent schematic-drawing software!

This project was done on a breadboard, so any permanent circuit one wishes to make will need to be modified with a surface-mount PCB. Also, external batteries are needed to keep this project running when the power eventually goes out when a flood comes. C++ is used for all the software.

### Description:

My house flooded in the summers of 2018, 2019, and 2020, with 2018 and 2019 being from major storms, and 2020 being from Hurricane Hannah.
We have flood insurance, but some random insurance adjuster from Alabama (I'm from Texas) came into our house, looked around for a few hours, and decided to give us money 
to compensate for our flood damage. This man was unknown to my family and I, and we relied completely on him to evaluate our flood damage. 

What if the insurance adjuster was feeling sick?
What if the insurance adjuster was having a bad day?
What if the insurance adjuster was told to give us less money because the company would go bankrupt?
All our money paid to our flood insurance over the years would be for nothing if we weren't given the proper amount of money to pay for the flood damage that we had over three
years. 

Therefore, this Water Level Sensor is meant to further verify flood insurance adjuster's claims on how much damage was done to one's house to get a more accurate account of how
much damage was done to a building, by measuring the maximum water height that entered the building. This Water Level Sensor measures the water height once an hour, every hour
for 3 days and then displays the highest water height (that entered the house) in both centimeters and inches until the reset button is pushed. It also displays the date, day of
week, and time that the highest water level was measured.

There is also a 'display' button, that shows the current highest water level, in case you want to view the highest water level so far, even if three days haven't passed. The
reset button resets the highest water level and restarts the measuring process. To get started, have the Water Level Sensor measure about 1cm of water for at least 10 seconds,
which will prompt the software to begin taking measurements for the next three days. 


### Hardware used in this project (prices are as of June 2021 in USD):


- 1x Arduino ATmega 2560 microcontroller with USB cable ($15.99 on Amazon)

- 1x 830-point breadboard (About $10 on Amazon)

- 1x LCD 1602 (Liquis Crystal Display) ($7.99 on Amazon)

- 5x 10KΩ resistors ($4.99 on Amazon)

- 2x Pushbuttons (Less than $10 on Amazon)

- 1x Water Level Detector Module (Less than $10 on Amazon)

- 1x DS3231 Real Time Clock (RTC) module (About $10 on Amazon)

- 7x Female to Male DuPont wires 

- 21x Male to Male DuPont wires (F to M and M to M for $6.99 total on Amazon)

-LCD software driver can be found in Arduino's Library Manager

### Important links: 

http://www.rinkydinkelectronics.com/library.php?id=73 --> DS3231 RTC software and hardware connections
https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/ --> how to configure pins as input/output 
https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/ --> make pins output a voltage
https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/ --> read a voltage from pins
https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/ --> attach interrupt to a pin


- !!Look at pictures in this repository to see hardware connections!!

### Advantages of this project:
- Realtively cheap construction, total cost is under $40 for guaranteeing tens of thousands of dollars in flood damage compensation
- Water Level Sensor, in case of degradation, can be replaced easily
- Real Time Clock module's nickel battery keeps accurate time (up to seconds in accuracy) for up to one year without recharging
- Parts for replacement are cheap on Amazon, Digikey, or Mouser

### Limitations of this project: 
- The Water Level Sensor is cheap and therefore of poor quality. The ADC values that the Arduino's chip measures are not consistent, even when measuring the same water level
with many trials. Therefore, the water level measured by the Water Level Sensor is inaccurate by at least 1cm.

- The Water Level Sensor works by running current through exposed PCB copper traces through the positive voltage traces. Once water touches this trace, it creates a path
to the other, exposed ground traces, thus creating a varying voltage drop (that is dependent on the water level) across a resistor that is hooked up to the Arduino's ADC. The
ADC measures this varying voltage drop, thereby measuring the water level. However, since we are exposing copper, which tarnishes, to water over a long period of time, 
the copper corrodes and eventually comes off the PCB, making it impossible to measure any water level. 

- Finally, pure water is an insulator, but since flood water is generally very dirty, it will conduct electricity. The water conductivity depends on the material in it,
making the Water Level Sensor inaccurate depending on the amount and type of contaminents it has. 










