// ====================================================================================================
// Includes
// ====================================================================================================
#include "Updater.h"
#include <memory>
#pragma comment(lib,"urlmon.lib")
#pragma comment(lib,"Wininet.lib")
#include <wininet.h>

class CCallback : public IBindStatusCallback
{
public:
	CCallback()
	{
		//
	}
	~CCallback()
	{
		//
	}
	DownloadThreadInfo* m_pThreadInfo;

	STDMETHOD(OnStartBinding)(
		/* [in] */ DWORD dwReserved,
		/* [in] */ IBinding __RPC_FAR *pib)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetPriority)(
		/* [out] */ LONG __RPC_FAR *pnPriority)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(OnLowResource)(
		/* [in] */ DWORD reserved)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(OnProgress)(
		/* [in] */ ULONG ulProgress,
		/* [in] */ ULONG ulProgressMax,
		/* [in] */ ULONG ulStatusCode,
		/* [in] */ LPCWSTR wszStatusText)
	{
		m_pThreadInfo->size_downloaded = ulProgress;
		m_pThreadInfo->size_total = ulProgressMax;

		if (ulProgressMax > 0)
		{
			m_pThreadInfo->progress = (float)((double)ulProgress / (double)ulProgressMax) * 100.0f;
		}
		return 0;
	}

	STDMETHOD(OnStopBinding)(
		/* [in] */ HRESULT hresult,
		/* [unique][in] */ LPCWSTR szError)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetBindInfo)(
		/* [out] */ DWORD __RPC_FAR *grfBINDF,
		/* [unique][out][in] */ BINDINFO __RPC_FAR *pbindinfo)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(OnDataAvailable)(
		/* [in] */ DWORD grfBSCF,
		/* [in] */ DWORD dwSize,
		/* [in] */ FORMATETC __RPC_FAR *pformatetc,
		/* [in] */ STGMEDIUM __RPC_FAR *pstgmed)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(OnObjectAvailable)(
		/* [in] */ REFIID riid,
		/* [iid_is][in] */ IUnknown __RPC_FAR *punk)
	{
		return E_NOTIMPL;
	}

	STDMETHOD_(ULONG, AddRef)()
	{
		return 0;
	}

	STDMETHOD_(ULONG, Release)()
	{
		return 0;
	}

	STDMETHOD(QueryInterface)(
		/* [in] */ REFIID riid,
		/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject)
	{
		return E_NOTIMPL;
	}
};

// ====================================================================================================
// Download Thread
// ====================================================================================================
DWORD WINAPI DownloadThread(void* _pThreadInfo)
{
	DownloadThreadInfo* pThreadInfo = (DownloadThreadInfo*)_pThreadInfo;

	CCallback* sc = new CCallback();
	sc->m_pThreadInfo = pThreadInfo;
	DeleteUrlCacheEntry(pThreadInfo->path.c_str());
	HRESULT hResult = URLDownloadToFile(NULL, pThreadInfo->path.c_str(), pThreadInfo->saveas.c_str(), NULL, (IBindStatusCallback*) sc);

	pThreadInfo->bSuccess = SUCCEEDED(hResult);
	pThreadInfo->bFinished = true;
	return NULL;
}

// ====================================================================================================
// Download File
// ====================================================================================================
DownloadThreadInfo* DownloadFile(std::string filepath, std::string saveas)
{
	DownloadThreadInfo* pThreadInfo = new DownloadThreadInfo();
	pThreadInfo->bFinished = false;
	pThreadInfo->path = filepath;
	pThreadInfo->bSuccess = false;
	pThreadInfo->progress = 0.0f;
	pThreadInfo->size_downloaded = 0;
	pThreadInfo->size_total = 0;
	pThreadInfo->saveas = saveas;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)DownloadThread, (void*)pThreadInfo, NULL, NULL);
	return pThreadInfo;
}

// ====================================================================================================
// File Revision
// ====================================================================================================
int GetFileRevision(std::string val)
{
	try
	{
		int filerev_i = std::stoi(val);
		return filerev_i;
	}
	catch (...)
	{
		return -1;
	}
}