/*
 * ballShooter.cpp
 *
 *  Created on: Sep 19, 2017
 *      Author: Kevin
 */
#include "ballShooter.hpp"
#include "WPILib.h"
#include "inputManager.hpp"

FRC::ballShooter::ballShooter():

inputManager(),
intake(0)

{

}

void FRC::ballShooter::controlSpeed()
{
	if(inputManager.xBox.GetRawAxis(1) >= 0)
	{

		intake.SetSpeed(inputManager.xBox.GetRawAxis(1));//Rolls in one direction. Probably.

	}
}

void FRC::ballShooter::stop()
{

	intake.SetSpeed(0);//For emergency or regular purposes, hit the stop button. We don't have a brake though, so do not expect it to stop at once.

}
