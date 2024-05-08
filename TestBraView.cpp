
// TestBraView.cpp: CTestBraView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "TestBra.h"
#endif

#include "TestBraDoc.h"
#include "TestBraView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define	PI 3.1425926
#define Round(d) int(floor(d+0.5))
#endif


// CTestBraView

IMPLEMENT_DYNCREATE(CTestBraView, CView)

BEGIN_MESSAGE_MAP(CTestBraView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTestBraView 构造/析构

CTestBraView::CTestBraView() noexcept
{
	// TODO: 在此处添加构造代码

}

CTestBraView::~CTestBraView()
{
}

BOOL CTestBraView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTestBraView 绘图

void CTestBraView::BresenhamLine(CDC* pDC, CPoint p0, CPoint p1)
{
	COLORREF crColor = RGB(247, 215, 24);
	int dx = abs(p1.x - p0.x);
	int dy = abs(p1.y - p0.y);
	BOOL binterChange = FALSE;
	int e, signX, signY, temp;
	signX = (p1.x > p0.x) ? 1 : ((p1.x < p0.x) ? -1 : 0);
	signY = (p1.y > p0.y) ? 1 : ((p1.y < p0.y) ? -1 : 0);
	if (dy > dx) {
		temp = dx;
		dx = dy;
		dy = temp;
		binterChange = TRUE;
	}
	e = -dx;
	int x = p0.x, y = p0.y;
	for (int i = 1; i <= dx; i++) {
		pDC->SetPixelV(x, y, crColor);
		if (binterChange) {
			y += signY;
		}
		else {
			x += signX;
		}
		e += 2 * dy;
		if (e >= 0) {
			if (binterChange) {
				x += signX;
			}
			else {
				y += signY;
			}
			e -= 2 * dx;
		}

	}



}

void CTestBraView::OnDraw(CDC* pDC)
{
	CTestBraDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(), rect.Height());
	pDC->SetViewportExt(rect.Width(), -rect.Height());
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);
	double R = rect.Width() / 6;
	CPoint p0(0, 0), p1;
	for (int beta = 0; beta < 360; beta++) {
		p1.x = Round(R * cos(beta * PI / 180));
		p1.y = Round(R * sin(beta * PI / 180));
		BresenhamLine(pDC, p0, p1);
	}


}


// CTestBraView 打印

BOOL CTestBraView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTestBraView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CTestBraView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CTestBraView 诊断

#ifdef _DEBUG
void CTestBraView::AssertValid() const
{
	CView::AssertValid();
}

void CTestBraView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestBraDoc* CTestBraView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestBraDoc)));
	return (CTestBraDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestBraView 消息处理程序
