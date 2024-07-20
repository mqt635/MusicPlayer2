﻿#pragma once
#include "SongInfo.h"
#include "FormatConvertDlg.h"
#include "RecentFolderAndPlaylist.h"

class CMusicPlayerCmdHelper
{
public:
    CMusicPlayerCmdHelper(CWnd* pOwner = nullptr);
    ~CMusicPlayerCmdHelper();

    void VeiwOnline(SongInfo& song);
    void FormatConvert(const std::vector<SongInfo>& songs);

    //执行添加到新建播放列表命令，成功返回true
    //get_song_list: 获取要添加的文件列表的回调函数，函数原型为 void Func(std::vector<SongInfo>&)
    //playlist_path: 接收新播放列表的路径
    //default_name：新播放列表的默认名称
    bool OnAddToNewPlaylist(std::function<void(std::vector<SongInfo>&)> get_song_list, std::wstring& playlist_path, const std::wstring& default_name = L"");

    bool OnAddToPlaylistCommand(std::function<void(std::vector<SongInfo>&)> get_song_list, DWORD command);

    //从磁盘删除歌曲
    bool DeleteSongsFromDisk(const std::vector<SongInfo>& files);

    //查找可能匹配的所有歌词文件
    void SearchLyricFiles(const wstring& lyric_name, const wstring& cur_dir, std::vector<std::wstring>& result, bool fuzzy_match);
    //查找最佳匹配的歌词文件并返回路径
    std::wstring SearchLyricFile(const SongInfo& song, bool fuzzy_match);

    //查找匹配的外部专辑封面
    std::wstring SearchAlbumCover(const SongInfo& song);

    //响应歌曲分级命令
    //（分级数据会写入到音频文件和song_data.dat文件中。如果文件写入失败，则返回false，否则返回true。
    //但是如果此文件格式不支持将分级，则只会写入到song_data.dat文件中，函数仍然返回true）
    bool OnRating(const SongInfo& song, DWORD command);

    //更新媒体库，返回新增的歌曲数。（此函数执行时间可能会较长，应该在后台线程中执行）
    static int UpdateMediaLib();

    //清理数据，函数对象fun_condition用来判断文件是否要被清理，如果是则返回true
    static int CleanUpSongData(std::function<bool(const SongInfo&)> fun_condition = [&](const SongInfo& song) { return !CCommon::FileExist(song.file_path); });

    // 清除最近播放文件夹中的无效条目
    static int CleanUpRecentFolders();

    enum eMediaLibTab
    {
        ML_FOLDER = 0,
        ML_PLAYLIST = 1,
        ML_ARTIST,
        ML_ALBUM,
        ML_GENRE,
        ML_YEAR,
        ML_FILE_TYPE,
        ML_BITRATE,
        ML_RATING
    };

    std::wstring GetMediaLibTabName(eMediaLibTab tab);

    //显示媒体库对话框
    //cur_tab: 打开对话框后要切换的标签，如果为-1，则保持上次打开的标签
    //tab_force_show: 要强制显示的标签，使用int中的各个bit表示要显示的标签，每个bit参见枚举 MediaLibDisplayItem 的声明
    void ShowMediaLib(int cur_tab = -1, int tab_force_show = 0);

    //刷新媒体库指定标签页，0刷新文件夹，1刷新播放列表
    static void RefreshMediaTabData(eMediaLibTab tab);

    //在媒体库中查看
    void OnViewInMediaLib(eMediaLibTab tab, const std::wstring name);

    //查看艺术家
    void OnViewArtist(const SongInfo& song_info);

    //查看唱片集
    void OnViewAlbum(const SongInfo& song_info);

    //修正播放列表中的错误的路径
    int FixPlaylistPathError(const std::wstring& path);

    void OnFolderSelected(const PathInfo& path_info, bool play = false);

    void OnPlaylistSelected(const PlaylistInfo& playlist_info, bool play = false);

    void OnMediaLibItemSelected(CMediaClassifier::ClassificationType type, const std::wstring& name, bool play = false);

    //响应播放列表上方下拉列表项
    void OnRecentItemSelected(const CRecentFolderAndPlaylist::Item* item);

protected:
    void AddToPlaylist(const std::vector<SongInfo>& songs, const std::wstring& playlist_path);

private:
    CWnd* GetOwner();

private:
    CWnd* m_pOwner{};
};
