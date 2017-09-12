#include "WPILib.h"
#include "inputManager.hpp"
#include "cmath"

FRC::inputManager::inputManager(): //Declare Object Ports

joyStick(0),
xBox(1)

{

}

void FRC::inputManager::getData(){
	joyX = joyStick.GetRawAxis(0);
	joyY = joyStick.GetRawAxis(1);
	joyZ = joyStick.GetRawAxis(2);
}
