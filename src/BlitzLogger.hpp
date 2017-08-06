/*
 * BlitzLogger.hpp
 *
 *  Created on: Aug 5, 2017
 *      Author: Sam
 */

#ifndef SRC_BLITZLOGGER_HPP_
#define SRC_BLITZLOGGER_HPP_

#include "WPILib.h"
#include <iostream>
#include <fstream>

namespace FRC
{
	class BlitzLogger
	{
	public :
		BlitzLogger();

		//Variables
		std::ofstream logfile;
		bool writeDebugMessage = false;

		//Non-logging functions
		void init(bool debugMode);
		void close();

		//Logging Functions
		void info(char message[]);
		void debug(char message[]);
		void warning(char message[]);
		void error(char message[]);
	};
}




#endif /* SRC_BLITZLOGGER_HPP_ */
