# Changelog

## Unreleased

- **Note:** Unreleased changes are checked in but not part of an official release (available through the Arduino IDE or PlatfomIO) yet. This allows you to test WiP features and give feedback to them.

- none

## [1.3.2] - 2023-06-26

- updated `setup()`now uses `const char*`

## [1.3.1] - 2021-09-12

- removed `Arduino.h` include in `OTAWrapper.h` file
- added default case to `switch` in `errorToString()`
- changed `char*` to `String` in `setup()` and convert them to `const char` inside the function

## [1.3.0] - 2020-01-09

- added M5Stack example
- added simple example

## [1.2.0] - 2020-12-31

- added `getProgress()` function
- updated the example

## [1.1.1] - 2020-09-01

- added blinking LED detection

## [1.0.0] - 2020-07-15

- initial release

## About

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).
