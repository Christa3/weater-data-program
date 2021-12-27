// This program uses the file weather_station_five_column.txt
// stored in file Temp.
//
// It presents to the user a menu with
// five options.  
//
// If option 1 is picked, it determines the
// total precipitation from all the stations in inches for
// a user-given date.  
//
// If option 2 is picked, it determines
// the total precipitation from all the station in inches
// over a user-given range of dates.  
//
// If option 3 is picked, it determines the total 
// precipitation in the month of March
// at all of the stations that are an exact match or include
// the words of a user-given station name.  
//
// If option 4 is picked, it determines the maximum temperature,
// minimum temperature, average high temperature, and average
// low temperature for the month of March for a user-given station 
// name.  The station name must match exactly.
//
// If option 5 is picked, it determines the maximum temperature,
// minimum temperature, average high temperature, and average 
// low temperature for a user-specified station name for a user-
// given range of dates.  The station name must match exactly.
// 

#include <iostream>;
#include <fstream>;
#include <iomanip>
#include <string>

using namespace std;

void printDayPrcp(unsigned int month, unsigned int day, 
	unsigned int year);
double dayPrcp(unsigned int user_month, unsigned int user_day,
	unsigned int user_year);
void printRangePrcp(unsigned int month1, unsigned int day1,
	unsigned int year1, unsigned int month2,
	unsigned int day2, unsigned int year2);
void printStationPrcp(string user_name);
void printMonthTemp(string stationName);
void printRangeTemp(string user_name, unsigned int month1,
	unsigned int day1, unsigned int year1,
	unsigned int month2, unsigned int day2, unsigned int year2);
bool findTemp(string user_name, unsigned int user_month,
	unsigned int user_day, unsigned int user_year);

double totalMaxTemp, totalMinTemp;
double maxSum, minSum;

int main(void) {

	unsigned int option = 0; // The menu option that the user chooses.

	// The month, day, and year input by the user.
	// The 1's are for the starting date and
	// the 2's are for the ending date.
	unsigned int month1 = 0, day1 = 0, year1 = 0;
	unsigned int month2 = 0, day2 = 0, year2 = 0;

	string startDate, endDate = ""; // Starting and ending dates.
	string name = ""; // A station name.

	cout << fixed << setprecision(2);

	// Print out the menu.
	cout << "Select an option from the following menu." << endl << endl;
	cout << "1. Total precipitation from all stations for a given day."
		<< endl;
	cout << "2. Total precipitation over a date range." << endl;
	cout << "3. Total precipitation by station for March." << endl;
	cout << "4. Temperature max, min, and average by station for March."
		<< endl;
	cout << "5. Temperature max, min, and average by station for " <<
		"date range." << endl;
	cout << "6. Quit." << endl;

	// Read in the user's menu choice.
	cin >> option;
	
	switch (option) {

	case 1:
		cout << "You selected option 1.  Total precipitation from " <<
			"all station for a given day" << endl;
		cout << "Enter the date in mm dd yyyy format." << endl;
		cin >> month1 >> day1 >> year1;
		printDayPrcp(month1, day1, year1);
		break;

	case 2:
		cout << "You selected option 2.  Total precipitation over " <<
			"a date range." << endl;
		cout << "Enter the beginning date in mm dd yyyy format." <<
			endl;
		cin >> month1 >> day1 >> year1 ;
		cout << "Enter the ending date in mm dd yyyy format." << endl;
		cin >> month2 >> day2 >> year2;
		printRangePrcp(month1, day1, year1,
			                month2, day2, year2);
		break;

	case 3:
		cin.ignore();
		cout << "You selected option 3.  Total precipitation by " <<
			"station for March." << endl;
		cout << "Enter the station name." << endl;
		getline(cin, name);
		printStationPrcp(name);
		break;


	case 4:
		cin.ignore();
		cout << "You selected option 4.  Temperature max, min and " <<
			"average by station for March." << endl;
		cout << "Enter the station name." << endl;
		getline(cin, name);
		printMonthTemp(name);
		break;
	
	case 5:
		cin.ignore();
		cout << "You selected option 5. Temperature max, min and " <<
			"average by station for date range." << endl;
		cout << "Enter the station name." << endl;
		getline(cin, name);
		cout << "Enter the beginning date in mm dd yyyy format." <<
			endl;
		cin >> month1 >> day1 >> year1;
		cout << "Enter the ending date in mm dd yyyy format." <<
			endl;
		cin >> month2 >> day2 >> year2;
		printRangeTemp(name, month1, day1, year1, month2, day2, year2);
		break;
	}

	system("pause");
	return 0;
}

// ------------------------------------------------------------------
//
//                       LIST OF FUNCTIONS
//
// ------------------------------------------------------------------


// Function takes parameter for the month, day, and year of a date
// as strings. It then prints out the total precipitation from
// all stations in inches for that date.  Relies on funtion 
// dayStatePrcp.
void printDayPrcp(unsigned int month, unsigned int day, 
	              unsigned int year) {

	double prcp = 0; // The total precipitation for the date.

	prcp = dayPrcp(month, day, year);

	cout << setfill('0') << setprecision(2);
	cout << "The total precipitation for the state of Alabama" <<
		endl;
	cout << "on " << setw(2) << month << " " << setw(2) 
		<< day << " " << setw(4) << year << " was " << 
		prcp << " inches." << endl;
}

// Function takes parameter for the month, day, and year of a date
// as strings.  It then returns the total precipitation from 
// all stations in inches for that date.

double dayPrcp(unsigned int user_month, unsigned int user_day, 
	           unsigned int user_year) {

	string dataline = ""; // A line from the data file.
	
	// The date from the line of data.
	unsigned int chart_year = 0, chart_month = 0, chart_day = 0;

	// The indexes of the start of the date and prcp columns.
	unsigned int year_index = 0;
	unsigned int month_index = 0;
	unsigned int day_index = 0;
	unsigned int prcp_index = 0;

	// The precipitation for one station.
	string prcp_s = "";

	// The total precipitation for that date.
	double totalPrcp = 0;

	ifstream infile; // For the data file.


    // Open the data file.
	infile.open("C:/Temp/weather_station_five_column.txt");
	if (!infile) {
		cout << "Data file could not be found." << endl;
		system("pause");
		return -1;
	}


	// Look through heading of file to find start
	// of date and precipitation columns.

	getline(infile, dataline);
	year_index = dataline.find("DATE");
	if (year_index == string::npos) {
		cout << "Date column could not be found." << endl;
		system("pause");
		return -2;
	}

	// The year starts 2 indexes before the
	// word DATE
	year_index -= 2;
	month_index = year_index + 5;
	day_index = month_index + 3;

	

	prcp_index = dataline.find("PRCP");
	if (prcp_index == string::npos) {
		cout << "Precipitation column could not be found." << endl;
		system("pause");
		return -2;
	}

	// Read in lines of data
	getline(infile, dataline);
	while (!infile.eof()) {
		chart_year = stoi(dataline.substr(year_index, 4));
		chart_month = stoi(dataline.substr(month_index, 2));
		chart_day = stoi(dataline.substr(day_index, 2));
		if ((chart_year == user_year) && (chart_month == user_month) &&
			(chart_day == user_day) ) {
			// Find precipitation for this line and
			// add it to the total precipitation.
			prcp_s = dataline.substr(prcp_index, 4);
			totalPrcp += stod(prcp_s);
		}
		getline(infile, dataline);
	}

	infile.close();
	return totalPrcp;

}



// Funtion takes parameters for a starting month, day, and year
// and an ending day.  It is assumed that the ending date is in
// the same month and year as the starting date.  It then 
// prints out the total precipitation from all stations in inches
// for the range of dates.

void printRangePrcp(unsigned int month1, unsigned int day1, 
			        unsigned int year1, unsigned int month2, 
	                unsigned int day2,  unsigned int year2) {
	double prcp = 0; // The total precipitation over the date range.
	

	// The start month and end month of a full year.
	unsigned int start_month = 1, end_month = 12;

	// The start day and end day of a month that has 31 days.
	unsigned int start_day = 1, end_day = 31;

	// Cycle through each day in the date range.
	for (unsigned int y = year1; y <= year2; y++) {
		if (y == year1)
			start_month = month1;
		if (y == year2)
			end_month = month2;
		for (unsigned int m = start_month; m <= end_month; m++) {
			if (y == year1 && m == month1)
				start_day = day1;
			if (y == year2 && m == month2)
				end_day = day2;
			for (unsigned int d = start_day; d <= end_day; d++) {

				// Find the precipitation for the day.
				prcp += dayPrcp(m, d, y);

			}

			// Reset the start day.
			start_day = 1;
		}

		// Reset the start month.
		start_month = 1;
	}

	cout << setfill('0') << setprecision(2);
	cout << "The total precipitation for the state of Alabama" << endl;
	cout << "from " << setw(2) << month1 << " " << setw(2) << day1 <<
		" " << setw(4) << year1 << " to " << setw(2) << month2 <<
		" " << setw(2) << day2 << " " << setw(4) << year2 << " was " <<
		prcp << " inches." << endl;
}

// Function takes a parameter of a station name (or partial
// station name).  It then prints out the total precipitation
// for the entire month of March from any stations that 
// contain the station name parameter as part of its station
// name.

void printStationPrcp(string user_name) {

	string dataline = ""; // A line from the data file.

	string chart_name = ""; // The name of the station
	                        // in the data.

    // The date from the line of data.
	unsigned int chart_month = 0;

	// The indexes of the start of the date and prcp columns.
	unsigned int month_index = 0;
	unsigned int prcp_index = 0;

	// The precipitation for one station.
	string prcp_s = "";

	// The total precipitation for that date.
	double totalPrcp = 0;

	ifstream infile; // For the data file.

	// Open the data file.
	infile.open("C:/Temp/weather_station_five_column.txt");
	if (!infile) {
		cout << "Data file could not be found." << endl;
		system("pause");
		return;
	}


	// Look through heading of file to find the index of
	// the month in the chart.

	getline(infile, dataline);
	month_index = dataline.find("DATE");
	if (month_index == string::npos) {
		cout << "Month could not be found." << endl;
		system("pause");
		return;
	}
	// The start of the month is three indexes after
	// the word "DATE".
	month_index +=3;

	// Find the start of the precipitation column.

	prcp_index = dataline.find("PRCP");
	if (prcp_index == string::npos) {
		cout << "Precipitation column could not be found." << endl;
		system("pause");
		return;
	}

	// Read in lines of data
	getline(infile, dataline);
	while (!infile.eof()) {
		chart_name = dataline.substr(0, 44);
		chart_month = stoi(dataline.substr(month_index, 2));
		// If the station name includes the user-given name and
		// the month is March, count the precipitation for this
		// station.
		if ((chart_name.find(user_name) != string :: npos) && 
			(chart_month == 3)) {
			// Find precipitation for this line and
			// add it to the total precipitation.
			prcp_s = dataline.substr(prcp_index, 4);
			totalPrcp += stod(prcp_s);
		}
		getline(infile, dataline);
	}

	cout << setprecision(2);
	cout << "The total precipitation for the state of Alabama in March"
		<< endl << "from stations containting " << user_name <<
		" was " << totalPrcp << " inches." << endl;

	infile.close();
}


// Function takes a parameter of a complete station name.
// It then prints out the maximum temp, minimum temp,
// average high temperature, and average low temperature
// for the station during March.
void printMonthTemp(string user_name) {
	printRangeTemp(user_name, 3, 1, 2018, 3, 31, 2018);
}




// Function takes parameters of a complete station name, 
// a starting date, and an ending date.  Both the starting
// and ending dates are strings in the format mm dd yyyy.
// It then prints out the maximum temp, minimum temp, average
// high temperature, and average low temperature for the 
// specified station over the date range.
void printRangeTemp(string user_name, unsigned int month1,
	unsigned int day1, unsigned int year1,
	unsigned int month2, unsigned int day2,
	unsigned int year2) {

	unsigned int dataTotal = 0; // The amount of lines of data 
	                            // that have been processed.

	// The average of the maximum and minimum temperature 
	// values, respectively.
	double maxAverage = 0, minAverage = 0;

	totalMaxTemp = 0;
	totalMinTemp = UINT_MAX;
	
	maxSum = 0;
	minSum = 0;


	// The start month and end month of a full year.
	unsigned int start_month = 1, end_month = 12;

	// The start day and end day of a month that has 31 days.
	unsigned int start_day = 1, end_day = 31;

	// Cycle through each day in the date range.
	for (unsigned int y = year1; y <= year2; y++) {
		if (y == year1)
			start_month = month1;
		if (y == year2)
			end_month = month2;
		for (unsigned int m = start_month; m <= end_month; m++) {
			if (y == year1 && m == month1)
				start_day = day1;
			if (y == year2 && m == month2)
				end_day = day2;
			for (unsigned int d = start_day; d <= end_day; d++) {

				findTemp(user_name, m, d, y);
				dataTotal++;

			}

			// Reset the start day.
			start_day = 1;
		}

		// Reset the start month.
		start_month = 1;
	}
	
	// Calculate the average maximum and minimum temperatures.
	maxAverage = maxSum / dataTotal;
	minAverage = minSum / dataTotal;

	cout << fixed << setprecision(2) << setfill('0');

	cout << "The maximum temperature for station " << user_name <<
		" from " << setw(2) << month1 << " " << setw(2) << day1 <<
		" " << setw(4) << year1 << " to " << setw(2) << month2 <<
		" " << setw(2) << day2 << " " << setw(4) << year2 <<
		" was " << totalMaxTemp << " F" << endl;
	cout << "The minimum temperature was " << totalMinTemp <<
		" F" << endl;
	cout << "The average high temperature was " << maxAverage <<
		" F" << endl;
	cout << "The average low temperature was " << minAverage <<
		" F" << endl;
}


// Takes a station name, month, day, and year as parameters.
// Attempts to find the data entry for the given station name
// on the given date.  If it cannot be found, false is returned.
// Else, the maximum temperature and minimum temperature are
// added to the global variables maxSum and minSum,
// respectively.  If the maximum temperature is greater than
// the global variable totalMaxTemp, the maximum temperature
// becomes the new value for totalMaxTemp.  If the minimum
// temperature is less than the global variable totalMinTemp,
// the minimum temperature becomes the new value for totalMinTemp.
bool findTemp(string user_name, unsigned int user_month, 
	unsigned int user_day, unsigned int user_year) {
	string dataline = ""; // A line from the data file.

	string chart_name = ""; // The name of the station
							// in the data.

	// The date from the line of data.
	unsigned int chart_year = 0, chart_month = 0, chart_day = 0;

	// The indexes of the start of the date and prcp columns.
	unsigned int year_index = 0;
	unsigned int month_index = 0;
	unsigned int day_index = 0;
	unsigned int tmax_index = 0;
	unsigned int tmin_index = 0;

	// The maximum and minimum temperature for the station on
	// the given day.
	double tmax = 0, tmin = 0;

	// The starting index for the name in the data, not including
	// white space.
	unsigned int name_start;

	ifstream infile; // For the data file.

	// Open the data file.
	infile.open("C:/Temp/weather_station_five_column.txt");
	if (!infile) {
		cout << "Data file could not be found." << endl;
		system("pause");
		return false;
	}


	// Look through heading of file to find the index of
	// the month in the chart.

	getline(infile, dataline);
	year_index = dataline.find("DATE");
	if (year_index == string::npos) {
		cout << "Date column could not be found." << endl;
		system("pause");
		return false;
	}

	// The start of the date column is two indexes before
	// the word "DATE".
	year_index -= 2;

	// The month is 5 indexes over from the year.
	month_index = year_index + 5;

	// The day is 3 indexes over from the month.
	day_index = month_index + 3;

	// Find the start of the TMAX column

	tmax_index = dataline.find("TMAX");
	if (tmax_index == string::npos) {
		cout << "Maximum temperature column could not be found." << endl;
		system("pause");
		return false;
	}

	tmin_index = dataline.find("TMIN");
	if (tmin_index == string::npos) {
		cout << "Minimum temperature column could not be found." << endl;
		system("pause");
		return false;
	}

	// Read in lines of data
	getline(infile, dataline);
	while (!infile.eof()) {
		chart_name = dataline.substr(0, 44);
		chart_year = stoi(dataline.substr(year_index, 4));
		chart_month = stoi(dataline.substr(month_index, 2));;
		chart_day = stoi(dataline.substr(day_index, 2));

		// Trim whitespace fromm chart_name
		name_start = chart_name.find_first_not_of(' ');
		chart_name = chart_name.substr(name_start,
			chart_name.length() - name_start);


		// If the station name includes the user-given name and
		// the month is March, look at temperatures for this line.
		if ((chart_name == user_name) &&
			(chart_year == user_year) && (chart_month == user_month) &&
			(chart_day == user_day)) {
			
			tmax = stod(dataline.substr(tmax_index, 5));
			tmin = stod(dataline.substr(tmin_index, 5));

			maxSum += tmax;
			minSum += tmin;

			if (tmin < totalMinTemp)
				totalMinTemp = tmin;

			if (tmax > totalMaxTemp)
				totalMaxTemp = tmax;

			infile.close();

			return true;
		}
		getline(infile, dataline);
	}
	return false;
}