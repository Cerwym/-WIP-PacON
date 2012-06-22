#define WIN32_WIND

#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "OpenGLSys.h"
#include "timer.h"

HDC hDC;				// Private GDI Device Context
bool active=true;		// Window Active Flag
bool fullscreen=false;	// Fullscreen Flag

// Ugly stuff
long wWidth = 800;
long wHeight = 600;
long wBits = 32;

OpenGLSys *glRender = NULL;
CHiResTimer *g_hiResTimer = NULL;

void SetupPixelFormat(HDC hDC)
{
	int pixelFormat;

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1, // Version Number
		PFD_DRAW_TO_WINDOW | // Supports being in a window
		PFD_SUPPORT_OPENGL | // Supports OpenGL
		PFD_DOUBLEBUFFER, // Supports Double Buffering
		PFD_TYPE_RGBA, // Request RGBA Format
		32, // Sets the Colour Depth
		0, 0, 0, 0, 0, 0, // Ignore Colour Bits
		0, // No Alpha Buffer
		0, // Shift Bit Ignored
		0, // No Accumulation Buffer
		0, 0, 0, 0, // Accumulation Bits Ignored
		16, // 16bit Depth Buffer
		0, //  NO Stencil Buffer
		0, // No Auxiliary Buffer
		PFD_MAIN_PLANE, // Main Drawing Layer
		0, // Reserved
		0, 0, 0 // Layer Masks Ignored
	};

	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pixelFormat, &pfd);
}

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hDC;
	static HGLRC hRC;
	int height, width;
	switch (uMsg)
	{
		case WM_CREATE:
			// Makes more sense to init OpenGL when the Window creation is called through the API
			hDC = GetDC(hWnd);
			SetupPixelFormat(hDC);

			hRC = wglCreateContext(hDC);
			wglMakeCurrent(hDC, hRC);
			break;

		case WM_DESTROY:
		case WM_QUIT:
		case WM_CLOSE: // X has been pressed
			{
				// Deselect the renering context, then delete it
				wglMakeCurrent(hDC, NULL);
				wglDeleteContext(hRC);
				PostQuitMessage(0);
				break;
			}
		case WM_SIZE:
			{
				height = HIWORD(lParam);
				width = LOWORD(lParam);
				glRender->SetProjection(width, height); // Width -> Height
				break;
			}
		case WM_PAINT:              // Sent when another app or windows wants to draw on this
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_LBUTTONDOWN:
			break;
		case WM_RBUTTONDOWN:
			break;
		case WM_MOUSEMOVE:
			break;
		case WM_LBUTTONUP:
			break;
		case WM_RBUTTONUP:
			break;
		case WM_KEYUP:
			break;

		case WM_KEYDOWN:
			int fwKeys;
			LPARAM keyData;
			fwKeys = (int)wParam;    // virtual-key code
			keyData = lParam;          // key data

			switch(fwKeys)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			default:
				break;
			}

			break; // Out of KeyDOWN

		default:
			break;
	}
	// Pass all unhandled messages to DefWindowProc and let Windows deal with them
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc; // Window Class
	HWND hWnd; // Window Handle
	MSG msg; // Message structure
	DWORD dwExStyle; // Window Extended Style
	DWORD dwStyle; // Window Style
	RECT windowRect;

	glRender = new OpenGLSys;
	g_hiResTimer = new CHiResTimer;

	windowRect.left=(long)0;                        // Set Left Value To 0
	windowRect.right=(long)800; // Set Right Value To Requested Width
	windowRect.top=(long)0;                         // Set Top Value To 0
	windowRect.bottom=(long)600;   // Set Bottom Value To Requested Height

	// fill out the window class structure
	wc.cbSize          = sizeof(WNDCLASSEX);
	wc.style           = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc     = MainWindowProc;
	wc.cbClsExtra      = 0;
	wc.cbWndExtra      = 0;
	wc.hInstance       = hInstance;
	wc.hIcon           = LoadIcon(NULL, IDI_APPLICATION);  // default icon
	wc.hCursor         = LoadCursor(NULL, IDC_ARROW);      // default arrow
	wc.hbrBackground   = NULL;                             // don't need background
	wc.lpszMenuName    = NULL;                             // no menu
	wc.lpszClassName   = "POpenGLApp";
	wc.hIconSm         = LoadIcon(NULL, IDI_WINLOGO);      // windows logo small icon

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Failed to register the window class", "ERROR", MB_OK | MB_ICONINFORMATION);
		return false;
	}

	if (fullscreen)
	{
		/*
		 * Clears room to store the video settings
		 */
		DEVMODE dmScreenSettings; // Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings)); // Make sure the memory has been cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings); // Size of the struct
		dmScreenSettings.dmPelsHeight = wHeight;
		dmScreenSettings.dmPelsWidth = wWidth;
		dmScreenSettings.dmBitsPerPel = wBits; // Bits per pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try to set the selected mode
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If it fails, ask to quit or attempt to run in a window
			if (MessageBox(NULL, "Fullscreen is not supported by your video card\n Use Windows Mode Instead?", "",
				MB_YESNO | MB_ICONINFORMATION) == IDYES)
			{
				fullscreen = false;
			}
			else
			{
				MessageBox(NULL, "Closing the application", "ERROR", MB_OK | MB_ICONSTOP);
				return false;
			}
		}
	}

	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(false);
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}

	AdjustWindowRectEx(&windowRect, dwStyle, false, dwExStyle); // And adjust window to the REQUESTED size
	if (!(hWnd=CreateWindowEx(  dwExStyle,
		"POpenGLApp",							// Class Name
		"Pete's Summer Game",					// Window Title
		WS_CLIPSIBLINGS |						// Required Window Style
		WS_CLIPCHILDREN |						// Required Window Style
		dwStyle,								// Selected Window Style
		0, 0,									// Window Position
		windowRect.right-windowRect.left,		// Calculate Adjusted Window Width
		windowRect.bottom-windowRect.top,		// Calculate Adjusted Window Height
		NULL,									// No Parent Window
		NULL,									// No Menu
		hInstance,								// Instance
		NULL)))									// Don't Pass Anything To WM_CREATE
	{
		MessageBox(NULL, "Window Creation Error", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	// Create the window
	hDC = GetDC(hWnd);

	ShowWindow(hWnd, SW_SHOW); // Display
	UpdateWindow(hWnd); // Show

	glRender->Init();

	// Init the timer that will 'limit' the framerate and help the program deal with updates based on time rather than frames elapsed
	g_hiResTimer->Init();

	while (active)
	{
		glRender->Update(g_hiResTimer->GetElapsedSeconds(1));
		glRender->Render();
		SwapBuffers(hDC);

		while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage (&msg, NULL, 0, 0))
			{
				active = false;
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	delete glRender;
	delete g_hiResTimer;
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(true);
	}
	return (msg.wParam);
}