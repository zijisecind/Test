
// TestBraView.h: CTestBraView 类的接口
//

#pragma once


class CTestBraView : public CView
{
protected: // 仅从序列化创建
	CTestBraView() noexcept;
	DECLARE_DYNCREATE(CTestBraView)

// 特性
public:
	CTestBraDoc* GetDocument() const;

// 操作
public:
	void BresenhamLine(CDC* pDC, CPoint p0, CPoint p1);
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTestBraView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TestBraView.cpp 中的调试版本
inline CTestBraDoc* CTestBraView::GetDocument() const
   { return reinterpret_cast<CTestBraDoc*>(m_pDocument); }
#endif

