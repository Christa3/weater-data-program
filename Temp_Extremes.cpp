// This program looks at the file weather_station_five_column.txt
// stored in folder Temp.  It determines the highest and lowest
// temperatures in the chart.  It ten prints out the station names
// with these temperature extremes along with the highest and lowest
// temperatures.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

int main(void) {
	string dataline = ""; // A line of data read from the file.

	// The indexes of the start of the tmax and 
	// tmin columns, respectively.
	unsigned int tmax_start = 0, tmin_start = 0; 


	// The indexes of the start of the year, month,
	// and day.
	unsigned int year_start = 0, month_start = 0, day_start = 0;

    // The maximum and minimum temperatures for 
	// a particular data entry.
	double maxTemp = 0, minTemp = 0;  


    // The maximum and minimum temperature found.
	double totalMax = 0, totalMin = 0;  

	string station_name = ""; // The name of the station.

	// The month, day, and year of the chart date.
	unsigned int month = 0, day = 0, year = 0;

	ifstream infile;

	// Open file.
	infile.open("C:/Temp/weather_station_five_column.txt");
	if (!infile) {
		cout << "The file could not be opened." << endl;
		system("pause");
		return 1;
	}
	else {
		cout << "File opened." << endl;
	}

	// Read in chart heading.

	getline(infile, dataline);

	// Look for the positions of DATE, TMAX, and TMIN columns.

	year_start = dataline.find("DATE");
	if (year_start == string::npos) {
		cout << "Date column could not be found." << endl;
		system("pause");
		return 2;
	}
	// Year actually starts two positions before
	// the word DATE
	year_start -= 2;
	
	month_start = year_start + 5;
	day_start = month_start + 3;



	tmax_start = dataline.find("TMAX");
	if (tmax_start == string::npos) {
		cout << "Maximum temperature column could not be found." << endl;
		system("pause");
		return 2;
	}

	tmin_start = dataline.find("TMIN");
	if (tmin_start == string::npos) {
		cout << "Minimum temperature column could not be found." << endl;
		system("pause");
		return 2;
	}

	// Read in first line of data and initialize the minimum and maximum
	// temperatures to this station's temperature.

	getline(infile, dataline);
	maxTemp = stod(dataline.substr(tmax_start, 5));
	minTemp = stod(dataline.substr(tmin_start, 5));
	// Change temperatures to type float and put as total maximum
	// and minimum
	totalMax = maxTemp;
	totalMin = minTemp;

	// Read in lines of data until end of file.
	getline(infile, dataline);
	while (!infile.eof()) {
		if (stoi(dataline.substr(month_start, 2)) == 3
			&& stoi(dataline.substr(year_start, 4)) == 2018) {

			// Read in maximum and minimum temperature and convert
			// them to values of type float
			maxTemp = stod(dataline.substr(tmax_start, 5));
			minTemp = stod(dataline.substr(tmin_start, 5));

			// If maximum is greater than current total maximum 
			// temperature, this is the new total maximum.
			if (maxTemp > totalMax)
				totalMax = maxTemp;

			// If minimum is greater than current total minimum
			// temperature, this is the new total minimum.
			if (minTemp < totalMin)
				totalMin = minTemp;
		}

		getline(infile, dataline);
	}

	// Reset file.
	infile.close();
	infile.open("C:/Temp/weather_station_five_column.txt");

	cout << "The highest temperature in March is " << totalMax << endl;
	cout << "This occured at: " << endl;

	// Determine and print out stations where the temperature has the
	// highest temperature in March

	// Read first line of headings
	getline(infile, dataline);

	// Go through each data line to see if it has the highest
	// temperature in March.
	getline(infile, dataline);
	while (!infile.eof()) {
		maxTemp = stod(dataline.substr(tmax_start, 5));
		if (maxTemp == totalMax) {
			station_name = dataline.substr(0, 44);
			day = stoi(dataline.substr(day_start, 2));
			cout << station_name << " on March " <<
				day << endl;
		}
		getline(infile, dataline);
	}

	cout << endl;

	// Reset file.
	infile.close();
	infile.open("C:/Temp/weather_station_five_column.txt");

	// Determine and print out stations where the temperature has the
    // lowest temperature in March

     // Read first line of headings
	getline(infile, dataline);

	cout << "The lowest temperature in March is " << totalMin << endl;
	cout << "This occurred at: " << endl;

	// Go through each data line to see if it has the lowerst
    // temperature in March.
	getline(infile, dataline);
	while (!infile.eof()) {
		minTemp = stod(dataline.substr(tmin_start, 5));
		if (minTemp == totalMin) {
			station_name = dataline.substr(0, 44);
			day = stoi(dataline.substr(day_start, 2));
			cout << station_name << " on March " <<
				day << endl;
		}
		getline(infile, dataline);
	}

	infile.close();

	system("pause");
	return 0;
}