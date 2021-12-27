// Takes the chart stored in Filtered_AL_Weather_Station.txt
// in file Temp.  Keeps the information for station name, date,
// precipitation, maximum temperature, and minimum temperature and
// makes a new five-column chart.  In this new chart, the termperatures
// are converted from Celsius into Fahrenheit.  This new chart
// is then stored in weather_station_five_column.txt in file Temp.


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main(void)
{
	string dataline = "";  // A line of data from the original chart

	// The index of the start of the various columns
	int name_start = 0;
	int name_end = 0;
	int date_start = 0;
	int prcp_start = 0;
	int tmax_start = 0;
	int tmin_start = 0;

	// The data in the various columns as strings
	string station_name = "";
	string s_date = "";
	string s_prcp = "";
	string s_tmin = "";
	string s_tmax = "";

	// Strings for the year, month, and day contained
	// in the date.
	string s_year = "";
	string s_month = "";
	string s_day = "";
	
	// The mimimum and maximum temperature in degrees Celsius
	float tmax_celsius = 0, tmin_celsius = 0; 

	// The minimum and maximum temperature in degrees Farenheit
	float tmax_farenheit = 0, tmin_farenheit = 0;

	// The input and output files.
	ifstream infile;
	ofstream outfile;

	// Open the data file.
	infile.open("C:/Temp/Filtered_AL_Weather_Station.txt");
	if (!infile) {
		cout << "Unable to open the input file." << endl;
		system("pause");
		return 1;
	}
	else {
		cout << "Data file opened." << endl;
	}

	// Open the output file.
	outfile.open("C:/Temp/weather_station_five_column.txt");

	if (!outfile){
		cout << "Unable to open the output file." << endl;
		system("pause");
		return 1;
	}
	else {
		cout << "Output file opened." << endl;
	}


	// Output the heading for the new chart.
	outfile << setw(22) << "STATION NAME" << setw(29) << "DATE"
		<< setw(11) << "PRCP" << setw(6) << "TMAX" << setw(7)
		<< "TMIN" << endl;

	// Use the heading in the original file to find the starting
	// position for the needed columns

	getline(infile, dataline);
	name_start = dataline.find("STATION_NAME");
	if (name_start == string::npos) {
		cout << "Station name column not found." << endl;
		system("pause");
		return 2;
	}

	date_start = dataline.find("DATE");
	if (date_start == string::npos) {
		cout << "Date column not found." << endl;
		system("pause");
		return 2;
	}

	prcp_start = dataline.find("PRCP");
	if (prcp_start == string::npos) {
		cout << "Precipitation column not found." << endl;
		system("pause");
		return 2;
	}

	tmax_start = dataline.find("TMAX");
	if (tmax_start == string::npos) {
		cout << "Maximum temperature column not found." << endl;
		system("pause");
		return 2;
	}

	tmin_start = dataline.find("TMIN");
	if (tmin_start == string::npos) {
		cout << "Minimum temperature column not found." << endl;
		system("pause");
		return 2;
	}

	// Read and ignore the line of dashes.
	getline(infile, dataline); 

	getline(infile, dataline);

	// Read in lines of data
	while (!infile.eof()) {
		
		// Find the needed data
		station_name = dataline.substr(name_start, 44);
		s_date = dataline.substr(date_start, 8);
		s_prcp = dataline.substr(prcp_start, 4);
		s_tmax = dataline.substr(tmax_start, 2);
		s_tmin = dataline.substr(tmin_start, 2);

		// Split date into year, month, and day
		s_year = s_date.substr(0, 4);
		s_month = s_date.substr(4, 2);
		s_day = s_date.substr(6, 2);

		// Convert s_tmax and s_tmin into float values
		// The data is giving in tenths of a degree Celsius.  Divide by 10
		// to get in degrees Celsius
		tmax_celsius = stof(s_tmax) / 10;
		tmin_celsius = stof(s_tmin) / 10;

		// Convert tmax and tmin into farenheit
		tmax_farenheit = tmax_celsius * 1.8 + 32;
		tmin_farenheit = tmin_celsius * 1.8 + 32;

		// Print data into new chart

		outfile << fixed << setprecision(2);

		outfile << setw(44) << station_name << setw(5) << s_year << setw(3) <<
			s_month << setw(3) << s_day << setw(7) << s_prcp << setw(7) <<
			tmax_farenheit << setw(7) << tmin_farenheit << endl;

		// Read the line
		getline(infile, dataline);

	}

	cout << "Five column chart created." << endl;

	infile.close();
	outfile.close();

	system("pause");
	return 0;
}