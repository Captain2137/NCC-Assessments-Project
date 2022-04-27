#include "stdafx.h" //Allows for the use of the DoModal function which creates an unadjustable window
#include "mfccharts.h" //Creates an array that the demo window uses to display the demo graphs
#include "chartdir.h"

//These are the header files of charts that display in separate windows
#include "CompAverage.h"
#include "SectionAverage.h"
#include "CompScore.h"

//All the functions up to demoCharts[] are implementation files

void compaverage(CChartViewer* viewer, int /* chartIndex */)
{
    CompAverage* d = new CompAverage(); //Because this chart will appear in a window, it needs to be in its own file
    d->DoModal(); //DoModal is what creates a windowed view. It's a function of CDialog
    delete d; //Delete the window once the user clicks on the 'x' button
}

void sectionaverage(CChartViewer* viewer, int /* chartIndex */)
{
    SectionAverage* d = new SectionAverage(); //Because this chart will appear in a window, it needs to be in its own file
    d->DoModal(); //DoModal is what creates a windowed view. It's a function of CDialog
    delete d; //Delete the window once the user clicks on the 'x' button
}

void compscore(CChartViewer* viewer, int /* chartIndex */)
{
    CompScore* d = new CompScore(); //Because this chart will appear in a window, it needs to be in its own file
    d->DoModal(); //DoModal is what creates a windowed view. It's a function of CDialog
    delete d; //Delete the window once the user clicks on the 'x' button
}

//This array stores all the demo charts that can be used. The empty array at the end signals the end of the array.
DemoChart demoCharts[] = 
{

    {"Graphs", 0, 0, "zoomchart.ico"},

        {"Competency Average", 1, compaverage, 0},
        {"Section Average", 1, sectionaverage, 0},
        {"Competency Score", 1, compscore, 0},

    {0, 0, 0, 0}
};