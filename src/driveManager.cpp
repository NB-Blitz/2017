#include "WPILib.h"
#include "driveManager.hpp"
#include "inputManager.hpp"
#include "cmath"
#include "cstdbool"
#include "cstdlib"
#include "CanTalon.h"
#include "AHRS.h"

FRC::driveManager::driveManager(): //Declare Object Ports

leftBackM(3),			//FIX
leftFrontM(1),			//THIS
rightBackM(4),			//WARNING!!!
rightFrontM(2),
ahrs {SPI::Port::kMXP},
inputManager()

{

}

//Get NavBoard Angle
float FRC::driveManager::getAngle()
{
	return ahrs.GetFusedHeading();
}

//Quick stop and prevent drift
void FRC::driveManager::PIcorrection(int id)
{
	double const RateFrequency = 2000; //target Velocity
	double propGain = 1.0; //Proportional multiplier
	double const MaxHz = 2600.0; // max Hz

	if(speeds[id] - preSpeed[id] > .1)
	{
		propGain = 4;
	}
	else
	{
		propGain = 1.5;
	}

	spdRef[id] = speeds[id] * (RateFrequency/MaxHz);

	SPFeedBack[id] = EncoderFreq[id]/RateFrequency;

	error[id] = spdRef[id] - SPFeedBack[id];

	propOut[id] = error[id] * propGain;

	PIout[id] = propOut[id];

	PWMout[id] = spdRef[id] + PIout[id];

	preSpeed[id] = speeds[id];
}

//Slow increase in speed
void FRC::driveManager::ramp()
{
	double deadBand = 0.2;	//deadband range
	double rampRate = 1/(.05 * 200.0); //.5 = time in seconds, 200 = scan rate

	JoyXRaw = dir * (inputManager.JoyStick.GetRawAxis(1));
	JoyYRaw = dir * (-inputManager.JoyStick.GetRawAxis(0));
	JoyRotateRaw = -(inputManager.JoyStick.GetRawAxis(2) * .75);

	//Left X axis
	if(fabs(JoyXRaw) < deadBand)
	{
		JoyXRaw = 0;
	}
	if(JoyXRaw + .02 >= JoyX && JoyXRaw - .02 <= JoyX)
	{
		//WAT???????????????
	}
	else if(JoyXRaw > JoyX)
	{
		JoyX += rampRate;
	}
	else
	{
		JoyX -= rampRate;
	}

	//Left Y axis
	if(fabs(JoyYRaw) < deadBand)
	{
		JoyYRaw = 0;
	}
	if(JoyYRaw + .02 >= JoyY && JoyYRaw - .02 <= JoyY)
	{
		//WAT???????????????
	}
	else if(JoyYRaw > JoyY)
	{
		JoyY += rampRate;
	}
	else
	{
		JoyY -= rampRate;
	}

	//Right X axis
	if(fabs(JoyRotateRaw) < .1)
	{
		JoyRotateRaw = 0;
	}
	if(JoyRotateRaw + .02 >= joyRotate && JoyRotateRaw - .02 <= joyRotate)
	{
		//WAT???????????????
	}
	else if(JoyRotateRaw > joyRotate)
	{
		joyRotate += rampRate;
	}
	else
	{
		joyRotate -= rampRate;
	}
}

//Perform mecanum drive with joystick input
void FRC::driveManager::mecanumDrive(double y, double x, double rotate, bool bypass)
{
	double const Pow = 1;

	if(fabs(rotate) < .1)
	{
		rotation = 0.05 * (delta)+ .012 *ahrs.GetRate();

		//Mecanum equation(Left side inverted)
		speeds[0] = x + y - rotation;//Left Front
		speeds[1] = -(-x + y + rotation); //Left Rear
		speeds[2] = -x + y - rotation; //Right Front
		speeds[3] = -(x + y + rotation); //Right Rear

		//Normalize function: keeps values proportional and below 1
		maxMagnitude = std::fabs(FRC::driveManager::speeds[0]);
		int i;

		for (i = 1; i < 4; i++)
		{
			double temp = std::fabs(speeds[i]);
			if (maxMagnitude < temp)
			{
				maxMagnitude = temp;
			}
		}
		if (maxMagnitude > 1.0)
		{
			for (i = 0; i < 4; i++)
			{
				speeds[i] = speeds[i] / maxMagnitude;
			}
		}

		if(!bypass)
		{
			EncoderFreq[0] = leftFrontM.GetEncVel(); //Left Front
			EncoderFreq[1] = -leftBackM.GetEncVel(); //Left Rear
			EncoderFreq[2] = rightFrontM.GetEncVel(); //Right Front
			EncoderFreq[3] = -rightBackM.GetEncVel(); //Right Rear

			SmartDashboard::PutNumber("Left Front Enc Vel", EncoderFreq[0]);
			SmartDashboard::PutNumber("Left Back Enc Vel", EncoderFreq[1]);
			SmartDashboard::PutNumber("Right Front Enc Vel", EncoderFreq[2]);
			SmartDashboard::PutNumber("Right Back Enc Vel", EncoderFreq[3]);

			PIcorrection(0);
			PIcorrection(1);
			PIcorrection(2);
			PIcorrection(3);

			leftFrontM.Set(PWMout[0] * Pow);
			leftBackM.Set(PWMout[1] * Pow);
			rightFrontM.Set(PWMout[2] * Pow);
			rightBackM.Set(PWMout[3] * Pow);
		}
		else
		{
			leftFrontM.Set(speeds[0] * Pow);
			leftBackM.Set(speeds[1] * Pow);
			rightFrontM.Set(speeds[2] * Pow);
			rightBackM.Set(speeds[3] * Pow);
		}
	}
	else
	{
		leftFrontM.Set(x + y + rotate);
		leftBackM.Set(-(-x + y - rotate));
		rightFrontM.Set(-x + y + rotate);
		rightBackM.Set(-(x + y - rotate));
	}
}

//Drive perfectly straight
void FRC::driveManager::straightDrive(double PreAngle, double x, double y)
{
	delta = PreAngle - getAngle();

	ramp();

	if(fabs(delta) > 180 && delta > 0)
	{
		delta = -(360 - fabs(delta));
	}
	else if(fabs(delta) > 180 && delta < 0)
	{
		delta = 360 - delta;
	}

	rotation = 0.04 * delta;

	if(fabs(y) > fabs(x))
	{
		mecanumDrive(y, 0, -rotation, true);
	}
	else
	{
		mecanumDrive(0, x, -rotation, true);
	}
}

//Reset encoder positions
void FRC::driveManager::resetEnc()
{
	leftFrontM.SetEncPosition(0);
	leftBackM.SetEncPosition(0);
	rightFrontM.SetEncPosition(0);
	rightBackM.SetEncPosition(0);
}

//Field-Oriented Contols
void FRC::driveManager::FieldControl(double x, double y, double rotate)
{
	double r = sqrt(pow(x, 2) + pow(y, 2));

	if(inputManager.JoyStick.GetDirectionDegrees() < 0)
	{
		ang = 360 + inputManager.JoyStick.GetDirectionDegrees();
	}
	else
	{
		ang = inputManager.JoyStick.GetDirectionDegrees();
	}

	ang -= getAngle();

	x = r * cos(ang * (pi/180));
	y= r * sin(ang * (pi/180));

	mecanumDrive(-y, -x, rotate, false);
}
