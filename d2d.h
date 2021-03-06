#pragma once

/****************************************************************************************
* Author:	Gilles Bellot
* Date:		05/08/2017 - Dortmund - Germany
*
* Desc:		Main class to use the Direct2D and DirectWrite components of DirectX.
*
****************************************************************************************/

// INCLUDES /////////////////////////////////////////////////////////////////////////////

// Windows and COM
#include <wrl/client.h>

// shared pointers
#include <shared_mutex>

// DirectX includes
#include <d2d1_2.h>
#include <dwrite_2.h>

#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "dwrite.lib")

// bell0bytes utilities
#include "expected.h"

// CLASSES //////////////////////////////////////////////////////////////////////////////
namespace core
{
	class DirectXApp;
}

namespace graphics
{
	class Direct2D
	{
	private:
		core::DirectXApp* dxApp;								// pointer to the main application class

		Microsoft::WRL::ComPtr<IDWriteFactory2> writeFactory;	// pointer to the DirectWrite factory
		Microsoft::WRL::ComPtr<ID2D1Factory2> factory;			// pointer to the Direct2D factory
		Microsoft::WRL::ComPtr<ID2D1Device1> dev;				// pointer to the Direct2D device
		Microsoft::WRL::ComPtr<ID2D1DeviceContext1> devCon;		// pointer to the device context
		
		util::Expected<void> createDevice();					// creates the device and its context
		util::Expected<void> createBitmapRenderTarget();		// creates the bitmap render target, set to be the same as the backbuffer already in use for Direct3D
		util::Expected<void> initializeTextFormats();			// initializes the different formats, for now, only a format to print FPS information will be created

	public:
		// constructors
		Direct2D(core::DirectXApp* dxApp);
		~Direct2D();

		// brushes
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> yellowBrush;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> whiteBrush;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> blackBrush;

		// text formats
		Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormatFPS;

		// text layouts
		Microsoft::WRL::ComPtr<IDWriteTextLayout> textLayoutFPS;

		util::Expected<void> printFPS();						// prints fps information to the screen

		friend class core::DirectXApp;
		friend class Direct3D;
	};
}