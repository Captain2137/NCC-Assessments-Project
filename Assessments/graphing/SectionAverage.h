// SectionAverage.h : header file
//

#pragma once

#include "ChartViewer.h"
#include <afxmt.h>
#include <vector>


// SectionAverage dialog
class SectionAverage : public CDialog
{
public:
	SectionAverage(CWnd* pParent = NULL);	        // standard constructor
	~SectionAverage();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SECTIONAVERAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	DECLARE_MESSAGE_MAP()

protected:
	// Controls
	CButton	m_PointerPB;
	//CSliderCtrl	m_ZoomBar;
	CChartViewer m_ChartViewer;
	CViewPortControl m_ViewPortControl;

	// Override
	virtual BOOL OnInitDialog();

	// Message handlers
	afx_msg void OnSavePB();
	afx_msg void OnViewPortChanged();

	// Data arrays for the scrollable / zoomable chart.
	std::vector<double> dataX;
	std::vector<double> dataY;
	std::vector<double> dataZ;

	// To ensure color consistency, we need to save the first color axis and
	// synchronize the color axis of the zoom-in charts with the this axis.
	XYChart* firstChart;
	//ColorAxis* firstColorAxis;

	// Load data into data arrays
	void loadData();

	// Draw chart
	void drawChart(CChartViewer* viewer);

	// utility to load icon resource to a button
	void loadButtonIcon(int buttonId, int iconId, int width, int height);

	// utility to convert std::vector to a DoubleArray
	DoubleArray vectorToArray(std::vector<double>& v);
};
