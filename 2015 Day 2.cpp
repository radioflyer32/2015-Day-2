/*
* --- Day 2: I Was Told There Would Be No Math ---
The elves are running low on wrapping paper, and so they need to submit an order for more. They have a list of the dimensions (length l, width w, and height h) of each present, and only want to order exactly as much as they need.

Fortunately, every present is a box (a perfect right rectangular prism), which makes calculating the required wrapping paper for each gift a little easier: find the surface area of the box, which is 2*l*w + 2*w*h + 2*h*l. 
The elves also need a little extra paper for each present: the area of the smallest side.

For example:

A present with dimensions 2x3x4 requires 2*6 + 2*12 + 2*8 = 52 square feet of wrapping paper plus 6 square feet of slack, for a total of 58 square feet.
A present with dimensions 1x1x10 requires 2*1 + 2*10 + 2*10 = 42 square feet of wrapping paper plus 1 square foot of slack, for a total of 43 square feet.
All numbers in the elves' list are in feet. How many total square feet of wrapping paper should they order?
*/

/*
* Outline of process that needs to happen...
* Text is stored in a file
* Access each line of the file and determine measurements, keeping in mind smallest side of current package... Store the cumulative measurements
* Output the total square footage
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
    using std::cout;
    using std::cin;

    // Variables for calculating wrapping paper needed
    int valLength = 0;
    int valHeight = 0;
    int valWidth = 0;
    int smallestSide = 0;
    int totalSquareFeetNeeded = 0; // Var for total square footage

    // Open file
    std::string filename = "Gift List.txt"; // Variable for filename info
    std::ifstream inputFile(filename);
    
    if (!inputFile.is_open()) // output error in case file cannot be opened...
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    // Access each line of text and calculate the square footage needed
    std::string line;
    char lineDeliminator = 'x';

    while (getline(inputFile, line))
    {
        //std::cout << line << std::endl; // ##### Test line for testing file and line access #####
        
        // Parse through the current line and separate each number, removing the x... then store in each of lenght, width, and height
        std::vector<int> currentMeasurements;

        std::stringstream myStringStream(line);
        std::string temp;

        while (std::getline(myStringStream, temp, lineDeliminator))
        {
            // Convert extracted substring to an int
            currentMeasurements.push_back(std::stoi(temp));
        }

        /*
        * Do calculations for each gift including determine smallest side area ... 2*l*w + 2*w*h + 2*h*l + (area of smallest side)
        */

        valLength = currentMeasurements[0];
        valWidth = currentMeasurements[1];
        valHeight = currentMeasurements[2];

        // Calc side 1 (2*l*w)
        int sideOne = (valLength * valWidth);

        smallestSide = sideOne;
        sideOne = 2 * sideOne;

        // Calc side 2 (2*w*h)
        int sideTwo = (valWidth * valHeight);
        if (sideTwo < smallestSide)
        {
            smallestSide = sideTwo;
        }

        sideTwo = 2 * sideTwo;

        // Calc side 3 (2*h*l)
        int sideThree = (valHeight * valLength);
        if (sideThree < smallestSide)
        {
            smallestSide = sideThree;
        }

        sideThree = 2 * sideThree;

        /*
        * Store each square footage and calculate total square feet.
        */
        // Calc total area
        int boxArea = sideOne + sideTwo + sideThree + smallestSide;
        totalSquareFeetNeeded += boxArea; // Add current box area to total area needed
    }

    cout << "Total square footage needed: " << totalSquareFeetNeeded << std::endl;

    // Close the file
    inputFile.close();

    return 0;
}
