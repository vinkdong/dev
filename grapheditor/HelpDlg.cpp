// HelpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ex_draw.h"
#include "HelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg dialog


CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelpDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelpDlg)
	DDX_Control(pDX, IDC_STATIC_HLP, m_stat_help);
	DDX_Control(pDX, IDC_EDIT_HELP, m_edit_help);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialog)
	//{{AFX_MSG_MAP(CHelpDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg message handlers

BOOL CHelpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    m_captionFont.CreateFont(30, 15, 0, 0, 16, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("楷体"));

    m_txtFont.CreateFont(16, 8, 0, 0, 10, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("宋体"));

    m_edit_help.SetFont(&m_txtFont);
    m_stat_help.SetFont(&m_captionFont);
    GetDlgItem(IDOK)->SetFont(&m_txtFont);

    CString str = _T(
        " 以下涉及操作帮助和功能讲解。\r\n"

        "\r\n ============================= 一、功能概述 =============================\r\n"
        "\r\n 1. 添加启动界面"
        "\r\n 2. 文件可保存为位图（光栅化）和矢量图（序列化）"
        "\r\n 3. 添加控制面板和工具栏"
        "\r\n 4. 添加图形列表（双击定位）"
        "\r\n 5. 图形信息显示（选中右键）"
        "\r\n 6. 图形信息编辑（选中右键）"
        "\r\n 7. 图形删除（选中右键）"
        "\r\n 8. 图形拖拽与复制（按Ctrl键）"
        "\r\n 9. 图形拉伸变形"
        "\r\n 10. 图形位置微调（按方向键）"
        "\r\n 11. 撤消和恢复功能"
        "\r\n 12. Tab次序预览（Tab键）"
        "\r\n 13. 右键直接进入选择状态"
        "\r\n 14. 设置隐藏和显示隐藏（图形菜单）"
        "\r\n 15. 响应鼠标滚动"
        "\r\n 15. 画布动态响应窗口大小变化"
        "\r\n \r\n"

        "\r\n ============================= 二、使用帮助 =============================\r\n"
        "\r\n 1. 图片只能保存为位图（*.bmp），且为无损压缩"
        "\r\n 2. 控制栏可供选择的内容："
        "\r\n    （1）画笔颜色、风格、粗细"
        "\r\n    （2）画刷颜色、风格"
        "\r\n 3. 在选择模式下可以进行的操作："
        "\r\n    （1）选中、拖动、拉伸变形、按CTRL键复制、按方向键进行微调"
        "\r\n    （2）右键菜单弹出信息（先选中）：包括画布大小、图形操作、图形信息概况"
        "\r\n    （3）选中之后必须按住图形周围的圆点进行变形"
        "\r\n 4. 在画图模式下可以进行的操作："
        "\r\n    （1）一般操作"
        "\r\n    （2）按SHIFT键画正形（正圆、正方形、斜45度直线）"
        "\r\n 5. 附加功能："
        "\r\n    （1）Tab次序：控制显示在【图形】菜单中调整"
        "\r\n    （2）隐藏：图形设置隐藏，隐藏显示在【图形】菜单中调整"
        "\r\n    （3）自定义名称：图形设置中更改"
        "\r\n    （4）图形列表：双击可定位图形，选中图形也会定位列表"
        "\r\n \r\n"

        "\r\n ============================= 三、代码结构 =============================\r\n"
        "\r\n 1. 概况"
        "\r\n    （1）代码行数：约3000行（View：~1000 Graphic：~1000）"
        "\r\n    （2）主要类名：（带*的会有技术讲解）"
        "\r\n        * CGraphic（子类：直线类CLine，椭圆类CEllipse，矩形类CRectangle，曲线类CCurve）"
        "\r\n        CHelpDlg（模态帮助提示界面）"
        "\r\n        * CStartupDlg（非模态启动界面）"
        "\r\n        ConfigDlg（模态图形编辑界面）"
        "\r\n        GraphicMember（通用图形数据转存类）"
        "\r\n        * CGraphicLog（操作记录类，实现撤消和恢复）"
        "\r\n 2. 类的讲解和技术解析（带*的会详解）"
        "\r\n    （1）CGraphic：图形基类"
        "\r\n        1) 基类及派生类数据成员（看名称，略）"
        "\r\n        2) 主要静态函数"
        "\r\n            CreateGraphic： 根据介质创建相应类并赋值"
        "\r\n            GetIdBySelection... ： 存储画笔（刷）类型的一种方式，采用位运算"
        "\r\n            LineHitTest： 若点在直线上，那么短两边和等于第三边，以此判断"
        "\r\n        3) 主要成员函数"
        "\r\n            Serialize： 序列化（在子类中必须先调用父类的序列化）"
        "\r\n            UpdateData： 类似于MFC中的UpdateData（GraphicMember充当交换介质）"
        "\r\n            Draw： 画图"
        "\r\n            DrawSelectedEdge： 画选中后四周的点"
        "\r\n            * HitTest： 测试点是否在图形内部，若是，bResult为真"
        "\r\n            * HitSizingTest： 测试点是否在图形的四周变形点上，若是，bResult为真"
        "\r\n            GetRect： 返回图形的矩形坐标，便于重绘"
        "\r\n        4) 宏"
        "\r\n            选择误差：（->N：趋于N更精确）"
        "\r\n                SELECT_MISS_LINE： 直线（->1）"
        "\r\n                SELECT_MISS_ELLIPSE： 椭圆（->0）"
        "\r\n                DRAG_INF_WIDTH： 拉伸圆点"
        "\r\n            其他："
        "\r\n                INF_WIDTH： 图形外边框厚度"
        "\r\n                LOG_MAX_SAVE： 最大撤消数"
        "\r\n                图形类的类型（LINE...）"
        "\r\n                IF_NULL_PEN： 是否是透明画笔"
        "\r\n                IF_NULL_BRUSH： 是否是透明画刷"
        "\r\n                Convert_To_Graphic：转换为图形类"
        "\r\n        5) 带*讲解"
        "\r\n            HitTest和HitSizingTest：其实就是个回调函数，用来判断点是否在图形内部"
        "\r\n                HitSizingTest有另外两个参数 PtX PtY，是int**类型（有原因的）"
        "\r\n                假如要让图形变形，就要改它坐标，有时要改它的A坐标的X，B坐标的Y"
        "\r\n                那么就要保存原坐标的LONG变量指针，再间接改变它"
        "\r\n        6) 其他内容"
        "\r\n            操作图形的界面很特殊。可以这么想，假如所有图形就不可拖动和更改，图形"
        "\r\n                内容变的丰富，可以响应许多消息，可以加载位图，那么这个程序就实现"
        "\r\n                了一般商业程序UI的功能。所以，可以用设计UI的思想来设计这些类。"
        "\r\n            一般的开源UI库有Duilib和XCGUI，涉及工厂模式，观察者模式等等模式，且"
        "\r\n                实现控件坐标非硬性编码，界面可由ZIP加载（通过解析XML和图片），"
        "\r\n                所以多读优秀的代码可以提升思想。"
        "\r\n            有兴趣可以看Java的《Head First设计模式》，语言不同，但思想是互通的。"
        "\r\n            MFC的思想不错，只是可重用性不足，安全性不足，所以现在的软件一般采用"
        "\r\n                开源的或自己开发的界面库。"
        "\r\n            掌握了思想，技术实现就不是问题（只是时间问题）。"
        "\r\n    （2）CGraphicLog"
        "\r\n        1) 枚举体： 代表操作类型，包括新增，更改，删除"
        "\r\n        2) 结构体： GraphicOperation 包括操作类型，保存的数据对象，对应下标"
        "\r\n            Trace函数便于调试"
        "\r\n        3) 单词解释： Undo - 撤消，Done - 恢复"
        "\r\n        4) 解释"
        "\r\n            本类的实现思想略为复杂（详见代码注释）"
        "\r\n            虽然有两个成员是CList，但实现的功能是堆栈（思考为什么）"
        "\r\n            因为删除了对象，不能真删了它，不然怎么恢复？"
        "\r\n            对象被更改了，得保存更改之前的备份，这是UPDATE操作（new操作）"
        "\r\n            我又画了东西，那么Done里的东西不复存在，记录记不下了，要删"
        "\r\n            可是会导致重复删除（思考？），怎么解决？"
        "\r\n               “引用”思想"
        "\r\n            ——创建时维持引用计数为1，删除时减去1，如果计数为0则删除。"
        "\r\n    （3）CStartupDlg"
        "\r\n        运用工具：定时器，无模态对话框，线程"
        "\r\n        线程同步方法：事件（CEvent->HANDLE），WaitingForSingleObject"
        "\r\n \r\n"

        "\r\n 3. 其他技术解析"
        "\r\n    （1）双缓冲位图和后台位图"
        "\r\n            直接在屏幕DC上操作，那么每画一次，就得更新一次界面，所以会闪屏"
        "\r\n            如果在缓冲上操作，然后BitBlt给屏幕，那只要更新一次"
        "\r\n            后台位图的功能是：当拖拽图形A的时候，除去这个图形之外的所有图形"
        "\r\n            全部画在X上，此时拖动A，只要将屏幕重设成X，再画改变坐标后的A，"
        "\r\n            再加上双缓冲，就可以有效避免闪屏"
        "\r\n            注：为了简便（累。。），有些细节没有处理，所以还是会有闪屏"
        "\r\n            注2： 在有些BitBlt操作之前，必须先调用UpdateWindow"
        "\r\n    （2）保存为位图"
        "\r\n            位图：BITMAPFILEHEADER，BITMAPINFO，位图像素"
        "\r\n            函数实现详见XXXView::OnSaveAsBitmap，方法固定"
        "\r\n \r\n"

        "\r\n ============================= 四、总体评价 =============================\r\n"
        "\r\n 1. 本人带有代码格式化的习惯（格式化直观体现美和便于阅读）"
        "\r\n    * 推荐格式化工具（Visual Assist X）"
        "\r\n 2. 程序代码相对较长，因此会有未发现的BUG……"
        "\r\n 3. 代码注释较少，故将解释写在帮助中"
        "\r\n 4. 写此文也是为了总结MFC的主要内容"
        "\r\n 5. 不熟悉的类和方法可以查询MSDN"
        "\r\n 6. 尚未尝试的功能：多选（很复杂，相当于重新建构），旋转（像素级运算），"
        "\r\n   （PS：尝试后倒地不起）"
        "\r\n 7. 代码更新：三周"
    );

    m_edit_help.SetWindowText(str);

    GetDlgItem(IDOK)->SetFocus();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CHelpDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	

	// TODO: Change any attributes of the DC here
    if (nCtlColor == CTLCOLOR_STATIC && pWnd->GetDlgCtrlID() == IDC_STATIC_HLP)
    {
        pDC->SetTextColor(RGB(255, 0, 0));
    }
    else if (nCtlColor == CTLCOLOR_STATIC && pWnd->GetDlgCtrlID() == IDC_EDIT_HELP)
    {
        pDC->SetTextColor(RGB(30, 20, 235));
    }

	// TODO: Return a different brush if the default is not desired
	return hbr;
}
