#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <dirent.h>
#include <time.h>
#include <windows.h>
#include "BubbleSort.cpp"
using namespace std;


struct Results
{
    double time;
    int cycleIterationsCount;
};

int countOfFilesInDirectory(string pathToDir)
{
    DIR *dir = opendir((pathToDir).c_str());
    struct dirent *entry;
    int countOfFiles = 0;
    while ( (entry = readdir(dir)) != NULL)
        if (string(entry->d_name) != "." && string(entry->d_name) != "..")
            countOfFiles++;
    closedir(dir);
    return countOfFiles;
}

pair<int, int*> readDataFromFile(ifstream& file)
{
    int countOfNumbers, number;
    file >> countOfNumbers;
    int* arr = new int[countOfNumbers];
    for (int j = 0; j < countOfNumbers; j++)
    {
        file >> number;
        arr[j] = number;
    }
    return pair<int, int*>(countOfNumbers, arr);
}

void printMeasurementsIntoFile(map <int, double[2]> measurements)
{
    map <int, double[2]> :: iterator it;
    ofstream file("./testsMeasurementsResults.txt");
    for (it = measurements.begin(); it != measurements.end(); it++)
        file << it->first << ": " << it->second[0] << ", " << (int)it->second[1] << ", " << 0 << endl;
    file.close();
}

Results averageProcessingResults(int* arr, int countOfNumbers)
{
    const int countOfSortsForTest = 300;
    int* arrCopy = new int[countOfNumbers];
    for (int i = 0; i < countOfSortsForTest; i++)
        arrCopy[i] = arr[i];

    int startTime = clock();
    int cycleIterationsCount = bubbleSort(arr, countOfNumbers);
    for (int i = 0; i < countOfSortsForTest; i++)
    {
        for (int j = 0; j < countOfSortsForTest; j++)
            arr[j] = arrCopy[j];
        int newCycleIterationsCount = bubbleSort(arr, countOfNumbers);
        cycleIterationsCount = (cycleIterationsCount + newCycleIterationsCount) / 2;
    }
    delete arrCopy;
    double time = (double)(clock() - startTime) / CLOCKS_PER_SEC;

    Results results;
    results.time = time;
    results.cycleIterationsCount = cycleIterationsCount;
    return results;
}

void updateMeasurements(map <int, double[2]> &measurements, int countOfNumbers,
                        double averageTime, int cycleIterationsCount)
{
    if (measurements.find(countOfNumbers) == measurements.end())
    {
        measurements[countOfNumbers][0] = averageTime;
        measurements[countOfNumbers][1] = cycleIterationsCount;
    }
    else
    {
        measurements[countOfNumbers][0] = (measurements[countOfNumbers][0] + averageTime) / 2;
        measurements[countOfNumbers][1] = (measurements[countOfNumbers][1] + cycleIterationsCount) / 2;
    }
}

string zfill(int number)
{
    string fileName = to_string(number);
    while (fileName.length() < 3)
    {
        fileName = "0" + fileName;
    }
    return fileName;
}

int main()
{
    int countOfTestFiles = countOfFilesInDirectory("../tests/");
    // ключи - размеры входных данных, значения - время выполнения и количество итераций в цикле
    map <int, double[2]> measurements;

    for (int i = 1; i <= countOfTestFiles; i++)
    {
        ifstream file("../tests/" + zfill(i) + ".txt");
        auto [countOfNumbers, arr] = readDataFromFile(file);

        Results results = averageProcessingResults(arr, countOfNumbers);
        updateMeasurements(measurements, countOfNumbers, results.time,
                           results.cycleIterationsCount);

        delete arr;
        arr = nullptr;
        file.close();
    }

    printMeasurementsIntoFile(measurements);
    return 0;
}
