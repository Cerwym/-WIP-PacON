#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <iostream>

using namespace std;

HGLRC hRC=NULL;			// Permanent Rendering Context
HDC hDC=NULL;			// Private GDI Device Context
HWND hWnd=NULL;			// Holds the Window Handle
HINSTANCE hInstance;	// Holds the Instance of the Application

bool keys[256];			// Keyboard Information
bool active=true;		// Window Active Flag
bool fullscreen=false;	// Fullscreen Flag

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

GLvoid ResizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0) // Prevents divide by zero
	{
		height = 1; // by making height NEVER be zero
	}

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // Reset the projection matrix

	// Calculate aspect ratio of the screen
	gluPerspective(45.0f, (GLfloat) width / (GLfloat) height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW); // Selects the modelview matrix
	glLoadIdentity(); // Resets the modelview matrix
}

int InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Black
	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enabled Depth Testing
	glDepthFunc(GL_LEQUAL); // Lessens Z-Depth Fighting
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return true;
}

int DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen AND depth, it's a flag (fancy eh?)
	glLoadIdentity(); // Reset modelview matrix
	return true;
}

GLvoid KillGLWindow(GLvoid)
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0); // Switch to desktop
		ShowCursor(true); // And enable the pointer if it was disabled
	}

	/*
	 * A rendering context is a port through which all OpenGl commands pass, every thread that makes a call MUST have a
	 * current rendering context. Rendering contexts link OpenGL to the Windows window system.
	 */
	if (hRC)
	{
		if (!wglMakeCurrent(NULL, NULL)) // Can we release the Device context AND Rendering context?
		{
			MessageBox(NULL, "Release of Device and Rendering context failed", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC)) // Aaand can we delete the RC?
		{
			MessageBox(NULL, "Release of Rendering Context Failed", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL; // Set the RC to null
	}

	if (hDC && !ReleaseDC(hWnd, hDC))
	{
		MessageBox(NULL, "Release of Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}

	if (hWnd && !DestroyWindow(hWnd)) // Can we destroy the window?
	{
		MessageBox(NULL, "Could not release the Window", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}

	if (!UnregisterClass("POpenGLApp", hInstance)) // Can we unregister the window class - this allows us to close and re-open the window without error
	{
		MessageBox(NULL, "Could not unregister window class", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}

bool CreateGLWindow(char* title, int width, int height, int bits, bool fullscrenflag)
{
	GLuint PixelFormat; // Holds the results after searching for a match
	WNDCLASS wc; // Windows class structure
	DWORD dwExStyle; // Window Extended Style;
	DWORD dwStyle; // Window Style

	/*
	 * Grab the upper left and lower right values of a rectangle so we can
	 * adjust the window to draw on by the resolution we want
	 */
	RECT WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long) width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long) height;

	fullscreen = fullscrenflag;

	// Grab the instance for the window and delcare the (windows) window class
	hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Redraw on Move and own device context
	wc.lpfnWndProc = (WNDPROC) WndProc; // Handles messages
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Default Windows Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Load the default arrow pointer
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL; // No menu
	wc.lpszClassName = "POpenGLApp";

	if (!RegisterClass(&wc))
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
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmBitsPerPel = bits; // Bits per pixel
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

	AdjustWindowRectEx(&WindowRect, dwStyle, false, dwExStyle); // Adjust the window to the requested size

	if (!(hWnd=CreateWindowEx(  dwExStyle,
		"POpenGLApp",               // Class Name
		title,									// Window Title
		WS_CLIPSIBLINGS |						// Required Window Style
		WS_CLIPCHILDREN |						// Required Window Style
		dwStyle,								// Selected Window Style
		0, 0,									// Window Position
		WindowRect.right-WindowRect.left,		// Calculate Adjusted Window Width
		WindowRect.bottom-WindowRect.top,		// Calculate Adjusted Window Height
		NULL,									// No Parent Window
		NULL,									// No Menu
		hInstance,								// Instance
		NULL)))									// Don't Pass Anything To WM_CREATE
	{
		KillGLWindow();
		MessageBox(NULL, "Window Creation Error", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1, // Version Number
		PFD_DRAW_TO_WINDOW | // Supports being in a window
		PFD_SUPPORT_OPENGL | // Supports OpenGL
		PFD_DOUBLEBUFFER, // Supports Double Buffering
		PFD_TYPE_RGBA, // Request RGBA Format
		bits, // Sets the Colour Depth
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

	if (! (hDC=GetDC(hWnd)))
	{
		KillGLWindow();
		MessageBox(NULL, "Cant create an OpenGL Device Context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't find a suitable PixelFormat", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if (! SetPixelFormat(hDC,PixelFormat, &pfd))
	{
		KillGLWindow();
		MessageBox(NULL, "Error Setting the pixel format", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if (! (hRC = wglCreateContext(hDC)))
	{
		KillGLWindow();
		MessageBox(NULL, "Create create a GL rendering context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if(!wglMakeCurrent(hDC, hRC))
	{
		KillGLWindow();
		MessageBox(NULL, "Can't Activate the GL rendering context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	// So, if we've got to this point in the func, create the window
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd); // Set KEYBOARD focus to the window
	ResizeGLScene(width, height);

	if (!InitGL())
	{
		KillGLWindow();
		MessageBox(NULL, "Initialization Failed", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	return true; // Ta-da success!
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_ACTIVATE: // Windows Active Message
			{
				if(!HIWORD(wParam)) // If this window is NOT minimized
				{
					active = true; // It's Active!
				}
				else
				{
					active = false; // Awww crap it's not anymore
				}

				return 0; // Loop
			}
		case WM_SYSCOMMAND: // Intercept System Commands, like screen saver, power saver etc
			{
				switch(wParam)
				{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0; // Prevent
				}
				break;
			}
		case WM_CLOSE: // X has been pressed
			{
				PostQuitMessage(0);
				return 0;
			}
		case WM_KEYDOWN:
			{
				keys[wParam] = true;
				return 0;
			}
		case WM_KEYUP:
			{
				keys[wParam] = false;
				return 0;
			}
		case WM_SIZE:
			{
				ResizeGLScene(LOWORD(lParam), HIWORD(lParam)); // Width -> Height
				return 0;
			}
	}
	// Pass all unhandled messages to DefWindowProc and let Windows deal with them
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg; // Message structure
	bool done = false;

	/*
	if (MessageBox(NULL, "Run in Fullscreen?", "Screen Options", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		fullscreen = false;
	}
	*/

	if(!CreateGLWindow("Pete's OpenGL Test APP", 800, 600, 16, fullscreen))
	{
		return 0; // Quit because creating the window failed
	}

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // If a message is waiting
		{
			if (msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				// Translate and Dispatch the message
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else // No mesages are being sent
		{
			if (active)
			{
				if (keys[VK_ESCAPE])
				{
					done = true;
				}
				else // Run the scene
				{
					DrawGLScene();
					SwapBuffers(hDC); // Double Buffering
					cout << "Hello";
				}
			}

			if (keys[VK_F1])
			{
				keys[VK_F1] = false;
				KillGLWindow();
				fullscreen != fullscreen;
				if (!CreateGLWindow("Pete's OpenGL Test App", 800, 600, 16, fullscreen))
				{
					return 0;
				}
			}
		}
	}

	// When out of the loop
	KillGLWindow();
	return (msg.wParam);
}