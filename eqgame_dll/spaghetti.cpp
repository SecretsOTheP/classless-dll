#include "spaghetti.h"
//#include "MQ2Main.h"
//#include <intrin.h>
//#include <IPTypes.h>
//#include <iphlpapi.h>
//#include <iostream>
//#include <comdef.h>
//#include <Wbemidl.h>
//#include <d3d9.h>
//#include <vector>
//#include <string>
//
//#pragma comment(lib, "wbemuuid.lib")
//
//#pragma comment(lib, "Iphlpapi.lib")
//
//#pragma comment(lib, "d3d9.lib")
//
//#define SAFE_RELEASE(D) if(D) { D->Release(); }
//
//CHWInfo::CHWInfo()
//{
//	memset(this, 0, sizeof(*this));
//	bInit = false;
//}
//
//void CHWInfo::Grab()
//{
//	GetMACAddress();
//	GetCPUInfo();
//	GetCPUFreq();
//	GetMemoryInfo();
//	GetDesktopResolution();
//	GetD3DInfo();
//	GetOSInfo();
//	if (!bInit)
//	{
//	
//		CoInitialize(0);
//		CoInitializeSecurity(
//			NULL,
//			-1,                          // COM authentication
//			NULL,                        // Authentication services
//			NULL,                        // Reserved
//			RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
//			RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
//			NULL,                        // Authentication info
//			EOAC_NONE,                   // Additional capabilities 
//			NULL                         // Reserved
//		);
//		bInit = true;
//	}
//	HDDSerial = queryAndPrintResult(L"SELECT SerialNumber FROM Win32_PhysicalMedia", L"SerialNumber");
//}
//
//enum class WmiQueryError {
//	None,
//	BadQueryFailure,
//	PropertyExtractionFailure,
//	ComInitializationFailure,
//	SecurityInitializationFailure,
//	IWbemLocatorFailure,
//	IWbemServiceConnectionFailure,
//	BlanketProxySetFailure,
//};
//
//struct WmiQueryResult
//{
//	std::vector<std::wstring> ResultList;
//	WmiQueryError Error = WmiQueryError::None;
//	std::wstring ErrorDescription;
//};
//
//WmiQueryResult getWmiQueryResult(std::wstring wmiQuery, std::wstring propNameOfResultObject, bool allowEmptyItems = false) {
//
//	WmiQueryResult retVal;
//	retVal.Error = WmiQueryError::None;
//	retVal.ErrorDescription = L"";
//
//	HRESULT hres;
//
//
//	IWbemLocator *pLoc = NULL;
//	IWbemServices *pSvc = NULL;
//	IEnumWbemClassObject* pEnumerator = NULL;
//	IWbemClassObject *pclsObj = NULL;
//	VARIANT vtProp;
//
//
//	// Step 1: --------------------------------------------------
//	// Initialize COM. ------------------------------------------
//	hres = CoInitialize(0);
//	// Step 3: ---------------------------------------------------
//	// Obtain the initial locator to WMI -------------------------
//	pLoc = NULL;
//
//	hres = CoCreateInstance(
//		CLSID_WbemLocator,
//		0,
//		CLSCTX_INPROC_SERVER,
//		IID_IWbemLocator, (LPVOID *)&pLoc);
//
//	if (FAILED(hres))
//	{
//		retVal.Error = WmiQueryError::IWbemLocatorFailure;
//	}
//	else
//	{
//		// Step 4: -----------------------------------------------------
//		// Connect to WMI through the IWbemLocator::ConnectServer method
//
//		pSvc = NULL;
//
//		// Connect to the root\cimv2 namespace with
//		// the current user and obtain pointer pSvc
//		// to make IWbemServices calls.
//		hres = pLoc->ConnectServer(
//			_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
//			NULL,                    // User name. NULL = current user
//			NULL,                    // User password. NULL = current
//			0,                       // Locale. NULL indicates current
//			NULL,                    // Security flags.
//			0,                       // Authority (for example, Kerberos)
//			0,                       // Context object 
//			&pSvc                    // pointer to IWbemServices proxy
//		);
//
//		// Connected to ROOT\\CIMV2 WMI namespace
//
//		if (FAILED(hres))
//		{
//			retVal.Error = WmiQueryError::IWbemServiceConnectionFailure;
//		}
//		else
//		{
//			// Step 5: --------------------------------------------------
//			// Set security levels on the proxy -------------------------
//
//			hres = CoSetProxyBlanket(
//				pSvc,                        // Indicates the proxy to set
//				RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
//				RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
//				NULL,                        // Server principal name 
//				RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
//				RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
//				NULL,                        // client identity
//				EOAC_NONE                    // proxy capabilities 
//			);
//
//			if (FAILED(hres))
//			{
//				retVal.Error = WmiQueryError::BlanketProxySetFailure;
//			}
//			else
//			{
//				// Step 6: --------------------------------------------------
//				// Use the IWbemServices pointer to make requests of WMI ----
//
//				// For example, get the name of the operating system
//				pEnumerator = NULL;
//				hres = pSvc->ExecQuery(
//					bstr_t("WQL"),
//					bstr_t(wmiQuery.c_str()),
//					WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
//					NULL,
//					&pEnumerator);
//
//				if (FAILED(hres))
//				{
//					retVal.Error = WmiQueryError::BadQueryFailure;
//				}
//				else
//				{
//					// Step 7: -------------------------------------------------
//					// Get the data from the query in step 6 -------------------
//
//					pclsObj = NULL;
//					ULONG uReturn = 0;
//
//					while (pEnumerator)
//					{
//						HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
//							&pclsObj, &uReturn);
//
//						if (0 == uReturn)
//						{
//							break;
//						}
//
//						// VARIANT vtProp;
//
//						// Get the value of desired property
//						hr = pclsObj->Get(propNameOfResultObject.c_str(), 0, &vtProp, 0, 0);
//						if (S_OK != hr) {
//							retVal.Error = WmiQueryError::PropertyExtractionFailure;
//						}
//						else {
//							BSTR val = vtProp.bstrVal;
//
//							// Sometimes val might be NULL even when result is S_OK
//							// Convert NULL to empty string (otherwise "std::wstring(val)" would throw exception)
//							if (NULL == val) {
//								if (allowEmptyItems) {
//									retVal.ResultList.push_back(std::wstring(L""));
//								}
//							}
//							else {
//								retVal.ResultList.push_back(std::wstring(val));
//							}
//						}
//					}
//				}
//			}
//		}
//	}
//
//	// Cleanup
//	// ========
//
//	VariantClear(&vtProp);
//	if (pclsObj)
//		pclsObj->Release();
//
//	if (pSvc)
//		pSvc->Release();
//
//	if (pLoc)
//		pLoc->Release();
//
//	if (pEnumerator)
//		pEnumerator->Release();
//
//	return retVal;
//}
//
//std::wstring queryAndPrintResult(std::wstring query, std::wstring propNameOfResultObject)
//{
//	WmiQueryResult res;
//	res = getWmiQueryResult(query, propNameOfResultObject);
//
//	if (res.Error != WmiQueryError::None) {
//		return std::wstring(L"None"); // Exitting function
//	}
//
//	for (const auto& item : res.ResultList) {
//		return item.c_str();
//	}
//}
//
//void CHWInfo::GetMACAddress()
//{
//	/*IP_ADAPTER_INFO AdapterInfo[16];
//	DWORD dwBufLen = sizeof(AdapterInfo);
//	DWORD dwStatus = GetAdaptersInfo(AdapterInfo, &dwBufLen);
//	if (dwStatus != ERROR_SUCCESS)
//		return;
//
//	memcpy(&macAddress, AdapterInfo[0].Address, sizeof(macAddress));
//
//	MacCRC = crc32buf((char*)&macAddress, 8);*/
//}
//
//static uint32_t crc_32_tab[] = { /* CRC polynomial 0xedb88320 */
//0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
//0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
//0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
//0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
//0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
//0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
//0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
//0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
//0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
//0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
//0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
//0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
//0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
//0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
//0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
//0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
//0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
//0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
//0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
//0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
//0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
//0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
//0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
//0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
//0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
//0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
//0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
//0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
//0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
//0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
//0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
//0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
//0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
//0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
//0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
//0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
//0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
//0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
//0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
//0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
//0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
//0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
//0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
//};
//
//DWORD updateCRC32(unsigned char ch, DWORD crc)
//{
//	return UPDC32(ch, crc);
//}
//
//DWORD crc32buf(char *buf, size_t len)
//{
//	register DWORD oldcrc32;
//
//	oldcrc32 = 0xFFFFFFFF;
//
//	for (; len; --len, ++buf)
//	{
//		oldcrc32 = UPDC32(*buf, oldcrc32);
//	}
//
//	return ~oldcrc32;
//
//}
//
//void CHWInfo::GetCPUInfo()
//{
//	int CPUInfo[4] = { -1 };
//
//	// __cpuid with an InfoType argument of 0 returns the number of
//	// valid Ids in CPUInfo[0] and the CPU identification string
//	__cpuid(CPUInfo, 0);
//	memset(CPUString, 0, sizeof(CPUString));
//	*((DWORD*)CPUString) = CPUInfo[1];
//	*((DWORD*)(CPUString + 4)) = CPUInfo[3];
//	*((DWORD*)(CPUString + 8)) = CPUInfo[2];
//
//	// get CPU feature information.
//	__cpuid(CPUFeatures, 1);
//
//	CPUBrandCRC = crc32buf((char*)&CPUFeatures, sizeof(int) * 4);
//
//	// Calling __cpuid with 0x80000000 as the InfoType argument
//	// gets the number of valid extended IDs.
//	memset(CPUBrandString, 0, sizeof(CPUBrandString));
//
//	__cpuid(CPUInfo, 0x80000000);
//	int nExIds = CPUInfo[0];
//
//	// Get the information associated with each extended ID.
//	for (int i = 0x80000000; i <= nExIds; ++i)
//	{
//		__cpuid(CPUInfo, i);
//
//		if (i == 0x80000002)
//			memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
//		else if (i == 0x80000003)
//			memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
//		else if (i == 0x80000004)
//			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
//	}
//
//	CPUBrandCRC = crc32buf((char*)&CPUBrandString, 64);
//
//	// check if brandsting is invalid
//	if (strlen(CPUBrandString) >= sizeof(CPUBrandString))
//		CPUBrandString[0] = 0;
//
//	return;
//}
//
//void CHWInfo::GetCPUFreq()
//{
//	// open the key where the proc speed is stored
//	HKEY hKey;
//	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
//		0, KEY_READ, &hKey) != ERROR_SUCCESS)
//	{
//		return;
//	}
//
//	// query the key
//	DWORD size = sizeof(CPUFreq);
//	RegQueryValueEx(hKey, "~MHz", NULL, NULL, (LPBYTE)&CPUFreq, &size);
//
//	CPUFreqCRC = crc32buf((char*)&CPUFreq, 4);
//
//}
//
//void CHWInfo::GetMemoryInfo()
//{
//	MEMORYSTATUSEX stat;
//	stat.dwLength = sizeof(stat);
//	GlobalMemoryStatusEx(&stat);
//
//	TotalMemory = (DWORD)(stat.ullTotalPhys / 1024);
//
//	return;
//}
//
//void CHWInfo::GetDesktopResolution()
//{
//	HDC disp_dc = CreateIC("DISPLAY", NULL, NULL, NULL);
//	DisplayW = GetDeviceCaps(disp_dc, HORZRES);
//	DisplayH = GetDeviceCaps(disp_dc, VERTRES);
//	DeleteDC(disp_dc);
//}
//
//
//
//void CHWInfo::GetD3DInfo()
//{
//	IDirect3D9* pd3d = Direct3DCreate9(D3D_SDK_VERSION);
//	if (pd3d == NULL) {
//		return;
//	}
//
//	D3DADAPTER_IDENTIFIER9 ident;
//	if (D3D_OK == pd3d->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &ident))
//	{
//		gfxDeviceId = ident.DeviceId;
//		gfxVendorId = ident.VendorId;
//		strncpy(gfxDescription, ident.Description, 256);
//	}
//
//	SAFE_RELEASE(pd3d);
//}
//
//void CHWInfo::GetOSInfo()
//{
//	OSVERSIONINFO osvi = { 0 };
//	osvi.dwOSVersionInfoSize = sizeof(osvi);
//	GetVersionEx(&osvi);
//
//	sprintf(OSVersion, "%d.%d.%d", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
//}
