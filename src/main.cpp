#include "main.h"
// #include "Optical_sensor.hpp"

// Toggle this to switch between your student program and your test program.
constexpr bool kUseTestCode = true;
// constexpr bool kUseOpticalSensor = !kUseTestCode;

void OverRideMainPrograming();


void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(0, kUseTestCode ? "Mode: TEST" : "Mode: STUDENT");
	// if (kUseOpticalSensor) {
	// 	optical_sensor::initialize();
	// }

	if (kUseTestCode) {
		OverRideMainPrograming();
	}// else {
	// 	initialize_student();
	// }
}

