Learning by doing fun with 7 segment display and 74HC595 Shift Register. Made this Temperature and Humidity thing with an ATtiny 85 and a 74HC595 Shift Register. It displays alternating temperature and humidity with decimal point if nessesairy. How to address the 7 segments and measure sensor readings with only 5 free pins on an ATTiny85? These articles helped me to find the solution:
<BR><BR>https://www.electronicwings.com/users/SMRITISINGH/projects/1309/dice-using-7-segment-display-and-attiny85
<BR>https://www.youtube.com/watch?v=yi_e0TZ0uKw
<BR>https://www.tinkercad.com/things/jz9WaizxM4N-dice-with-7segment-display-and-attiny85/editel
<BR>https://iotprojectsideas.com/mini-weather-station-using-dht22-attiny85/
<BR>
<BR>Used Asiar AM2122 because it was the only one I could find that runs on a 3v cell. The 7-segment display is common anode but in the .ino you can change it to common cathode. There is an .stl if you want to 3D print a simple stand. Used the Fritzing schematic I made and not the Tinkercad one wich is a tiny bit different. Use .8 or .5mm brass wire.

<img src="https://github.com/gtmans/ATTiny7segBitshift/blob/main/ATTiny7segBitshiftPic.jpg" width="600">
<img src="https://github.com/gtmans/ATTiny7segBitshift/blob/main/ATTiny7segBitshift-breadboard.png" width="600">

![temphum](https://github.com/gtmans/ATTiny7segBitshift/blob/main/ATTiny7segBitshift.png)<BR>
![temphum](https://github.com/gtmans/ATTiny7segBitshift/blob/main/ATTiny7segBitshift-FRITZING.png)<BR>

<img src="https://github.com/gtmans/ATTiny7segBitshift/blob/main/ATTiny7segBitshiftPic2.jpg"><BR>
<img src="https://github.com/gtmans/ATTiny7segBitshift/blob/main/ATTiny7segBitshiftPic-back.jpg">
