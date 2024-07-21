# Bus Reservation System

The Bus Reservation System is a C-based project I developed which has the ability to book, cancel, and check the status of bus tickets easily and efficiently.

## Key Features

1. **User Authentication:**
   - Secure login system for users.
   - Predefined usernames and passwords for demonstration purposes.

2. **Bus Information Management:**
   - Stores and manages information for multiple buses, including bus number, source, destination, total seats, available seats, and fare.

3. **Passenger Information Management:**
   - Collects and stores passenger details such as name, age, seat number, and bus number.

4. **Ticket Booking:**
   - Allows users to book tickets by selecting a bus, entering passenger details, and automatically assigning a seat number.
   - Updates the number of available seats for the selected bus.

5. **Ticket Cancellation:**
   - Enables users to cancel tickets by entering the passenger’s name.
   - Increases the number of available seats for the bus upon cancellation.

6. **Bus Status Check:**
   - Users can check the status of a bus, including the number of available seats, by entering the bus number.

## Sample Data

!!! Please make sure to use one of the following sample data sets when logging in or interacting with the system.

**Users:**
- Username: alice, Password: alice123
- Username: bob, Password: bob456
- Username: charlie, Password: charlie789
- Username: david, Password: david101
- Username: eve, Password: eve202

**Buses:**
- Bus Number: 201, Source: City X, Destination: City Y, Total Seats: 60, Available Seats: 60, Fare: $30.00
- Bus Number: 202, Source: City Z, Destination: City W, Total Seats: 45, Available Seats: 45, Fare: $22.50
- Bus Number: 203, Source: City U, Destination: City V, Total Seats: 35, Available Seats: 35, Fare: $17.50
