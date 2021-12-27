// This program takes the file AL_Weather_Station.txt, which is stored
// in the folder Temp.  This file contains a list of weather data.
//
// This program filters out any data entries that have invalid data
// for the fields PRCP (precipitation), TMAX (maximum temperature), or 
// TMIN (minimum temperature).  A field of invalid data is flagged by
// the value -9999.
//
// A new file called Filtered_AL_Weather_Station.txt that containns the
// weather station data with invalid lines omitted is stored in the Temp
// folder.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main(void)
{
	// Variables

	string dataline = ""; 
	string station = "";

	string prcp_s = " ", tmax_s = "", tmin_s = "";

	unsigned int pos_station_name = 0;
	unsigned int pos_date = 0;
	unsigned int pos_prcp = 0;
	unsigned int pos_tmax = 0;
	unsigned int pos_tmin = 0;
	unsigned int bad_records = 0;

	float prcp = 0, tmax = 0, tmin = 0;

	ifstream infile;
	ofstream outfile;

	cout << "WEATHER STATION DATA" << endl << endl;
	// Open the data file.
	infile.open("C:/Temp/AL_Weather_Station.txt");

	if (!infile)
	{
		cout << "Unable to open the input file. " << endl;
		system("pause");
		return(1);
	}
	else
	{
		cout << "Data file opened." << endl;
	}

	outfile.open("C:/Temp/Filtered_AL_Weather_Station.txt");

	if (!outfile)
	{
		cout << "Unable to open the output file. " << endl;
		system("pause");
		return(1);
	}
	else
	{
		cout << "Output file opened." << endl;
	}

	// Use the first line of the file to find the column positions.
	getline(infile, dataline);
	outfile << dataline << endl;

	// Use headers to fine prcp and max/min temp columns
	pos_prcp = dataline.find("PRCP");
	if (pos_prcp > dataline.length())
	{
		cout << "PRCP not found." << endl;
		return 2;
	}

	pos_tmax = dataline.find("TMAX");
	if (pos_tmax > dataline.length())
	{
		cout << "TMAX not found." << endl;
		return 2;
	}

	pos_tmin = dataline.find("TMIN");
	if (pos_tmin > dataline.length())
	{
		cout << "TMIN not found." << endl;
		return 2;
	}

	// Read the second line from the file.

	getline(infile, dataline);
	outfile << dataline << endl;

	// Now process the data records from the file


	while (!infile.eof())
	{
		// Read the lines with data
		getline(infile, dataline);

		// Extract prcp, tmax and tmin from dataline
		prcp_s = dataline.substr(pos_prcp, 5);
		tmax_s = dataline.substr(pos_tmax, 5);
		tmin_s = dataline.substr(pos_tmin, 5);

		// Convert the string types to float
		prcp = stof(prcp_s); // Convert string prcp_s to float prcp
		tmax = stof(tmax_s); // Convert string tmax_s to float tmax
		tmin = stof(tmin_s); // Convert string tmin_s to float tmin

		// NOTE: to convert string to int use stoi
		//       to convert string to double use stod

		// Test for bad data flag.  If good data then write to new file.

		if (prcp != -9999 && tmax != -9999 && tmin != -9999)
			outfile << dataline << endl;
		else
			bad_records++;

	} // End While 

	// Close the files
	infile.close();
	outfile.close();

	cout << "New file created with bad records filtered out. " << endl;
	cout << "There were " << bad_records << " filtered out." << endl;

	system("pause");
	return 0;
}
