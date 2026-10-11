#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>

#include "reservationManager.h"
#include "waitinglist.h"
#include "cancellationHistory.h"
#include "resource.h"
#include "ResourceSorter.h"


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
        cout << "8. Sort Resources" << endl;
        cout << "9. Search" << endl;
        cout << "10. System Reporting" << endl;
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

            case 8:
                {
                    cout << "sort by: name / type / availability /id\n";
                    string criteria;
                    cin >> criteria;

                    ResourceSorter::mergeSort(resources, criteria);

                    cout << "\n===== Sorted Resources =====\n";
                    for (const Resource& r : resources)
                        r.display();
                    break;
                }
            case 9:
                {
                    int searchChoice;

                    cout << "\n===== Search Menu =====" << endl;
                    cout << "1. Search Resource by ID" << endl;
                    cout << "2. Search Reservation by ID" << endl;
                    cout << "0. Return to Main Menu" << endl;
                    cout << "Enter your choice: ";

                    if (!(cin >> searchChoice))
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid choice. Please enter a number." << endl;
                        break;
                    }

                    if (searchChoice == 1)
                    {
                        string resourceID;
                        bool found = false;

                        cout << "Enter Resource ID: ";
                        cin >> resourceID;

                        for (const Resource& resource : resources)
                        {
                            if (resource.getID() == resourceID)
                            {
                                cout << "\nResource Found:" << endl;
                                resource.display();
                                found = true;
                                break;
                            }
                        }

                        if (!found)
                        {
                            cout << "Resource not found." << endl;
                        }
                    }
                    else if (searchChoice == 2)
                    {
                        int reservationID;

                        cout << "Enter Reservation ID: ";

                        if (!(cin >> reservationID))
                        {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Invalid Reservation ID." << endl;
                            break;
                        }

                        Reservation* reservation =
                            reservationManager.findReservation(reservationID);

                        if (reservation != nullptr)
                        {
                            cout << "\nReservation Found:" << endl;
                            reservation->display();
                        }
                        else
                        {
                            cout << "Reservation not found." << endl;
                        }
                    }
                    else if (searchChoice == 0)
                    {
                        cout << "Returning to main menu." << endl;
                    }
                    else
                    {
                        cout << "Invalid search choice." << endl;
                    }

                    break;
                }
                        case 10:
            {
                int reportChoice;

                cout << "\n===== System Reporting =====" << endl;
                cout << "1. Active Reservations Report" << endl;
                cout << "2. Resource Utilization Report" << endl;
                cout << "3. Most Requested Resources" << endl;
                cout << "4. Waiting-List Statistics" << endl;
                cout << "0. Return to Main Menu" << endl;
                cout << "Enter your choice: ";

                if (!(cin >> reportChoice))
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid report choice." << endl;
                    break;
                }

                switch (reportChoice)
                {
                    case 1:
                    {
                        cout << "\n===== Active Reservations Report =====" << endl;

                        reservationManager.displayReservations();

                        cout << "Total active reservations: "
                             << reservationManager.getReservationCount()
                             << endl;
                        break;
                    }

                    case 2:
                    {
                        cout << "\n===== Resource Utilization Report =====" << endl;

                        if (resources.empty())
                        {
                            cout << "No resources available." << endl;
                            break;
                        }

                        for (const Resource& resource : resources)
                        {
                            cout << "Resource ID: " << resource.getID()
                                 << " | Active Reservations: "
                                 << reservationManager.countByResource(resource.getID())
                                 << endl;
                        }

                        break;
                    }

                    case 3:
                    {
                        cout << "\n===== Most Requested Resources =====" << endl;

                        if (resources.empty())
                        {
                            cout << "No resources available." << endl;
                            break;
                        }

                        vector<pair<string, int>> rankings;

                        for (const Resource& resource : resources)
                        {
                            rankings.emplace_back(
                                resource.getID(),
                                reservationManager.countByResource(resource.getID())
                            );
                        }

                        sort(
                            rankings.begin(),
                            rankings.end(),
                            [](const pair<string, int>& a,
                               const pair<string, int>& b)
                            {
                                if (a.second != b.second)
                                {
                                    return a.second > b.second;
                                }

                                return a.first < b.first;
                            }
                        );

                        int rank = 1;

                        for (const auto& item : rankings)
                        {
                            cout << rank << ". Resource ID: "
                                 << item.first
                                 << " | Active Reservations: "
                                 << item.second << endl;
                            rank++;
                        }

                        break;
                    }

                    case 4:
                    {
                        cout << "\n===== Waiting-List Statistics =====" << endl;

                        if (resources.empty())
                        {
                            cout << "No resources available." << endl;
                            break;
                        }

                        for (const Resource& resource : resources)
                        {
                            cout << "Resource ID: " << resource.getID()
                                 << " | Students Waiting: "
                                 << waitingList.countByResource(resource.getID())
                                 << endl;
                        }

                        break;
                    }

                    case 0:
                    {
                        cout << "Returning to main menu." << endl;
                        break;
                    }

                    default:
                    {
                        cout << "Invalid report choice." << endl;
                        break;
                    }
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
