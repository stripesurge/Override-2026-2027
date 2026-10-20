#include <cmath>
#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

//Motors
pros::Motor front_left_drive(1, pros::v5::MotorGears::blue);
pros::Motor back_left_drive(2, pros::v5::MotorGears::blue);
pros::Motor left_dr4b(-3, pros::v5::MotorGears::red);
pros::Motor right_dr4b(4, pros::v5::MotorGears::red);
pros::Motor intake_1(5, pros::v5::MotorGears::green);
pros::Motor intake_2(6, pros::v5::MotorGears::green);
pros::Motor front_right_drive(-11, pros::v5::MotorGears::blue);
pros::Motor back_right_drive(-12, pros::v5::MotorGears::blue);
pros::Motor intake_3(13, pros::v5::MotorGear::green);
pros::Motor intake_4(-14, pros::v5::MotorGear::green);


//Pneumatics
pros::adi::Pneumatics claw('C', false);
pros::adi::Pneumatics invert('A', false); // To invert which side is up
pros::adi::Pneumatics flip('B', false); // To flip the cup and pin upright

float gw = 0; // Setpoint (Genghis Wong)

double gotoHeight(float height){ //f^-1 (h)
	float L1 = 375.0; //length in mm
	float L2 = 150.0;
	float L3 = 385.0;
	float gr = 1/7; //#grrrmondays
	float point = (height-L2)/(L1+L3);
	return gr * asinf(point); //theta
}

// void bangBang(float setPoint){
// 	int d4rb_power = 0;
// 	const int error = 900;
// 	// Declan BLAINE "Higgs" "Genghis" Wong
// 	if (setPoint>right_dr4b.get_position() +error) {
// 		d4rb_power = 127;
// 	} else if (setPoint<right_dr4b.get_position() -error){
// 		d4rb_power = -127;
// 	} else {
// 		d4rb_power = 0;
// 	}
// 	right_dr4b.move(d4rb_power);
// 	left_dr4b.move(d4rb_power);
// }


void opcontrol() {
	
	float h = 0.0;
	right_dr4b.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	left_dr4b.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	int dr4b_power;
	while (true) {
		const int forward = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		const int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		const int left_power = forward + turn;
		const int right_power = forward - turn;

		front_left_drive.move(-left_power);
		back_left_drive.move(-left_power);
		front_right_drive.move(-right_power);
		back_right_drive.move(-right_power);

		int intake_power = 0;
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
			intake_power = -127;
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
			intake_power = 127;
		}

		intake_1.move(intake_power);
		intake_2.move(intake_power);
		intake_3.move(intake_power);
		intake_4.move(intake_power);

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			dr4b_power = -127;
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			dr4b_power = 127;
		} else {
			dr4b_power = 0;
		}
		left_dr4b.move(dr4b_power);
		right_dr4b.move(dr4b_power);
		// bangBang(gw);

		/*Claw controls: 
			B -> Open
			A -> Invert colour on top
			Y -> Flip claw upright/down
			X -> Make claw go to bottom and pick up cup & pin
		*/
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
			claw.toggle();
			pros::delay(200);
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
			invert.toggle();
			pros::delay(200);
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
			flip.toggle();
			pros::delay(200);
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
			// double offset = 20.0;
			// flip.retract();
			// claw.retract();

			double angle = gotoHeight(1000);
			right_dr4b.move_absolute(angle, 100);
			left_dr4b.move_absolute(-angle, 100);

			// pros::delay(500);
			// claw.extend();
			
			// double angle = gotoHeight(h+offset);
			// right_dr4b.move_absolute(angle, 100);
			// left_dr4b.move_absolute(-angle, 100);
			// flip.extend();
		}




		pros::delay(20);
	}
}

void move(){

	
}

void autonomous(){
	right_dr4b.tare_position();
	left_dr4b.tare_position();
	right_dr4b.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	left_dr4b.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	int dr4b_power = -127;
	left_dr4b.move(dr4b_power);
	right_dr4b.move(dr4b_power);
	pros::delay(900);
	left_dr4b.move( 0);
	right_dr4b.move(0);
	pros::delay(700);
	dr4b_power = 127;
	left_dr4b.move(dr4b_power);
	right_dr4b.move(dr4b_power);
	pros::delay(900);
	left_dr4b.move( 0);
	right_dr4b.move(0);

} 