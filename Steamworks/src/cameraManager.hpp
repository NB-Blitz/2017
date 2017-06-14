/*
 * cameraManager.hpp
 *
 *  Created on: Feb 18, 2017
 *      Author: Robotics
 */

#ifndef SRC_CAMERAMANAGER_HPP_
#define SRC_CAMERAMANAGER_HPP_

#include "WPILib.h"
#include "driveManager.hpp"

namespace FRC
{
	class cameraManager
	{
		public:
			cameraManager();
			//Function Declarations
			double getDistFromCenter();
	};
}
#endif /* SRC_CAMERAMANAGER_HPP_ */
