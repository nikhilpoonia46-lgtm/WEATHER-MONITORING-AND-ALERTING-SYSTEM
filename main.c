#include <stdio.h>
#include <stdlib.h>

// Threshold definitions for extreme weather alerts
#define MAX_TEMP 40.0       // Celsius
#define MIN_TEMP 0.0        // Celsius
#define MAX_HUMIDITY 85.0   // Percentage
#define MIN_PRESSURE 980.0  // hPa (Low pressure storm warning)

// Structure to hold hourly weather readings
struct WeatherReading {
    int hour;
    float temperature;
    float humidity;
    float pressure;
};

// Function Prototypes
void inputReadings(struct WeatherReading *records, int count);
void calculateAverages(struct WeatherReading *records, int count, float *avgTemp, float *avgHum, float *avgPress);
void checkAlerts(struct WeatherReading *records, int count);
void displaySummary(struct WeatherReading *records, int count, float avgTemp, float avgHum, float avgPress);

int main() {
    int hours;
    struct WeatherReading *dailyData = NULL;
    float avgTemp = 0.0, avgHum = 0.0, avgPress = 0.0;

    printf("==================================================\n");
    printf("     WEATHER MONITORING AND ALERTING SYSTEM       \n");
    printf("==================================================\n");

    // Get number of hours to record (typically up to 24 for a day)
    printf("Enter number of hourly readings to record (1-24): ");
    scanf("%d", &hours);

    if (hours <= 0 || hours > 24) {
        printf("Invalid input. Please enter a value between 1 and 24.\n");
        return 1;
    }

    // Dynamic memory allocation using malloc()
    dailyData = (struct WeatherReading *)malloc(hours * sizeof(struct WeatherReading));
    
    // Always check if memory allocation succeeded
    if (dailyData == NULL) {
        printf("Memory allocation failed! Exiting program.\n");
        return 1;
    }

    // Modular function calls
    inputReadings(dailyData, hours);
    calculateAverages(dailyData, hours, &avgTemp, &avgHum, &avgPress);
    displaySummary(dailyData, hours, avgTemp, avgHum, avgPress);
    checkAlerts(dailyData, hours);

    // Free dynamically allocated memory
    free(dailyData);
    dailyData = NULL;

    return 0;
}

// Function to record hourly readings using pointers
void inputReadings(struct WeatherReading *records, int count) {
    printf("\n--- Enter Hourly Weather Data ---\n");
    for (int i = 0; i < count; i++) {
        (records + i)->hour = i + 1;
        printf("\nHour %d:\n", (records + i)->hour);
        
        printf("  Temperature (C): ");
        scanf("%f", &(records + i)->temperature);
        
        printf("  Humidity (%%): ");
        scanf("%f", &(records + i)->humidity);
        
        printf("  Pressure (hPa): ");
        scanf("%f", &(records + i)->pressure);
    }
}

// Function to compute daily averages using pass-by-reference pointers
void calculateAverages(struct WeatherReading *records, int count, float *avgTemp, float *avgHum, float *avgPress) {
    float sumTemp = 0.0, sumHum = 0.0, sumPress = 0.0;

    for (int i = 0; i < count; i++) {
        sumTemp += records[i].temperature;
        sumHum += records[i].humidity;
        sumPress += records[i].pressure;
    }

    *avgTemp = sumTemp / count;
    *avgHum = sumHum / count;
    *avgPress = sumPress / count;
}

// Function to display the daily summary table and averages
void displaySummary(struct WeatherReading *records, int count, float avgTemp, float avgHum, float avgPress) {
    printf("\n==================================================\n");
    printf("               DAILY WEATHER SUMMARY              \n");
    printf("==================================================\n");
    printf("Hour\tTemp (C)\tHumidity (%%)\tPressure (hPa)\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%02d:00\t%.2f\t\t%.2f\t\t%.2f\n", 
               records[i].hour, 
               records[i].temperature, 
               records[i].humidity, 
               records[i].pressure);
    }

    printf("--------------------------------------------------\n");
    printf("DAILY AVERAGES:\n");
    printf("  Average Temperature : %.2f C\n", avgTemp);
    printf("  Average Humidity    : %.2f %%\n", avgHum);
    printf("  Average Pressure    : %.2f hPa\n", avgPress);
    printf("==================================================\n");
}

// Function to detect and print extreme condition alerts
void checkAlerts(struct WeatherReading *records, int count) {
    int alertCount = 0;

    printf("\n==================================================\n");
    printf("             EXTREME CONDITION ALERTS             \n");
    printf("==================================================\n");

    for (int i = 0; i < count; i++) {
        if (records[i].temperature > MAX_TEMP) {
            printf("[ALERT - Hour %02d:00] Heatwave Warning! High Temp: %.2f C\n", 
                   records[i].hour, records[i].temperature);
            alertCount++;
        }
        if (records[i].temperature < MIN_TEMP) {
            printf("[ALERT - Hour %02d:00] Freeze Warning! Low Temp: %.2f C\n", 
                   records[i].hour, records[i].temperature);
            alertCount++;
        }
        if (records[i].humidity > MAX_HUMIDITY) {
            printf("[ALERT - Hour %02d:00] High Humidity Alert! Level: %.2f %%\n", 
                   records[i].hour, records[i].humidity);
            alertCount++;
        }
        if (records[i].pressure < MIN_PRESSURE) {
            printf("[ALERT - Hour %02d:00] Storm Warning! Low Pressure: %.2f hPa\n", 
                   records[i].hour, records[i].pressure);
            alertCount++;
        }
    }

    if (alertCount == 0) {
        printf("All weather parameters remained within safe limits.\n");
    }
    printf("==================================================\n");
}
