#ifndef _VFP2CFILE_H__
#define _VFP2CFILE_H__

#include <shlwapi.h>
#include <shlobj.h>
#include "vfp2chelpers.h"

class FileSearch
{
public:
	FileSearch() : m_Handle(INVALID_HANDLE_VALUE) {}
	~FileSearch() { if (m_Handle != INVALID_HANDLE_VALUE) FindClose(m_Handle); }

	bool FindFirst(char *pSearch);
	bool FindNext();
	bool IsFakeDir() const;
	const char* Filename() const;
	unsigned __int64 Filesize() const;

	WIN32_FIND_DATA File;

private:
	HANDLE m_Handle;
};

// custom defines and types for file operations
typedef struct _FILEPROGRESSPARAM {
	char pFileProgress[VFP2C_MAX_CALLBACKBUFFER];
	char pCallback[VFP2C_MAX_CALLBACKBUFFER];
	bool bCallback;
	bool bAborted;
	Value vRetVal;
} FILEPROGRESSPARAM, *LPFILEPROGRESSPARAM;

typedef struct _DIRECTORYINFO {
	int nNumberOfFiles;
	int nNumberOfSubDirs;
	double nDirSize;
	int nErrorNo;
} DIRECTORYINFO, *LPDIRECTORYINFO;

typedef struct _FILEATTRIBUTEINFO {
	DWORD nAttrib;
	DWORD nFlags;
	int nErrorNo;
} FILEATTRIBUTEINFO, *LPFILEATTRIBUTEINFO;

class BrowseCallback
{
public:
	BrowseCallback() { pBuffer.Size(VFP2C_MAX_CALLBACKBUFFER); }

	CStr pCallback;
	CStr pBuffer;
};

class OpenfileCallback
{
public:
	OpenfileCallback() { pBuffer.Size(VFP2C_MAX_CALLBACKBUFFER); vRetVal.ev_type = '0'; }

	int nErrorNo;
	Value vRetVal;
	CStr pCallback;
	CStr pBuffer;
};

#define ADIREX_DEST_ARRAY		0x01
#define ADIREX_DEST_CURSOR		0x02
#define ADIREX_DEST_CALLBACK	0x04
#define ADIREX_FILTER_ALL		0x08
#define ADIREX_FILTER_NONE		0x10
#define ADIREX_FILTER_EXACT		0x20
#define ADIREX_UTC_TIMES		0x40

#define FILE_OVERWRITE_ASK		0
#define FILE_OVERWRITE_YES		1
#define FILE_OVERWRITE_YESALL	2
#define FILE_OVERWRITE_NO		3
#define FILE_OVERWRITE_NOALL	4
#define FILE_OVERWRITE_IFNEWER	5
#define FILE_OVERWRITE_ABORT	6

#define CALLBACK_FILE_PROGRESS 1
#define CALLBACK_FILE_CHANGE 2
#define CALLBACK_FILE_OVERWRITE	3

#define MAX_OPENFILENAME_BUFFER 32768
#define MAX_ENVSTRING_BUFFER	4096

#define VFP2C_MAX_VOLUME_NAME			128
#define VFP2C_MAX_MOUNTPOINT_NAME		512
#define VFP2C_MAX_DEVICE_NAME			1024

#define VFP2C_FILE_LINE_BUFFER		32

#define MAXFILESEARCHPARAM (MAX_PATH-3)

// additional file attribute to filter "." & ".." directory's
#define FILE_ATTRIBUTE_FAKEDIRECTORY	0x80000000

#define SECURITY_DESCRIPTOR_LEN 256

// typedef's for runtime dynamic linking
typedef BOOL (_stdcall *PGETFILESIZEEX)(HANDLE,PLARGE_INTEGER); // GetFileSizeEx
typedef DWORD (_stdcall *PGETLONGPATHNAME)(LPSTR,LPSTR,DWORD); // GetLongPathName
typedef BOOL (_stdcall *PLOCKFILEEX)(HANDLE,DWORD,DWORD,DWORD,DWORD,LPOVERLAPPED); // LockFileEx
typedef BOOL (_stdcall *PUNLOCKFILEEX)(HANDLE,DWORD,DWORD,DWORD,LPOVERLAPPED); // UnlockFileEx

typedef BOOL (_stdcall *PGETFILEATTRIBUTESEX)(LPCTSTR,GET_FILEEX_INFO_LEVELS,LPVOID); // GetFileAttributesEx
typedef BOOL (_stdcall *PGETSPECIALFOLDER)(HWND,LPSTR,int,BOOL); // SHGetSpecialFolderPathA (shell32.dll)
typedef HRESULT (_stdcall *PSHILCREATEFROMPATH)(LPCWSTR,LPITEMIDLIST*,DWORD*); // SHILCreateFromPath (shell32.dll)
typedef LPITEMIDLIST (_stdcall *PSHILCREATEFROMPATHEX)(LPCWSTR); // undocumented func #162 on shell32.dll
#define SHILCREATEFROMPATHEXID 162

typedef BOOL (_stdcall *PGETKERNELOBJECTSECURITY)(HANDLE,SECURITY_INFORMATION,PSECURITY_DESCRIPTOR,DWORD,LPDWORD); // GetKernelObjectSecurity (advapi32.dll)
typedef BOOL (_stdcall *PGETSECURITYDESCRIPTOROWNER)(PSECURITY_DESCRIPTOR,PSID *,LPBOOL); // GetSecurityDescriptorOwner (advapi32.dll)
typedef BOOL (_stdcall *PLOOKUPACCOUNTSIDA)(LPCSTR,PSID,LPSTR,LPDWORD,LPSTR,LPDWORD,PSID_NAME_USE); // LookupAccountSidA (advapi32.dll)

typedef HANDLE (_stdcall *PFINDFIRSTVOLUME)(LPTSTR, DWORD); // FindFirstVolume
typedef BOOL (_stdcall *PFINDNEXTVOLUME)(HANDLE, LPTSTR, DWORD); // FindNextVolume
typedef BOOL (_stdcall *PFINDVOLUMECLOSE)(HANDLE); // FindVolumeClose
typedef HANDLE (_stdcall *FINDFIRSTVOLUMEMOUNTPOINT)(LPTSTR, LPTSTR, DWORD); // FindFirstVolumeMountPoint
typedef BOOL (_stdcall *PFINDNEXTVOLUMEMOUNTPOINT)(HANDLE, LPTSTR, DWORD); // FindNextVolumeMountPoint
typedef BOOL (_stdcall *PFINDVOLUMEMOUNTPOINTCLOSE)(HANDLE); // FindVolumeMountPointClose
typedef BOOL (_stdcall *PGETVOLUMENAMEFORVOLUMEMOUNTPOINT)(LPCTSTR, LPTSTR, DWORD); // GetVolumeNameForVolumeMountPoint
typedef DWORD (_stdcall *PQUERYDOSDEVICE)(LPCTSTR, LPTSTR, DWORD); // QueryDosDevice
typedef BOOL (_stdcall *PDEVICEIOCONTROL)(HANDLE, DWORD, LPVOID, DWORD, LPVOID, DWORD, LPDWORD, LPOVERLAPPED); // DeviceIoControl
typedef BOOL (_stdcall *PGETVOLUMEPATHNAME)(LPCTSTR, LPTSTR, DWORD); // GetVolumePathName

typedef bool (_stdcall *PADIREXFILTER)(DWORD, DWORD);

#ifdef __cplusplus
extern "C" {
#endif

// function prototypes of vfp2cfile.c
bool _stdcall VFP2C_Init_File();
void _stdcall VFP2C_Destroy_File();

void _fastcall ADirEx(ParamBlk *parm);
bool _stdcall AdirExFilter_All(DWORD nAttributes, DWORD nFilter);
bool _stdcall AdirExFilter_One(DWORD nAttributes, DWORD nFilter);
bool _stdcall AdirExFilter_None(DWORD nAttributes, DWORD nFilter);
bool _stdcall AdirExFilter_Exact(DWORD nAttributes, DWORD nFilter);

void _fastcall AFileAttributes(ParamBlk *parm);
void _fastcall AFileAttributesEx(ParamBlk *parm);
void _fastcall ADirectoryInfo(ParamBlk *parm);
#pragma warning(disable : 4290) // disable warning 4290 - VC++ doesn't implement throw ...
void _stdcall ADirectoryInfoSubRoutine(LPDIRECTORYINFO pDirInfo, CStr& pDirectory) throw(int);
void _fastcall GetFileTimes(ParamBlk *parm);
void _fastcall SetFileTimes(ParamBlk *parm);
void _fastcall GetFileSizeLib(ParamBlk *parm);
void _fastcall GetFileAttributesLib(ParamBlk *parm);
void _fastcall SetFileAttributesLib(ParamBlk *parm);
void _fastcall GetFileOwner(ParamBlk *parm);
void _fastcall GetLongPathNameLib(ParamBlk *parm);
void _fastcall GetShortPathNameLib(ParamBlk *parm);
void _fastcall GetOpenFileNameLib(ParamBlk *parm);
void _fastcall GetSaveFileNameLib(ParamBlk *parm);
UINT_PTR _stdcall GetFileNameCallback(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
void _fastcall ADriveInfo(ParamBlk *parm);
void _fastcall AVolumeInformation(ParamBlk *parm);
void _fastcall GetWindowsDirectoryLib(ParamBlk *parm);
void _fastcall GetSystemDirectoryLib(ParamBlk *parm);
void _fastcall ExpandEnvironmentStringsLib(ParamBlk *parm);
void _fastcall CopyFileExLib(ParamBlk *parm);
void _fastcall MoveFileExLib(ParamBlk *parm);
bool _stdcall CopyFileProgress(char *pSource, char *pDest, LPFILEPROGRESSPARAM pProgress) throw(int);
bool _stdcall MoveFileProgress(char *pSourceFile, char *pDestFile, DWORD nAttributes, bool bCrossVolume,
				  LPFILEPROGRESSPARAM pProgress) throw(int);
void _fastcall CompareFileTimes(ParamBlk *parm);
void _fastcall DeleteFileEx(ParamBlk *parm);
void _fastcall DeleteDirectory(ParamBlk *parm);

// extended VFP like file functions
void _fastcall FCreateEx(ParamBlk *parm);
void _fastcall FOpenEx(ParamBlk *parm);
void _fastcall FCloseEx(ParamBlk *parm);
void _fastcall FReadEx(ParamBlk *parm);
void _fastcall FWriteEx(ParamBlk *parm);
void _fastcall FGetsEx(ParamBlk *parm);
void _fastcall FPutsEx(ParamBlk *parm);
void _fastcall FSeekEx(ParamBlk *parm);
void _fastcall FEoFEx(ParamBlk *parm);
void _fastcall FChSizeEx(ParamBlk *parm);
void _fastcall FFlushEx(ParamBlk *parm);
void _fastcall FLockFile(ParamBlk *parm);
void _fastcall FUnlockFile(ParamBlk *parm);
void _fastcall FLockFileEx(ParamBlk *parm);
void _fastcall FUnlockFileEx(ParamBlk *parm);
void _fastcall AFHandlesEx(ParamBlk *parm);
void _stdcall MapFileAccessFlags(int nFileAttribs, int nAccess, int nShare, LPDWORD pAccess, LPDWORD pShare, LPDWORD pFlags) throw(int);

// shell api wrappers
void _fastcall SHSpecialFolder(ParamBlk *parm);
void _fastcall SHMoveFiles(ParamBlk *parm);
void _fastcall SHCopyFiles(ParamBlk *parm);
void _fastcall SHDeleteFiles(ParamBlk *parm);
void _fastcall SHRenameFiles(ParamBlk *parm);
void _fastcall SHBrowseFolder(ParamBlk *parm);
int _stdcall SHBrowseCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);

bool _stdcall PathIsSameVolume(const char *pPath1, const char *pPath2) throw(int);
bool _stdcall FileExists(const char *pFileName) throw(int);
void _stdcall CreateDirectoryExEx(const char *pDirectory) throw(int);
void _stdcall RemoveDirectoryEx(const char *pDirectory) throw(int);
void _stdcall DeleteDirectoryEx(const char *pDirectory) throw(int);
void _stdcall RemoveReadOnlyAttrib(const char *pFileName, DWORD nFileAttribs) throw(int);
void _stdcall DeleteFileExEx(const char *pFileName, DWORD nFileAttribs) throw(int);
int _stdcall CompareFileTimesEx(const char *pSourceFile, const char *pDestFile)  throw(int);

#ifdef __cplusplus
}
#endif // end of extern "C"

#endif // _VFP2CFILE_H__