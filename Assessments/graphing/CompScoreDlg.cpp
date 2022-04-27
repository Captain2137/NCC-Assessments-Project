// CompScore.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "CompScore.h"
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
CompScore::CompScore(CWnd* pParent /*=NULL*/)
    : CDialog(IDD_COMPSCORE, pParent)
{
    firstChart = 0;
    //firstColorAxis = 0;
}

//
// Destructor
//
CompScore::~CompScore()
{
    // Delete the old chart in m_ChartViewer unless it is the first chart
    if (m_ChartViewer.getChart() != firstChart)
        delete m_ChartViewer.getChart();

    // Delete the first chart
    delete firstChart;

    // Delete the chart in the m_ViewPortControl
    delete m_ViewPortControl.getChart();
}


void CompScore::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PointerPB, m_PointerPB);
    DDX_Control(pDX, IDC_ChartViewer, m_ChartViewer);
    DDX_Control(pDX, IDC_ViewPortControl, m_ViewPortControl);
}

BEGIN_MESSAGE_MAP(CompScore, CDialog)
    ON_WM_PAINT()
    //ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_SavePB, OnSavePB)
    //ON_WM_HSCROLL()
    ON_CONTROL(CVN_ViewPortChanged, IDC_ChartViewer, OnViewPortChanged)
END_MESSAGE_MAP()


//
// Initialization
//
BOOL CompScore::OnInitDialog()
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
void CompScore::OnSavePB()
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
void CompScore::OnViewPortChanged()
{
    // Update the chart if necessary
    if (m_ChartViewer.needUpdateChart())
        drawChart(&m_ChartViewer);
}

//
// Load the data
//
void CompScore::loadData()
{

}

//
// Draw the chart and display it in the given viewer
//
void CompScore::drawChart(CChartViewer* viewer)
{
    // The XY points for the scatter chart
    double dataX0[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    const int dataX0_size = (int)(sizeof(dataX0) / sizeof(*dataX0));
    double dataY0[] = { 0, 0, 0, 2.3, 2.3, 2.5, 2.5, 2.6, 2.7, 3.0, 3.1 };
    const int dataY0_size = (int)(sizeof(dataY0) / sizeof(*dataY0));

    // Create a XYChart object of size 450 x 420 pixels
    XYChart* c = new XYChart(450, 420);

    // Set the plotarea at (55, 65) and of size 350 x 300 pixels, with a light grey border
    // (0xc0c0c0). Turn on both horizontal and vertical grid lines with light grey color (0xc0c0c0)
    c->setPlotArea(55, 65, 350, 300, -1, -1, 0xc0c0c0, 0xc0c0c0, -1);

    // Add a legend box at (50, 30) (top of the chart) with horizontal layout. Use 12pt Times Bold
    // Italic font. Set the background and border color to Transparent.
    c->addLegend(50, 30, false, "Times New Roman Bold Italic", 12)->setBackground(Chart::Transparent
    );

    // Add a title to the chart using 18pt Times Bold Itatic font.
    c->addTitle("CSCI999 Sping 2022 Section A Competency 2 Scores", "Times New Roman Bold Italic", 14);

    // Add a title to the y axis using 12pt Arial Bold Italic font
    c->yAxis()->setTitle("Student Achievement", "Arial Bold Italic", 12);

    // Add a title to the x axis using 12pt Arial Bold Italic font
    c->xAxis()->setTitle("Students", "Arial Bold Italic", 12);

    // Set the axes line width to 3 pixels
    c->xAxis()->setWidth(3);
    c->yAxis()->setWidth(3);

    // Add an orange (0xff9933) scatter chart layer, using 13 pixel diamonds as symbols
    c->addScatterLayer(DoubleArray(dataX0, dataX0_size), DoubleArray(dataY0, dataY0_size),
        "", Chart::CircleSymbol, 8, 0xff0000);

    double phx[] = { 0 };
    const int phx_size = (int)(sizeof(phx) / sizeof(*phx));
    double phy[] = { 3.5 };
    const int phy_size = (int)(sizeof(phy) / sizeof(*phy));

    c->addScatterLayer(DoubleArray(phx, phx_size), DoubleArray(phy, phy_size),
        "", Chart::CircleSymbol, 0, 0x000000);

    // Output the chart
    viewer->setChart(c);

    //include tool tip for the chart
    viewer->setImageMap(c->getHTMLImageMap("clickable", "",
        "title='[{dataSetName}] Weight = {x} kg, Length = {value} cm'"));
}

/////////////////////////////////////////////////////////////////////////////
// General utilities

//
// Load an icon resource into a button
//
void CompScore::loadButtonIcon(int buttonId, int iconId, int width, int height)
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
DoubleArray CompScore::vectorToArray(std::vector<double>& v)
{
    return (v.size() == 0) ? DoubleArray() : DoubleArray(&(v[0]), (int)v.size());
}