//
//  WindowsANE.cpp
//

// primary include //

#include "WindowsANE.h"

// system includes //

#include <stdlib.h>

// namespaces //

using namespace Platform;
using namespace Windows::UI::Popups;

// globals //

// function list
FRENamedFunction* g_pFunc = NULL;

// functions required by Flash //

// extension initializer
WINDOWSANE_API void WindowsANEExtensionInitializer(void**                 ppExtDataToSet,
												   FREContextInitializer* pCtxInitializerToSet,
												   FREContextFinalizer*   pCtxFinalizerToSet)
{
	// reset data
	(*ppExtDataToSet) = NULL;

	// set context initializer
	(*pCtxInitializerToSet) = &WindowsANEContextInitializer;

	// reset finalizer
	(*pCtxFinalizerToSet) = &WindowsANEContextFinalizer;
}

// context initializer
WINDOWSANE_API void WindowsANEContextInitializer(void*                    pExtData,
												 const uint8_t*           pCtxType,
												 FREContext               ctx,
												 uint32_t*                pNumFunctionsToSet,
												 const FRENamedFunction** pFunctionsToSet)
{
	// set number of functions
	(*pNumFunctionsToSet) = 4;

	// allocate memory for functions
	g_pFunc = g_pFunc ? g_pFunc : (FRENamedFunction*) malloc(sizeof(FRENamedFunction) * (*pNumFunctionsToSet));

	// add functions
	#define SET_LIB_FN_POINTER(n, str, fn) g_pFunc[n].name = (const uint8_t*) str; g_pFunc[n].functionData = NULL; g_pFunc[n].function = &fn

	SET_LIB_FN_POINTER(0, "addFullScreenButton", addFullScreenButton);
	SET_LIB_FN_POINTER(1, "messageBox",          messageBox);
	SET_LIB_FN_POINTER(2, "testANE",             testANE);
	SET_LIB_FN_POINTER(3, "toggleFullScreen",    toggleFullScreen);

	// set function pointer
	(*pFunctionsToSet) = g_pFunc;
}

// context finalizer
WINDOWSANE_API void WindowsANEContextFinalizer(void* pExtData)
{
	// free function list
	SAFE_FREE(g_pFunc);
}

// function implementations //

// addFullScreenButton() -- add button to title bar
WINDOWSANE_API FREObject addFullScreenButton(FREContext ctx,
											 void*      pFuncData,
											 uint32_t   argc,
											 FREObject  argv[])
{
	// add functionality

	// ok
	return(NULL);
}

// messageBox() -- display simple modal alert box
WINDOWSANE_API FREObject messageBox(FREContext ctx,
									void*      pFuncData,
									uint32_t   argc,
									FREObject  argv[])
{
	// text lengths
	uint32_t nCaptionLen;
	uint32_t nMessageLen;

	// text data
	const uint8_t* pCaption;
	const uint8_t* pMessage;

	// get objects
	FREGetObjectAsUTF8(argv[0], &nCaptionLen, &pCaption);
	FREGetObjectAsUTF8(argv[1], &nMessageLen, &pMessage);

	// allocate wide strings
	wchar_t* pCaptionW = nCaptionLen ? (wchar_t*) malloc(sizeof(wchar_t) * (nCaptionLen + 1)) : NULL;
	wchar_t* pMessageW = nMessageLen ? (wchar_t*) malloc(sizeof(wchar_t) * (nMessageLen + 1)) : NULL;

	// number of characters converted
	size_t nNumChar;

	// convert strings
	if(pCaptionW) mbstowcs_s(&nNumChar, pCaptionW, nCaptionLen, (const char*) pCaption, nCaptionLen);
	if(pMessageW) mbstowcs_s(&nNumChar, pMessageW, nMessageLen, (const char*) pMessage, nMessageLen);

	// create strings
	String^ caption = ref new String(pCaptionW);
	String^ message = ref new String(pMessageW);

	// create message box
	MessageDialog^ dialog = ref new MessageDialog(message,
												  caption);

	// show message box
	dialog->ShowAsync();

	// release wide strings
	if(pCaptionW) free(pCaptionW);
	if(pMessageW) free(pMessageW);

	// ok
	return(NULL);
}

// testANE() -- verify that the library is working correctly
WINDOWSANE_API FREObject testANE(FREContext ctx,
								 void*      pFuncData,
								 uint32_t   argc,
								 FREObject  argv[])
{
	// passed parameter
	int32_t nData = 0;

	// get first parameter
	FREGetObjectAsInt32(argv[0], &nData);

	// object to return
	FREObject pRet = NULL;

	// create object
	FRENewObjectFromInt32(nData, &pRet);

	// ok (errors will fall thru)
	return(pRet);
}

// toggleFullScreen() -- toggle full-screen mode
WINDOWSANE_API FREObject toggleFullScreen(FREContext ctx,
										  void*      pFuncData,
										  uint32_t   argc,
										  FREObject  argv[])
{
	// add functionality

	// ok
	return(NULL);
}

// eof //
