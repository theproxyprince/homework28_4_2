#include <iostream>
#include <thread>
#include <mutex>

std::mutex trainStation, display;
int count = 0;

void TrainPath(int timeInSeconds, const std::string& trainName) {
    std::string command;

    display.lock();
    std::cout << "The train " << trainName << " has left." << std::endl;
    display.unlock();

    std::this_thread::sleep_for(std::chrono::seconds(timeInSeconds));

    display.lock();
    std::cout << "The train " << trainName << " has arrived at the station. Waiting." << std::endl;
    display.unlock();

    trainStation.lock();
    display.lock();
    std::cout << "The train " << trainName << " at the station. Waiting command to depart: ";
    do {
        std::cin >> command;
        if(command == "depart") {
            std::cout << "The train " << trainName << " is departs from station." << std::endl;
            count++;
        }
    } while (command != "depart");
    display.unlock();
    trainStation.unlock();

}

int main() {
    int pathTime;


    std::cout << "Enter the train A travel time: " ;
    std::cin >> pathTime;

    std::thread trainA(TrainPath, pathTime, "Train A ");

    display.lock();
    std::cout << "Enter the train B travel time: " ;
    std::cin >> pathTime;
    display.unlock();

    std::thread trainB(TrainPath, pathTime, "Train B ");

    display.lock();
    std::cout << "Enter the train C travel time: " ;
    std::cin >> pathTime;
    display.unlock();

    std::thread trainC(TrainPath, pathTime, "Train C ");

    trainA.detach();
    trainB.detach();
    trainC.detach();

    do{} while (count < 3);
}