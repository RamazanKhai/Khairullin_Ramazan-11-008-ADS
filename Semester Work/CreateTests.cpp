#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <time.h>
#include <direct.h>
using namespace std;

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
    srand(time(NULL));
    auto answer = mkdir("tests");
    if (answer == -1)
    {
        cout << "Tests folder is already present" << endl;
    }
    else
    {
        const int countOfTests = 10;
        for (int i = 1; i <= countOfTests; i++)
        {
            ofstream file("./tests/" + zfill(i) + ".txt");
            int countOfNumbers = rand() % 10000 + 100;
            file << to_string(countOfNumbers) << endl;
            for (int j = 0; j < countOfNumbers; j++)
            {
                file << to_string(rand() % 10000 + 100) << endl;
            }
            file.close();
        }
    }

    return 0;
}
