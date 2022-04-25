#include "CourseData.h"
#include "Util.h"

void CourseData::calculate() {
    // The 2D vector of the average, median, percent above three, and standard deviation
    std::vector<std::vector<double>> calcedData = util::calcData(data);

    average = calcedData[0];
    median = calcedData[1];
    percent = calcedData[2];
    deviation = calcedData[3];
}