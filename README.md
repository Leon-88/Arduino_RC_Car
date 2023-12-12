# Bluetooth Controlled RC Car Made With Arduino

> Updated: 11/3/2023

## About

This program is intended to be loaded onto a arduino uno and used to control an RC car over bluetooth.
The program revolves around a few basic functions which control one type of motion:

- Forward
- Backward
- Left
- Right
- FrontLeft
- FrontRight
- BackLeft
- BackRight

## Implementation

The program is made to accept inputs from the [Bluetooth RC Car](https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller) phone application available on the Google play store for Android. It is written for Ardunion devices using the C++ programming language.

The construction of the car is simple and straightforward, using the following components.

## Build Of Materials

| Item                                   | Count |
| -------------------------------------- | ----- |
| Arduino Uno                            | 1     |
| L293D Motor driver                     | 1     |
| Breadboard                             | 1     |
| Motor                                  | 4     |
| Wheel                                  | 4     |
| 9 Volt Battery                         | 1     |
| 4"x 6" x 0.5" piece of wood or plastic | 1     |
| Green Led (Optional)                   | 1     |
| Blue Led (Optional)                    | 1     |
| Red Led (Optional)                     | 1     |

## Reference

- TI L293D Data Sheet https://www.ti.com/product/L293D#features
- L293D with gear motor control: https://srituhobby.com
- Instructables build: https://www.instructables.com/RC-Car-Using-L293D-HC-05/
- YouTube https://www.youtube.com/results?search_query=L293D

## Dependencies

The program does not rely on any libraries. However, is to be run on a certain set of hardware, which may be catagorized as a dependency. See the BOM above.

## Disclaimer/ Warning

Run program at your own risk. Incorrect wiring or difference in hardware may result in damage to equipment. This software is only intended to run with the circuit depicted in the reference photos. This software has changed since it has last been tested, so follow up testing and tweaking should be expected from users who implement this project.

## License

This project is licensed under the GNU General Public License v3.0. See the LICENSE file for more info.
