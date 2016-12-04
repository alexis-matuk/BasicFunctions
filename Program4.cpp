/******************************************************************
 Program Assignment:            4
 Name:                          Alexis Matuk
 Date:                          12 de febrero de 2016
 Description:                   Program that takes in two rows of data and returns the 
 standard deviation, very small, small, medium, large and very large ranges
 ***********************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

/************************************************************
 Reuse instructions
 void openFile(std::ifstream & _file, std::string route)
  	Purpose: Function that accepts a file stream and a route, and opens a the file 
 in the given absolute or relative route
  ***********************************************************/
void openFile(std::ifstream & _file, std::string route)
{
    try
    {
        if (std::ifstream(route))
        {
            std::cout << "File found... opening " << std::endl;
            _file.open(route);
            if(_file.fail())
            {
                std::cout << "Error reading file... aborting" << std::endl;
                throw 2;
            }
        }
        else
        {
            std::cout << "File not found... Aborting" << std::endl;
            throw 1;
        }
    }
    catch (int e)
    {
        std::cerr << "Error reading data... Exception " << e << " caught" << std::endl;
    }
}

/************************************************************
 Reuse instructions
 std::vector<float> testData(std::ifstream & _file, int column1, int column2)
  	Purpose: Function that accepts a file and two columns, and 
 returns the first column divided by the second in a vector.
  ***********************************************************/
std::vector<float> testData(std::ifstream & _file, int column1, int column2)
{
    std::vector<float> data;
    if(_file.is_open())
    {
        _file.clear();
        _file.seekg(0, std::ios::beg);
        for( std::string line; getline( _file, line ); )
        {
            std::vector<float> columns;
            std::istringstream is(line);
            float a,b;
            is >> a >> b;
            columns.push_back(a);
            columns.push_back(b);
            data.push_back(columns[column1]/columns[column2]);
            std::cout << columns[column1] << "  " << columns[column2] << std::endl;
        }
    }
    else
        std::cout << "File not opened" << std::endl;
    return data;
}

/************************************************************
 Reuse instructions
 float getAverage(std::vector<float> data)
 Purpose: Function that takes a vector of floats as parameter and returns the “avg” value.
 ***********************************************************/
float getAverage(std::vector<float> data)
{
    float sum = 0;
    size_t n = data.size();
    for(int i = 0; i < n; i++)
    {
        sum += log(data[i]);
    }
    return sum / n;
}

/************************************************************
 Reuse instructions
 float getVar(std::vector<float> data, float average)
 Purpose: Function that accepts a vector of floats and the avergae, and returns the “var” value
 ***********************************************************/
float getVar(std::vector<float> data, float average)
{
    float sum = 0;
    size_t n = data.size();
    for(int i = 0; i < n; i++)
    {
        sum += pow((log(data[i]) - average),2);
    }
    return sum / (n - 1);
}
/************************************************************
 Reuse instructions
 float getStandardDev(std::vector<float> data)
 Purpose: Function that accepts a vector of floats and returns the 
 standard deviation. This function uses getAverage and getVar.
  ***********************************************************/

float getStandardDev(std::vector<float> data)
{
    float average = getAverage(data);
    float var = getVar(data, average);
    return sqrtf(var);
}

/************************************************************
 Reuse instructions
 std::vector<float> getValues(float average, float standardDeviation)
 Purpose: Function that accepts the average and standard deviation, 
 and returns a vector containing the values for VS, S, M, L, VL
 ***********************************************************/
std::vector<float> getValues(float average, float standardDeviation)
{
    std::vector<float> result;
    result.push_back(average - (2 * standardDeviation));//Very Small value
    result.push_back(average - standardDeviation);//Small value
    result.push_back(average);//Medium value
    result.push_back(average + standardDeviation);//Large value
    result.push_back(average + (2 * standardDeviation));//Very Large value
    for(int i = 0; i < result.size(); i++)
        result[i] = exp(result[i]);
    return result;
}

/************************************************************
 Reuse instructions
 void performTest(std::vector<float> data)
 Purpose: Function that accepts a vector of floats and prints their values, as well as the initial set of data used.
 ***********************************************************/
void performTest(std::vector<float> data)
{
    float average = getAverage(data);
    float standardDeviation = getStandardDev(data);
    std::vector<float> result;
    result = getValues(average, standardDeviation);
    std::cout << "=========================" << std::endl;
    std::cout << "-----Divided data-----" << std::endl;
    for(int i = 0; i < data.size(); i++)
        std::cout << data[i] << std::endl;
    std::cout << "=========================" << std::endl;
    std::cout << "-----Results-----" << std::endl;
    std::cout << "VS: " << result[0] << std::endl;
    std::cout << "S: " << result[1] << std::endl;
    std::cout << "M: " << result[2] << std::endl;
    std::cout << "L: " << result[3] << std::endl;
    std::cout << "VL: " << result[4] << std::endl;
}

/************************************************************
 Reuse instructions
 int main(int argc, const char * argv[])
 Purpose: Main function of the program
 ***********************************************************/
int main(int argc, const char * argv[])
{
    std::ifstream file;
    openFile(file, "test1.txt");
    std::cout << "=========================" << std::endl;
    std::cout << "-----Test data-----" << std::endl;
    std::vector<float> test1 = testData(file, 0, 1);
    performTest(test1);
    file.close();
    openFile(file, "test2.txt");
    std::cout << "=========================" << std::endl;
    std::cout << "-----Test data-----" << std::endl;
    std::vector<float> test2 = testData(file, 0, 1);
    performTest(test2);
    file.close();
}