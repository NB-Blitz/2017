#include "WPILib.h"
#include "manipulator.hpp"

FRC::manipulator::manipulator(): //Declare Object Ports

inputManager(),
gear(5),
climbMotor(2),
pot(0)

{

}

//Climb
void FRC::manipulator::climb()
{
	float cmd = 0;

	//Check if controller axis is moved and motor currents < 50
	if (inputManager.xBox.GetRawAxis(2) > .95)
	{
		cmd = 1.0;
	}
	else if (inputManager.xBox.GetRawAxis(2) <= .9 && inputManager.xBox.GetRawAxis(2) > .1)
	{
		cmd = 0.2;
	}
	else
	{
		cmd = 0.0;
	}

	if (PDP.GetCurrent(0) < 50 && PDP.GetCurrent(1) < 50)
	{
		climbMotor.Set(cmd);
	}
	else
	{
		climbMotor.Set(0.0);
	}
}

//Bring manipulator back until it hits specified pot value
void FRC::manipulator::GearReset(double speed)
{
	if (pot.GetValue() > 250)
	{
		gear.Set(speed * -0.4); //Change number for constraints
	}
	else
	{
		gear.Set(0);
	}
}

//Bring manipulator forward until it hits specified pot value
void FRC::manipulator::GearOut(double speed)
{
	if (pot.GetValue() < 3900)
	{
		gear.Set(speed * -0.5); //Change number for constraints
	}
	else
	{
		gear.Set(0);
	}
}
