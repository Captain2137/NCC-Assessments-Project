// CompAverageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CompAverage.h"
#include "chartdir.h"
#include <math.h>
#include <sstream>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
// Constructor
//
CompAverage::CompAverage(CWnd* pParent /*=NULL*/)
    : CDialog(IDD_COMPAVERAGE, pParent)
{
    firstChart = 0;
    //firstColorAxis = 0;
}

//
// Destructor
//
CompAverage::~CompAverage()
{
    // Delete the old chart in m_ChartViewer unless it is the first chart
    if (m_ChartViewer.getChart() != firstChart)
        delete m_ChartViewer.getChart();

    // Delete the first chart
    delete firstChart;

    // Delete the chart in the m_ViewPortControl
    delete m_ViewPortControl.getChart();
}


void CompAverage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PointerPB, m_PointerPB);
    DDX_Control(pDX, IDC_ChartViewer, m_ChartViewer);
    DDX_Control(pDX, IDC_ViewPortControl, m_ViewPortControl);
}

BEGIN_MESSAGE_MAP(CompAverage, CDialog)
    ON_WM_PAINT()
    //ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_SavePB, OnSavePB)
    //ON_WM_HSCROLL()
    ON_CONTROL(CVN_ViewPortChanged, IDC_ChartViewer, OnViewPortChanged)
END_MESSAGE_MAP()


//
// Initialization
//
BOOL CompAverage::OnInitDialog()
{
    CDialog::OnInitDialog();

    //
    // Initialize controls
    //

    // Load icons to mouse usage buttons
    loadButtonIcon(IDC_SavePB, IDI_SavePB, 100, 20);

    // Set Pointer pushbutton into clicked state
    m_PointerPB.SetCheck(1); //???

    // Set initial mouse usage for ChartViewer
    //What's this???
    //m_ChartViewer.setMouseUsage(Chart::MouseUsageScroll);
    //m_ChartViewer.setScrollDirection(Chart::DirectionHorizontalVertical);

    // Load the data
    

    // Trigger the ViewPortChanged event to draw the chart
    m_ChartViewer.updateViewPort(true, true);

    // Configure the CViewPortControl to use transparent black for region outside the viewport,
    // that is, to darken the outside region.
    m_ViewPortControl.setViewPortExternalColor(0x7f000000);
    m_ViewPortControl.setViewPortBorderColor(0x7fffffff);
    m_ViewPortControl.setSelectionBorderColor(0x7fffffff);

    // Bind the CChartViewer to the CViewPortControl
    m_ViewPortControl.setViewer(&m_ChartViewer);

    return TRUE;
}

//
// User clicks on the Save pushbutton
//
void CompAverage::OnSavePB()
{
    // Supported formats = PNG, JPG, GIF, BMP, SVG and PDF
    TCHAR szFilters[] = _T("PNG (*.png)|*.png|JPG (*.jpg)|*.jpg|GIF (*.gif)|*.gif|")
        _T("BMP (*.bmp)|*.bmp|SVG (*.svg)|*.svg|PDF (*.pdf)|*.pdf||");

    // The standard CFileDialog
    CFileDialog fileDlg(FALSE, _T("png"), _T("chartdirector_demo"), OFN_HIDEREADONLY |
        OFN_OVERWRITEPROMPT, szFilters);
    if (fileDlg.DoModal() != IDOK)
        return;

    // Save the chart
    CString path = fileDlg.GetPathName();
    BaseChart* c = m_ChartViewer.getChart();
    if (0 != c)
        c->makeChart(TCHARtoUTF8(path));
}

//
// The ViewPortChanged event handler. This event occurs if the user scrolls or zooms in or 
// out the chart by dragging or clicking on the chart. It can also be triggered by calling
// CChartViewer.updateViewPort and by the CViewPortControl.
//
void CompAverage::OnViewPortChanged()
{
    // Update the chart if necessary
    if (m_ChartViewer.needUpdateChart())
        drawChart(&m_ChartViewer);
}

//
// Load the data
//
void CompAverage::loadData()
{

}

//
// Draw the chart and display it in the given viewer
//
void CompAverage::drawChart(CChartViewer* viewer)
{
    // The data for the bar chart
    // This data would be the average of the competencies
    double data[] = { 4.090909, 3.63636, 3.090909};
    const int data_size = (int)(sizeof(data) / sizeof(*data));

    // The labels for the bar chart
    // These labels would be the competency names
    const char* labels[] = { "Outcome 1", "Outcome 2", "Outcome 3" };
    const int labels_size = (int)(sizeof(labels) / sizeof(*labels));

    // Create a XYChart object of size 600 x 400 pixels
    XYChart* c = new XYChart(600, 400);

    // Add a title box using grey (0x555555) 24pt Arial Bold font
    // Call getName, getTeacher
    c->addTitle("Spring2020 CRN: 20855 CSCI103N Section: A Website Development II, Teacher One", "Arial Bold", 18, 0x555555);

    // Set the plotarea at (70, 60) and of size 500 x 300 pixels, with transparent background and
    // border and light grey (0xcccccc) horizontal grid lines
    c->setPlotArea(70, 60, 500, 300, Chart::Transparent, -1, Chart::Transparent, 0xcccccc);

    // Set the x and y axis stems to transparent and the label font to 12pt Arial
    c->xAxis()->setColors(Chart::Transparent);
    c->yAxis()->setColors(Chart::Transparent);
    c->xAxis()->setLabelStyle("Arial", 12);
    c->yAxis()->setLabelStyle("Arial", 12);

    // Add a purple (0x800080) mark at y = 70 using a line width of 2.
    c->yAxis()->addMark(2.2, 0x800080, "Test = 2.2")->setLineWidth(2);

    // Add a blue (0x6699bb) bar chart layer with transparent border using the given data
    c->addBarLayer(DoubleArray(data, data_size), 0x6699bb)->setBorderColor(Chart::Transparent);

    // Set the labels on the x axis.
    c->xAxis()->setLabels(StringArray(labels, labels_size));

    // For the automatic y-axis labels, set the minimum spacing to 40 pixels.
    c->yAxis()->setTickDensity(40);

    // Add a title to the y axis using dark grey (0x555555) 14pt Arial Bold font
    c->yAxis()->setTitle("Student Achievement", "Arial Bold", 14, 0x555555);

    // Output the chart
    viewer->setChart(c);

    //include tool tip for the chart
    viewer->setImageMap(c->getHTMLImageMap("clickable", "", "title='{xLabel}: {value} kg'"));
}

/////////////////////////////////////////////////////////////////////////////
// General utilities

//
// Load an icon resource into a button
//
void CompAverage::loadButtonIcon(int buttonId, int iconId, int width, int height)
{
    // Resize the icon to match the screen DPI for high DPI support
    HDC screen = ::GetDC(0);
    double scaleFactor = GetDeviceCaps(screen, LOGPIXELSX) / 96.0;
    ::ReleaseDC(0, screen);
    width = (int)(width * scaleFactor + 0.5);
    height = (int)(height * scaleFactor + 0.5);

    GetDlgItem(buttonId)->SendMessage(BM_SETIMAGE, IMAGE_ICON, (LPARAM)::LoadImage(
        AfxGetResourceHandle(), MAKEINTRESOURCE(iconId), IMAGE_ICON, width, height, LR_DEFAULTCOLOR));
}

// Convert std::vector to a DoubleArray
//
DoubleArray CompAverage::vectorToArray(std::vector<double>& v)
{
    return (v.size() == 0) ? DoubleArray() : DoubleArray(&(v[0]), (int)v.size());
}