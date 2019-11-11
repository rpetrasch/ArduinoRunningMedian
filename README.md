# Running / Sliding Median for Arduino ![Logo for Running / Sliding Median for Arduino](https://github.com/rpetrasch/ArduinoRunningMedian/blob/master/ArduinoRunningMedianLogo.png?raw=true)

A simple heap and running median (min/max heaps) implementation that can be used on small development boards like Arduino UNO. 

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

If you want to test the library and the main program locally on your desktion machine, you will need the a C++17 development environment like IntelliJ CLion.
More info on C++17 ia available on [isocpp.org website](https://isocpp.org/std/the-standard) 

### Installing

Compile, build, and run the main program (test)

Use the zip file for the Arduino and check out the examples.
- Download [Arduino zip file](https://github.com/rpetrasch/ArduinoRunningMedian/raw/master/ArduinoRunningMedian.zip)
- Open your Arduino IDE: Sketch->Include Library-> Add .ZIP Library
- Select the file ArduinoRunningMedian.zip
- Open the simple example: File->Examples->ArduinoRunningMedian->simpleMedian
- Upload the sketch on your target and open the serial monitor. You should see something like this:
```
--------------------------------
Running Median - Test
--------------------------------
Element:    5 	 Median:    5
Element:   15 	 Median:   10
Element:    1 	 Median:    5
...
```

More infos coming soon...


## Running the tests

Compile, build, and run the main program. That's all for now. There will be proper Catch2 tests very soon.
For more infos visit [catch2 website](https://github.com/catchorg/Catch2) 

## Deployment

Here we will describe the Arduino scenarios in detail.

## Built With

* [CLion](https://www.jetbrains.com/clion/) - IntelliJ C and C++ IDE
* [Arduino IDE](https://www.arduino.cc/en/main/software) - Arduino IDE
+ g++ (Ubuntu 9.2.1-9ubuntu2) 9.2.1 20191008 - Free Software Foundation C++ compiler

## Versioning

We use git 2.20. 

## Authors

* **Roland Petrasch** - *Initial work* - [ResearchGate](https://www.researchgate.net/profile/Roland_Petrasch)

## License

This project is licensed under the GPL3 License - see the [LICENSE](LICENSE.GPL3) file for details

## Acknowledgments

* Thanks to the friendly folks from [AMDIS Media and IT Services](www.amdis-services.com) for their support 
