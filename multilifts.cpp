#include <iostream>
#include <vector>
#include <queue>
#include <limits> // for std::numeric_limits

const int NUM_LIFTS = 5; // Number of lifts in the system
const int TOTAL_FLOORS = 10; // Total number of floors in the building

class Lift {
private:
    int liftId;
    int currentFloor;
    std::queue<int> destinationFloors;
public:
    Lift(int id) {
        liftId = id;
        currentFloor = 0; // Assuming the ground floor is 0
    }

    int getCurrentFloor() const {
        return currentFloor;
    }

    void requestFloor(int floor) {
        destinationFloors.push(floor);
    }

    void moveToNextFloor() {
        if (!destinationFloors.empty()) {
            int nextFloor = destinationFloors.front();
            destinationFloors.pop();

            if (nextFloor > currentFloor) {
                while (currentFloor < nextFloor) {
                    currentFloor++;
                    std::cout << "Lift " << liftId << ": Moving up to Floor " << currentFloor << std::endl;
                }
            } else if (nextFloor < currentFloor) {
                while (currentFloor > nextFloor) {
                    currentFloor--;
                    std::cout << "Lift " << liftId << ": Moving down to Floor " << currentFloor << std::endl;
                }
            }

            std::cout << "Lift " << liftId << ": Arrived at Floor " << currentFloor << std::endl;
        } else {
            std::cout << "Lift " << liftId << ": No destination floors. Lift is idle." << std::endl;
        }
    }
};

class LiftController {
private:
    std::vector<Lift> lifts;
public:
    LiftController() {
        for (int i = 0; i < NUM_LIFTS; i++) {
            Lift lift(i);
            lifts.push_back(lift);
        }
    }

    void requestLift(int floor) {
        int closestLiftId = -1;
        int minDistance = std::numeric_limits<int>::max(); // Initialize with maximum possible distance

        // Find an available lift closest to the requested floor
        for (int i = 0; i < NUM_LIFTS; i++) {
            if (lifts[i].getCurrentFloor() == floor) {
                // If a lift is already at the requested floor, use it
                closestLiftId = i;
                break;
            }

            int distance = abs(lifts[i].getCurrentFloor() - floor);
            if (distance < minDistance) {
                minDistance = distance;
                closestLiftId = i;
            }
        }

        if (closestLiftId != -1) {
            lifts[closestLiftId].requestFloor(floor);
            lifts[closestLiftId].moveToNextFloor();
        } else {
            std::cout << "No available lifts. Please wait." << std::endl;
        }
    }
};

int main() {
    LiftController liftController;

    // Example usage
    liftController.requestLift(3); // Request a lift to Floor 3
    liftController.requestLift(2); // Request a lift to Floor 2
    liftController.requestLift(5); // Request a lift to Floor 5
    liftController.requestLift(7); // Request a lift to Floor 7
    liftController.requestLift(1); // Request a lift to Floor 1
    liftController.requestLift(9); // Request a lift to Floor 1
    liftController.requestLift(5); // Request a lift to Floor 1
    liftController.requestLift(2); // Request a lift to Floor 1
    liftController.requestLift(1); // Request a lift to Floor 1
    liftController.requestLift(3); // Request a lift to Floor 1
    liftController.requestLift(7); // Request a lift to Floor 7
    liftController.requestLift(3); // Request a lift to Floor 7
    liftController.requestLift(1); // Request a lift to Floor 7


    return 0;
}

