#pragma once
#include "afxwin.h"
#include "Time.h"
#include "EditEx.h"

const int WM_FINDREPLACE = ::RegisterWindowMessage(FINDMSGSTRING);	//将FINDMSGSTRING注册为WM_FINDREPLACE消息

// CLyricEditDlg 对话框

class CLyricEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CLyricEditDlg)

public:
	//定义操作时间标签的枚举
	enum class TagOpreation
	{
		INSERT,		//插入
		REPLACE,	//替换
		DELETE_		//删除
	};

	bool m_dlg_exist{ false };		//如果对话框存在，则为true

	CLyricEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLyricEditDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LYRIC_EDIT_DIALOG };
#endif

protected:
	CFont m_font;			//歌词编辑界面字体
	wstring m_lyric_string;		//歌词字符串
	wstring m_lyric_path;		//歌词路径
	wstring m_original_lyric_path;	//原来的歌词（当前播放歌曲对应的歌词）的路径
	CodeType m_code_type;		//歌词编码
	wstring m_current_song_name;	//正在播放的歌曲名
	bool m_modified{ false };	//如果歌词已更改，则为true
	bool m_lyric_saved{ false };	//如果执行过保存操作，则为true

	CToolTipCtrl m_Mytip;		//鼠标提示
	CStatusBarCtrl m_status_bar;	//状态栏

	CFindReplaceDialog* m_pFindDlg{};   //查找对话框
	CFindReplaceDialog* m_pReplaceDlg{};    //替换对话框
	wstring m_find_str;		//查找的字符串
	wstring m_replace_str;	//替换的字符串
	int m_find_index{ -1 };	//查找的字符串的索引
	bool m_find_down{ true };		//是否向后查找
	bool m_find_flag{ false };

	void OpreateTag(TagOpreation operation);
	bool SaveLyric(const wchar_t* path, CodeType code_type);
	void UpdateStatusbarInfo();			//更新状态栏信息

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
protected:
	CEditEx m_lyric_edit;
public:
	afx_msg void OnBnClickedInsertTagButton();
	afx_msg void OnBnClickedReplaceTagButton();
	afx_msg void OnBnClickedDeleteTag();
	afx_msg void OnBnClickedSaveLyricButton();
//	afx_msg void OnBnClickedSaveAsButton5();
	afx_msg void OnDestroy();
	afx_msg void OnEnChangeEdit1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
//	afx_msg void OnBnClickedOpenLyricButton();
	afx_msg void OnLyricOpen();
	afx_msg void OnLyricSave();
	afx_msg void OnLyricSaveAs();
	afx_msg void OnLyricFind();
	afx_msg void OnLyricReplace();
protected:
	afx_msg LRESULT OnFindReplace(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnFindNext();
};
