/*
 * BlitzLogger.cpp
 *
 *  Created on: Aug 5, 2017
 *      Author: Sam
 */

FRC::BlitzLogger::BlitzLogger()
{

}

void FRC::BlitzLogger::init(bool debugMode)
{
	logfile.open("Placeholder.txt");
	writeDebugMessage = debugMode;
}

void FRC::BlitzLogger::info(char message[])
{
	logfile << "[placeholder for Timestamp]"; //writes timestamp to file
	logfile << " "; //Separating time stamp and message type
	logfile << "[Info]"; //Message Type
	logfile << " "; //Separating message type and message
	logfile << message; //Writes message to file
	logfile << "\n"; //Sets writing location to next line for next log message
}

void FRC::BlitzLogger::debug(char message[])
{
	if(writeDebugMessage)
	{
		logfile << "[placeholder for Timestamp]"; //writes timestamp to file
		logfile << " "; //Separating time stamp and message type
		logfile << "[Debug]"; //Message Type
		logfile << " "; //Separating message type and message
		logfile << message; //Writes message to file
		logfile << "\n"; //Sets writing location to next line for next log message
	}
}

void FRC::BlitzLogger::warning(char message[])
{
	logfile << "[placeholder for Timestamp]"; //writes timestamp to file
	logfile << " "; //Separating time stamp and message type
	logfile << "[Warning]"; //Message Type
	logfile << " "; //Separating message type and message
	logfile << message; //Writes message to file
	logfile << "\n"; //Sets writing location to next line for next log message
}

void FRC::BlitzLogger::error(char message[])
{
	logfile << "[placeholder for Timestamp]"; //writes timestamp to file
	logfile << " "; //Separating time stamp and message type
	logfile << "[Error]"; //Message Type
	logfile << " "; //Separating message type and message
	logfile << message; //Writes message to file
	logfile << "\n"; //Sets writing location to next line for next log message
}


