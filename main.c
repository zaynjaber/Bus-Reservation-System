//
//  main.c
//  bus-reservation-system
//
//  Created by Zayn Jaber on 7/11/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Bus {
    int busNumber;
    char source[50];
    char destination[50];
    int totalSeats;
    int availableSeats;
    float fare;
};

struct Passenger {
    char name[50];
    int age;
    int seatNumber;
    int busNumber;
};

struct User {
    char username[50];
    char password[50];
};

// Declarations
void displayMainMenu(void);
void displayUserMenu(void);
int loginUser(struct User users[], int numUsers, char username[], char password[]);
void bookTicket(struct Bus buses[], int numBuses, struct Passenger passengers[], int* numPassengers, int userId);
void cancelTicket(struct Bus buses[], int numBuses, struct Passenger passengers[], int* numPassengers, int userId);
void checkBusStatus(struct Bus buses[], int numBuses);




int main(void)
{
    struct User users[5] = {
        { "alice", "alice123" }, { "bob", "bob456" },
        { "charlie", "charlie789" }, { "david", "david101" },
        { "eve", "eve202" },
    };
    int numUsers = 5;

    struct Bus buses[3] = {
        { 201, "City X", "City Y", 60, 60, 30.0 },
        { 202, "City Z", "City W", 45, 45, 22.5 },
        { 203, "City U", "City V", 35, 35, 17.5 },
    };
    int numBuses = 3;

    struct Passenger passengers[500];
    int numPassengers = 0;

    int loggedInUserId = -1;

    while (1) {
        if (loggedInUserId == -1) {
            displayMainMenu();
            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
                char username[50];
                char password[50];

                printf("Please enter your Username: ");
                scanf("%49s", username);
                printf("Please enter your Password: ");
                scanf("%49s", password);

                loggedInUserId = loginUser(users, numUsers, username, password);
                if (loggedInUserId == -1) {
                    printf("Login failed. Please verify your username and password.\n");
                } else {
                    printf("Login successful. Welcome, %s!\n", username);
                }
            } else if (choice == 2) {
                printf("Exiting the program. Thank you for using our service.\n");
                break;
            } else {
                printf("Invalid choice. Please try again.\n");
            }
        } else {
            displayUserMenu();
            int userChoice;
            scanf("%d", &userChoice);

            switch (userChoice) {
                case 1:
                    bookTicket(buses, numBuses, passengers, &numPassengers, loggedInUserId);
                    break;
                case 2:
                    cancelTicket(buses, numBuses, passengers, &numPassengers, loggedInUserId);
                    break;
                case 3:
                    checkBusStatus(buses, numBuses);
                    break;
                case 4:
                    printf("Logging out. See you again soon!\n");
                    loggedInUserId = -1;
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    }

    return 0;
}

void displayMainMenu(void)
{
    printf("\n=== Welcome to the Bus Reservation System ===\n");
    printf("1. Login to your account\n");
    printf("2. Exit the application\n");
    printf("Please select an option: ");
}

void displayUserMenu(void)
{
    printf("\n=== User Dashboard ===\n");
    printf("1. Book a Ticket\n");
    printf("2. Cancel a Ticket\n");
    printf("3. Check Bus Status\n");
    printf("4. Logout from your account\n");
    printf("Please select an option: ");
}

int loginUser(struct User users[], int numUsers, char username[], char password[])
{
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

void bookTicket(struct Bus buses[], int numBuses, struct Passenger passengers[], int* numPassengers, int userId)
{
    printf("\nPlease enter the Bus Number you wish to book: ");
    int busNumber;
    scanf("%d", &busNumber);

    int busIndex = -1;
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1) {
        printf("Sorry, no bus found with the number %d.\n", busNumber);
    } else if (buses[busIndex].availableSeats == 0) {
        printf("Unfortunately, the bus is fully booked.\n");
    } else {
        printf("Please enter the Passenger's Name: ");
        scanf("%49s", passengers[*numPassengers].name);

        printf("Please enter the Passenger's Age: ");
        scanf("%d", &passengers[*numPassengers].age);

        passengers[*numPassengers].seatNumber = buses[busIndex].totalSeats - buses[busIndex].availableSeats + 1;
        passengers[*numPassengers].busNumber = busNumber;
        buses[busIndex].availableSeats--;

        printf("Ticket booked successfully! Seat Number: %d\n", passengers[*numPassengers].seatNumber);
        (*numPassengers)++;
    }
}

void cancelTicket(struct Bus buses[], int numBuses, struct Passenger passengers[], int* numPassengers, int userId)
{
    printf("\nPlease enter the Passenger's Name to cancel the ticket: ");
    char name[50];
    scanf("%49s", name);

    int found = 0;
    for (int i = 0; i < *numPassengers; i++) {
        if (strcmp(passengers[i].name, name) == 0) {
            int busIndex = -1;
            for (int j = 0; j < numBuses; j++) {
                if (buses[j].busNumber == passengers[i].busNumber) {
                    busIndex = j;
                    break;
                }
            }
            buses[busIndex].availableSeats++;

            for (int j = i; j < (*numPassengers) - 1; j++) {
                passengers[j] = passengers[j + 1];
            }
            (*numPassengers)--;
            found = 1;
            printf("Ticket canceled successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("No passenger found with the name %s on this bus.\n", name);
    }
}

void checkBusStatus(struct Bus buses[], int numBuses)
{
    printf("\nPlease enter the Bus Number to check its status: ");
    int busNumber;
    scanf("%d", &busNumber);

    int busIndex = -1;
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1) {
        printf("Sorry, no bus found with the number %d.\n", busNumber);
    } else {
        printf("\nBus Number: %d\n", buses[busIndex].busNumber);
        printf("Source: %s\n", buses[busIndex].source);
        printf("Destination: %s\n", buses[busIndex].destination);
        printf("Total Seats: %d\n", buses[busIndex].totalSeats);
        printf("Available Seats: %d\n", buses[busIndex].availableSeats);
        printf("Fare: %.2f\n", buses[busIndex].fare);
    }
}
