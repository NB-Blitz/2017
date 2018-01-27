/*
 * ballShooter.hpp
 *
 *  Created on: Sep 19, 2017
 *      Author: Kevin
 */

#ifndef SRC_BALLSHOOTER_HPP_
#define SRC_BALLSHOOTER_HPP_

#include "DigitalInput.h"
#include "Talon.h"
#include "inputManager.hpp"

namespace FRC{

	class ballShooter{

		public:
			ballShooter();

			//Object Declarations
			FRC::inputManager inputManager;
			Talon intake;

			//Function Declarations
			void controlSpeed;
			void stop;

	};
}




#endif /* SRC_BALLSHOOTER_HPP_ */
