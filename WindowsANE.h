//
//  WindowsANE.h
//

#ifndef WindowsANE_WindowsANE_h
#define WindowsANE_WindowsANE_h

// windows includes //

#include <WinSDKVer.h> // load flags
	#define NTDDI_VERSION NTDDI_WINBLUE
	#define _WIN32_WINNT  _WIN32_WINNT_WINBLUE
	#define WINVER        _WIN32_WINNT_WINBLUE
#include <sdkddkver.h> // apply flags

#define WIN32_LEAN_AND_MEAN // keep it light

#include <Windows.h> // basic Windows components

// Flash includes //

#include "FlashRuntimeExtensions.h"

// function type definition //

#ifdef __cplusplus
	#define WINDOWSANE_API extern "C" __declspec(dllexport)
#else
	#define WINDOWSANE_API __declspec(dllexport)
#endif // __cplusplus

// macros //

#define DEBUG_MSG(msg) { MessageDialog^ dialog = ref new MessageDialog(msg); dialog->ShowAsync(); }

#define SAFE_FREE(mem) if(mem) { free((void*) mem); mem = NULL; }

// library function prototypes //

#define DECL_LIB_FN_PROTOTYPE(fn) WINDOWSANE_API FREObject fn (FREContext, void*, uint32_t, FREObject*)

WINDOWSANE_API void WindowsANEExtensionInitializer(void**, FREContextInitializer*, FREContextFinalizer*);
WINDOWSANE_API void WindowsANEContextInitializer(void*, const uint8_t*, FREContext, uint32_t*, const FRENamedFunction**);
WINDOWSANE_API void WindowsANEContextFinalizer(void*);

DECL_LIB_FN_PROTOTYPE(addFullScreenButton);
DECL_LIB_FN_PROTOTYPE(messageBox);
DECL_LIB_FN_PROTOTYPE(testANE);
DECL_LIB_FN_PROTOTYPE(toggleFullScreen);

#endif // WindowsANE_WindowsANE_h
