// SectionAverage.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "SectionAverage.h"
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
SectionAverage::SectionAverage(CWnd* pParent /*=NULL*/)
    : CDialog(IDD_SECTIONAVERAGE, pParent)
{
    firstChart = 0;
    //firstColorAxis = 0;
}

//
// Destructor
//
SectionAverage::~SectionAverage()
{
    // Delete the old chart in m_ChartViewer unless it is the first chart
    if (m_ChartViewer.getChart() != firstChart)
        delete m_ChartViewer.getChart();

    // Delete the first chart
    delete firstChart;

    // Delete the chart in the m_ViewPortControl
    delete m_ViewPortControl.getChart();
}


void SectionAverage::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PointerPB, m_PointerPB);
    DDX_Control(pDX, IDC_ChartViewer, m_ChartViewer);
    DDX_Control(pDX, IDC_ViewPortControl, m_ViewPortControl);
}

BEGIN_MESSAGE_MAP(SectionAverage, CDialog)
    ON_WM_PAINT()
    //ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_SavePB, OnSavePB)
    //ON_WM_HSCROLL()
    ON_CONTROL(CVN_ViewPortChanged, IDC_ChartViewer, OnViewPortChanged)
END_MESSAGE_MAP()


//
// Initialization
//
BOOL SectionAverage::OnInitDialog()
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
void SectionAverage::OnSavePB()
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
void SectionAverage::OnViewPortChanged()
{
    // Update the chart if necessary
    if (m_ChartViewer.needUpdateChart())
        drawChart(&m_ChartViewer);
}

//
// Load the data
//
void SectionAverage::loadData()
{

}

//
// Draw the chart and display it in the given viewer
//
void SectionAverage::drawChart(CChartViewer* viewer)
{
    // The data for the bar chart
    
    double data0[] = { 2.4, 2.7, 3.2, 3.1, 3.4 };
    const int data0_size = (int)(sizeof(data0) / sizeof(*data0));
    double data1[] = { 2.9, 2.5, 1.9, 2.6, 2.4 };
    const int data1_size = (int)(sizeof(data1) / sizeof(*data1));
    double data2[] = { 3.0, 3.3, 2.8, 2.7, 2.9 };
    const int data2_size = (int)(sizeof(data2) / sizeof(*data2));
    double data3[] = { 2.1, 2.0, 2.1, 2.2, 1.9 };
    const int data3_size = (int)(sizeof(data3) / sizeof(*data3));
    double data4[] = { 2.7, 3.1, 3.4, 3.6, 3.4 };
    const int data4_size = (int)(sizeof(data4) / sizeof(*data4));
    const char* labels[] = { "Fall 2021\nSection A", "Fall 2021\nSection B", "Spring 2022\nSection A", "Spring 2022\nSection B", "Spring 2022\nSection C" };
    const int labels_size = (int)(sizeof(labels) / sizeof(*labels));

    // Create a XYChart object of size 540 x 375 pixels
    XYChart* c = new XYChart(540, 375);

    // Add a title to the chart using 18pt Times Bold Italic font
    c->addTitle("CSCI999 Section Averages", "Times New Roman Bold Italic", 18);

    // Set the plotarea at (50, 55) and of 440 x 280 pixels in size. Use a vertical gradient color
    // from light blue (f9f9ff) to blue (6666ff) as background. Set border and grid lines to white
    // (ffffff).
    c->setPlotArea(50, 55, 440, 280, c->linearGradientColor(0, 55, 0, 335, 0xf9f9ff, 0x6666ff), -1,
        0xffffff, 0xffffff);

    // Add a legend box at (50, 28) using horizontal layout. Use 10pt Arial Bold as font, with
    // transparent background.
    c->addLegend(50, 28, false, "Arial Bold", 10)->setBackground(Chart::Transparent);

    // Set the x axis labels
    c->xAxis()->setLabels(StringArray(labels, labels_size));

    // Draw the ticks between label positions (instead of at label positions)
    c->xAxis()->setTickOffset(0.5);

    // Set axis label style to 8pt Arial Bold
    c->xAxis()->setLabelStyle("Arial Bold", 8);
    c->yAxis()->setLabelStyle("Arial Bold", 8);

    // Set axis line width to 2 pixels
    c->xAxis()->setWidth(2);
    c->yAxis()->setWidth(2);

    // Add axis title
    c->yAxis()->setTitle("Student Achievement");

    // Add a multi-bar layer with 3 data sets
    BarLayer* layer = c->addBarLayer(Chart::Side);
    layer->addDataSet(DoubleArray(data0, data0_size), 0xff0000, "Competency 1");
    layer->addDataSet(DoubleArray(data1, data1_size), 0x00ff00, "Competency 2");
    layer->addDataSet(DoubleArray(data2, data2_size), 0xff8800, "Competency 3");
    layer->addDataSet(DoubleArray(data3, data3_size), 0x008888, "Competency 4");
    layer->addDataSet(DoubleArray(data4, data4_size), 0xff88ff, "Competency 5");

    // Set bar border to transparent. Use glass lighting effect with light direction from left.
    layer->setBorderColor(Chart::Transparent, Chart::glassEffect(Chart::NormalGlare, Chart::Left));

    // Configure the bars within a group to touch each others (no gap)
    layer->setBarGap(0.2, Chart::TouchBar);

    // Output the chart
    viewer->setChart(c);

    //include tool tip for the chart
    viewer->setImageMap(c->getHTMLImageMap("clickable", "",
        "title='{dataSetName} on {xLabel}: {value} MBytes/hour'"));
}

/////////////////////////////////////////////////////////////////////////////
// General utilities

//
// Load an icon resource into a button
//
void SectionAverage::loadButtonIcon(int buttonId, int iconId, int width, int height)
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
DoubleArray SectionAverage::vectorToArray(std::vector<double>& v)
{
    return (v.size() == 0) ? DoubleArray() : DoubleArray(&(v[0]), (int)v.size());
}