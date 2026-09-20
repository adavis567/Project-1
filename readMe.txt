Campus Resource Reservation System

Project Description

The Campus Resource Reservation System is a menu-driven C++ program
designed to manage campus resources and student reservations.

The system manages resources such as study rooms, laptops, calculators,
and other campus equipment. Students can create reservations, cancel
reservations, join waiting lists, and restore cancelled reservations.


Features

1. Display Resources
2. Create Reservation
3. Cancel Reservation
4. Display Active Reservations
5. Display Waiting List
6. Display Cancellation History
7. Undo Cancellation
0. Exit


Data Structures

Vector
A vector is used to store the campus resource inventory.

Linked List
A linked list is used to store active reservations.

Queue
A linked queue is used to store students waiting for unavailable
resources. Students are processed in first-in, first-out (FIFO) order.

Stack
A stack is used to store cancellation history. The most recently
cancelled reservation can be restored first.


Input Files

resources.txt

This file contains the campus resource inventory.

Each line follows this format:

Resource ID | Resource Name | Resource Type | Availability

Example:

R001 | Study Room 1 | Study Room | 1
R002 | Study Room 2 | Study Room | 1
R003 | Laptop 1 | Laptop | 1
R004 | Calculator 1 | Calculator | 1


How to Compile

Use the following command:

g++ *.cpp -o project


How to Run

Use:

./project


Reservation Process

When a student creates a reservation, the system checks whether the
resource exists and whether the resource is available.

If the resource is available, the reservation is added to the active
reservation linked list and the resource becomes unavailable.

If the resource is unavailable, the student is added to the waiting list.


Cancellation Process

When a reservation is cancelled, it is removed from the active
reservation linked list and added to the cancellation history stack.

The resource becomes available.

If a student is waiting for that resource, the first student in the
waiting list is automatically assigned the resource.


Undo Cancellation

The undo cancellation feature removes the most recent cancellation from
the cancellation history stack and restores the reservation if its
resource is currently available.


Error Handling

The system checks for:

- Invalid menu choices
- Invalid numeric input
- Duplicate reservation IDs
- Invalid resource IDs
- Empty waiting lists
- Empty cancellation history
- Missing resource input file
- Empty student names
- Resources that are currently unavailable


Files

main.cpp
reservation.h
reservation.cpp
reservationManager.h
reservationManager.cpp
resource.h
resource.cpp
waitinglist.h
waitingList.cpp
cancellationHistory.h
cancellationHistory.cpp
resources.txt
reservations.txt
complexityAnalysis.txt
groupContributionReport.txt
readMe.txt
