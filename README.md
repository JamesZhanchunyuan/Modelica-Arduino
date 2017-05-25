# Simulate Arduino Sketches in Modelica

The Arduino Modelica library lets you simulate your circuits and sketches on a virtual [Arduino Uno](https://www.arduino.cc/en/Main/ArduinoBoardUno)

![Circuit w/ Arduino](Arduino/Resources/Images/led_circuit.png)

## Prerequisites

- [Dymola](https://www.3ds.com/products-services/catia/products/dymola) 2017 FD01 or 2018
- Visual Studio 2012

## Getting Started

- Download the [latest release](releases/latest) and extract the archive
- In Dymola select `File > Open...` and open `Arduino/package.mo` from the extracted files
- In the package browser double-click `Arduino.Examples.Blink`
- Right-click on the toolbar and check `Simulation` and `Animation` to view the simulation and animation toolbars
- Click ![Simulate Button](Arduino/Resources/Images/simulate_button.png) to run the Simulation
- After the simulation has finished click ![Run Button](Arduino/Resources/Images/run_button.png) in the animation toolbar and watch the LED `L` blink
- Try the other examples in `Arduino.Examples`


## Simulate your Sketch

To simulate your sketch `MySketch` you have to perform the following steps.

- Save your sketch as `Sketches/MySketch.ino`
- Add the block `Arduino.Components.ArduinoUno` to your model
- Double-click the block and set the parameter `sketch` to `"MySketch.ino"`


## Limitations

- Currently you can use only one instance of ArduinoUno in your Modelica model

- The whole [Arduino API](https://www.arduino.cc/en/Reference/HomePage) is supported except for the following functions

	- [analogReadResolution()](https://www.arduino.cc/en/Reference/AnalogReadResolution)
	- [analogWriteResolution()](https://www.arduino.cc/en/Reference/AnalogWriteResolution)
	- [tone()](https://www.arduino.cc/en/Reference/Tone)
	- [noTone()](https://www.arduino.cc/en/Reference/NoTone)
	- [shiftOut()](https://www.arduino.cc/en/Reference/ShiftOut)
	- [shiftIn()](https://www.arduino.cc/en/Reference/ShiftIn)
	- [isWhitespace()](https://www.arduino.cc/en/Reference/IsWhitespace)
	- [Serial](https://www.arduino.cc/en/Reference/Serial) `print(), println() and write() are supported`
	- [Stream](https://www.arduino.cc/en/Reference/Stream)
	- [Keyboard](https://www.arduino.cc/en/Reference/MouseKeyboard)
	- [Mouse](https://www.arduino.cc/en/Reference/MouseKeyboard)

## Using Libraries

To use a library in your sketch copy its header files (`*.h`) and source files (`*.cpp`) to the `Libraries` folder. If the library contains `.cpp` files you have to add them to the `Arduino` project by dragging them from the `Libraries` folder in the file browser onto the `Source Files` folder in the solution explorer.

## License

The code is licensed [GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html), the documentation [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/).

----------------------------

Developed by Torsten Sommer at [Dassault Systèmes](https://www.3ds.com/). Copyright &copy; 2017 Dassault Systèmes.
