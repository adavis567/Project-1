#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "reservationManager.h"
#include "waitinglist.h"
#include "cancellationHistory.h"
#include "resource.h"

using namespace std;

int main()
{
    int choice;

    ReservationManager reservationManager;
    WaitingList waitingList;
    CancellationHistory cancellationHistory;
    vector<Resource> resources;

    ifstream resourceFile("resources.txt");

    if (!resourceFile)
    {
        cout << "Error: Could not open resources.txt." << endl;
    }
    else
    {
        string line;

        while (getline(resourceFile, line))
        {
            if (line.empty())
            {
                continue;
            }

            stringstream ss(line);

            string id;
            string name;
            string type;
            string available;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, type, '|');
            getline(ss, available, '|');

            while (!id.empty() && id[0] == ' ')
            {
                id.erase(0, 1);
            }

            while (!id.empty() && id.back() == ' ')
            {
                id.pop_back();
            }

            while (!name.empty() && name[0] == ' ')
            {
                name.erase(0, 1);
            }

            while (!name.empty() && name.back() == ' ')
            {
                name.pop_back();
            }

            while (!type.empty() && type[0] == ' ')
            {
                type.erase(0, 1);
            }

            while (!type.empty() && type.back() == ' ')
            {
                type.pop_back();
            }

            while (!available.empty() && available[0] == ' ')
            {
                available.erase(0, 1);
            }

            while (!available.empty() && available.back() == ' ')
            {
                available.pop_back();
            }

            bool status = (available == "1");

            resources.emplace_back(id, name, type, status);
        }

        resourceFile.close();
    }

    do
    {
        cout << "\n===== Campus Resource Reservation System =====" << endl;
        cout << "1. Display Resources" << endl;
        cout << "2. Create Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. Display Reservations" << endl;
        cout << "5. Display Waiting List" << endl;
        cout << "6. Display Cancellation History" << endl;
        cout << "7. Undo Cancellation" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Invalid choice. Please enter a number." << endl;
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                if (resources.empty())
                {
                    cout << "No resources available." << endl;
                }
                else
                {
                    cout << "\n===== Resources =====" << endl;

                    for (const Resource& resource : resources)
                    {
                        resource.display();
                    }
                }

                break;
            }

            case 2:
            {
                int reservationID;
                int studentID;
                string studentName;
                string resourceID;
                string reservationDate;

                cout << "Enter Reservation ID: ";

                if (!(cin >> reservationID))
                {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Invalid Reservation ID." << endl;
                    break;
                }

                if (reservationManager.reservationExists(reservationID))
                {
                    cout << "Reservation ID already exists." << endl;
                    break;
                }

                cout << "Enter Student ID: ";

                if (!(cin >> studentID))
                {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Invalid Student ID." << endl;
                    break;
                }

                cin.ignore(10000, '\n');

                cout << "Enter Student Name: ";
                getline(cin, studentName);

                if (studentName.empty())
                {
                    cout << "Student name cannot be empty." << endl;
                    break;
                }

                cout << "Enter Resource ID: ";
                cin >> resourceID;

                cout << "Enter Reservation Date: ";
                cin >> reservationDate;

                Resource* selectedResource = nullptr;

                for (Resource& resource : resources)
                {
                    if (resource.getID() == resourceID)
                    {
                        selectedResource = &resource;
                        break;
                    }
                }

                if (selectedResource == nullptr)
                {
                    cout << "Invalid Resource ID." << endl;
                    break;
                }

                if (!selectedResource->getAvailability())
                {
                    waitingList.enqueue(
                        reservationID,
                        to_string(studentID),
                        studentName,
                        resourceID,
                        reservationDate
                    );

                    cout << "Resource is unavailable. Student added to waiting list." << endl;
                    break;
                }

                Reservation reservation(
                    reservationID,
                    studentID,
                    studentName,
                    resourceID,
                    reservationDate
                );

                if (reservationManager.insertReservation(reservation))
                {
                    selectedResource->setAvailability(false);

                    cout << "Reservation created successfully." << endl;
                }
                else
                {
                    cout << "Reservation ID already exists." << endl;
                }

                break;
            }

            case 3:
            {
                int reservationID;

                cout << "Enter Reservation ID to cancel: ";

                if (!(cin >> reservationID))
                {
                    cin.clear();
                    cin.ignore(10000, '\n');

                    cout << "Invalid Reservation ID." << endl;
                    break;
                }

                Reservation* reservation =
                    reservationManager.findReservation(reservationID);

                if (reservation == nullptr)
                {
                    cout << "Reservation not found." << endl;
                    break;
                }

                Reservation cancelledReservation = *reservation;

                if (reservationManager.removeReservation(reservationID))
                {
                    cancellationHistory.addCancellation(cancelledReservation);

                    Resource* selectedResource = nullptr;

                    for (Resource& resource : resources)
                    {
                        if (resource.getID() == cancelledReservation.getResourceID())
                        {
                            selectedResource = &resource;
                            break;
                        }
                    }

                    if (selectedResource != nullptr)
                    {
                        selectedResource->setAvailability(true);

                        WaitingNode* nextStudent = waitingList.peek();

                        if (nextStudent != nullptr &&
                            nextStudent->resourceID == selectedResource->getID())
                        {
                            int waitingReservationID =
                                nextStudent->reservationID;

                            int waitingStudentID =
                                stoi(nextStudent->studentID);

                            Reservation waitingReservation(
                                waitingReservationID,
                                waitingStudentID,
                                nextStudent->studentName,
                                nextStudent->resourceID,
                                nextStudent->reservationDate
                            );

                            if (reservationManager.insertReservation(waitingReservation))
                            {
                                selectedResource->setAvailability(false);
                                waitingList.dequeue();

                                cout << "Reservation cancelled successfully." << endl;
                                cout << "Resource automatically assigned to the next student on the waiting list." << endl;
                            }
                            else
                            {
                                cout << "Reservation cancelled successfully." << endl;
                                cout << "Could not automatically assign the waiting-list reservation." << endl;
                            }
                        }
                        else
                        {
                            cout << "Reservation cancelled successfully." << endl;
                        }
                    }
                    else
                    {
                        cout << "Reservation cancelled successfully." << endl;
                    }
                }

                break;
            }

            case 4:
            {
                reservationManager.displayReservations();
                break;
            }

            case 5:
            {
                waitingList.display();
                break;
            }

            case 6:
            {
                cancellationHistory.displayHistory();
                break;
            }

            case 7:
            {
                Reservation reservation;

                if (!cancellationHistory.undoCancellation(reservation))
                {
                    cout << "Cancellation history is empty." << endl;
                    break;
                }

                Resource* selectedResource = nullptr;

                for (Resource& resource : resources)
                {
                    if (resource.getID() == reservation.getResourceID())
                    {
                        selectedResource = &resource;
                        break;
                    }
                }

                if (selectedResource == nullptr)
                {
                    cout << "Could not restore reservation. Resource not found." << endl;
                    cancellationHistory.addCancellation(reservation);
                    break;
                }

                if (!selectedResource->getAvailability())
                {
                    cout << "Could not restore reservation. Resource is currently unavailable." << endl;
                    cancellationHistory.addCancellation(reservation);
                    break;
                }

                if (reservationManager.insertReservation(reservation))
                {
                    selectedResource->setAvailability(false);

                    cout << "Reservation restored successfully." << endl;
                }
                else
                {
                    cout << "Could not restore reservation. Reservation ID already exists." << endl;
                    cancellationHistory.addCancellation(reservation);
                }

                break;
            }

            case 0:
            {
                cout << "Exiting program..." << endl;
                break;
            }

            default:
            {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }

    } while (choice != 0);

    return 0;
}