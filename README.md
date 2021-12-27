# weather-data-program
Analyzes data from real weather stations, filters the information, and uses string formatting operations to output a new condensed list.  Creates an interactive data processing menu that performs calculations for rainfall and temperature based on dates and weather station names entered by the user.


## Files:

### Filter_Prcp_Temp.cpp
Finds all records in the AL Weather Station Data file that have bad data (signified by -9999) for PRCP, TMAX, or TMIN.  Produces a new data file (Filtered_AL_Weather_Station.txt) stored in the Temp folder that has the lines with bad data filtered out.

### Five_Col_Chart.cpp
Takes Filtered_AL_Weather_Station.txt stored in the Temp folder.  Creates another file weather_station_five_column.txt stored in the Temp folder.  The new file contains only the STATION NAME, DATE, PRCP, TMAX, and TMIN columns.  The TMAX and TMIN columns are converted from degrees Celsius to degrees Fahrenheit.

### Temp_Extremes.cpp
Uses the data file weather_station_five_column.txt stored in the folder Temp.  Determines and prints out the highest and lowest temperature for the month of March 2018.  It also prints out which stations had these temperatures on which days.  Multiple stations can have the same high or low temperature.

### Weather_Menu.cpp
Uses the data file weather_station_five_column.txt stored in the folder Temp.  Gives the user a menu of options.  The user selects one option.  For option 1, the user enters one day in mm dd yyyy format, and the program returns the total precipitation from all stations in inches for that date.  For option 2, the user enters a start date and end date in mm dd yyyy format, and the program returns the total precipitation from all stations over the date range.  For option 3, the user enters a station name, and the program returns the precipitation for the entire month of March from that station or group of stations.  (The station name needs to be part of the station name in the data file).  For option 4, the user enters a station name, and the program returns the maximum temperature, minimum temperature, average high temperature, and average low temperature for the station during March.  (The station name needs to be exact).  For option 5, the user enters a station name, a state date, and an end date in mm dd yyyy format, and the program returns the maximumum temperature, minimum temperature, average high temperature, and average low temperature for the specified station over the date range. (The station name needs to be exact).
