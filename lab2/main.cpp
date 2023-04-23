#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <regex>
#include <vector>
#include "sorting_algorithms.h"



std::vector<std::string> readConfig(std::string filename){
    std::ifstream config(filename);
    std::vector<std::string> values;
    std::string line;
    if(!config){
        std::cerr << "Cannot open configuration file!";
    }
    if(config.is_open()){
        while(getline(config, line)){

            size_t pos = line.find("=");
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            std::cout << "Key: " << key << "    Value: " << value << std::endl;
            values.push_back(value);

        }
    }
    config.close();
    return values;
}


std::vector<int> readFile(std::string filename){
    std::vector<int> numbers;
    std::ifstream in(filename);
    if (!in) {
        std::cerr <<" Failed to open numbers file!" << std::endl;
    }
    std::string line;
    while(getline(in, line)){
        std::stringstream ss(line);
        std::string number;
        while (getline(ss, number, ',')){
            numbers.push_back(std::stoi(number));
            //std::cout << number << std::endl;
        };
    }
    in.close();
    return numbers;

}

void saveSortedFile(std::string filename, int arr[], int instanceSize){
    std::ofstream out;
    out.open(filename, std::ios::trunc);
    for (int i = 0; i < instanceSize ; i++){
        //std::cout << arr[i] << std::endl;
        out << arr[i] << std::endl;
    }
    out.close();
}

void saveSummary(std::string filename, double meanTime, std::string algorithm, int intanceSize, int repeatCount){
    std::ofstream out;
    out.open(filename, std::ios::app);
    out <<"-------------------------------------------------" << std::endl;
        //<< "Time taken by program: " << timeTaken << " s" << std::endl
    out   << "MeanTime: " << meanTime << " s" << std::endl
        << "RepeatCount: " << repeatCount << std::endl
        << "Algorithm: " << algorithm << std::endl
        << "Instance size: " << intanceSize << std::endl;
    out.close();
}

class Timer {
    private:
        std::chrono::high_resolution_clock::time_point start;
        std::chrono::high_resolution_clock::time_point stop;
    public:
    void startTimer(){
        start = std::chrono::high_resolution_clock::now();
    }

    void stopTimer(){
        stop = std::chrono::high_resolution_clock::now();
    }

    double getElapsedTime(){
        double timeTaken = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
        timeTaken *= 1e-9;
        //std::cout << "Time taken by program: " << timeTaken << " s" <<std::endl;
        return timeTaken;
    }
};


int* copyVecToArr(const std::vector<int>& numbers, int n) {
    int* array = new int[n];
    for (int i = 0; i < n; i++) {
        array[i] = numbers[i];
    }
    return array;
}


int main(int argc, char *argv[]) {

    if (argc <= 1) {
        std::cout << "No argument provided!" << std::endl << "Usage: ./sdizo.exe <config_file>" << std::endl;
        return -1;
    }

    std::vector<std::string> config = readConfig(argv[1]);

    std::vector<int> numbers = readFile(config[0]);
    std::string algorithm = config[3];
    int instanceSize = std::stoi(config[4]);
    int repeatCount = std::stoi(config[5]);

    Timer timer;
    double elapsedTimeSum = 0;
    double meanTime = 0;
    void (*fptr)(int[], int);


    if (algorithm == "bubble_sort"){
        fptr = &bubbleSort;
        std::cout << "Bubble sort has been chosen as sorting algorithm." << std::endl;
    } else if (algorithm == "comb_sort") {
        fptr = &combSort;
        std::cout << "Comb sort has been chosen as sorting algorithm." << std::endl;
    } else if (algorithm == "counting_sort") {
        fptr = &countingSort;
        std::cout << "Counting sort has been chosen as sorting algorithm." << std::endl;
    } else if (algorithm == "cocktail_sort") {
        fptr = &cocktailSort;
        std::cout << "Cocktail sort has been chosen as sorting algorithm." << std::endl;
    }

    std::cout << "Sorting in progress." << std::endl;

    for (int i = 0; i < repeatCount; i++){

        int *arr = copyVecToArr(numbers, instanceSize);

        /*
        std::cout << "Unsorted: ";
        for (int j = 0; j < 10; j++) {
            std::cout  << arr[j] << " ";
        }
        std::cout << std::endl;
        */



        timer.startTimer();
        (*fptr)(arr, instanceSize);
        timer.stopTimer();

        /*
        std::cout << "Sorted: ";
        for (int j = 0; j < 10; j++)
            std::cout << arr[j] << " ";
        std::cout << std::endl;
         */


        std::cout << "Iteration " << i << " time: " << timer.getElapsedTime() << std::endl;


        elapsedTimeSum += timer.getElapsedTime();
        saveSortedFile(config[1], arr, instanceSize);

        if (elapsedTimeSum >= 600){
            std::cout << "Program running for too long, exiting!" << std::endl;
            return -2;
        }
    }
    meanTime = elapsedTimeSum / repeatCount;
    std::cout << "Mean time: " << meanTime << std::endl;
    std::cout << "Done!" << std::endl;

    saveSummary(config[2], meanTime, algorithm, instanceSize, repeatCount);

    return 0;
}
