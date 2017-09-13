#include "WPILib.h"
#include "inputManager.hpp"
#include "cmath"

FRC::inputManager::inputManager(): //Declare Object Ports

joyStick(0),
xBox(1)

{

}

void FRC::inputManager::getData(){
	if(joyStick.GetRawAxis(0) < .1)
	{
		joyX = 0;
	}
	else
	{
		joyX = joyStick.GetRawAxis(0);
	}

	if(joyStick.GetRawAxis(1) < .1)
	{
		joyY = 0;
	}
	else
	{
		joyY = joyStick.GetRawAxis(1);
	}

	if(joyStick.GetRawAxis(2) < .1)
	{
		joyZ = 0;
	}
	else
	{
		joyZ = joyStick.GetRawAxis(2);
	}
}
