#pragma once

#include <string>
#include <exception>
#include <windows.h>

namespace Debug
{
	class W32Console
	{
	public:
		static W32Console &Get()
		{
			if (mInstance)
				return (*mInstance);
			else
				throw(std::exception("Instance of console not created."));
		}

		static void Create(const int width, const int height, const int bgColour = 0);
		static void Destroy();

		// Print text to console, can specify where in console to print
		void Print(const std::string& text);
		void Print(const int x, const int y, const std::string& text);
		// Move cursor relatively and absolutely
		void MoveCursorTo(const int x, const int y);
		void MoveCursorBy(const int x_inc, const int y_inc, bool wrap = false);
		// Clear screen or a single line
		void Clear(const int bg_colour = -1);
		void ClearLine(const int line_no, const std::string& clear_char = "");
		// Set colour for future print/clear commands
		void SetTextColour(const int colour);
		void SetBackgroundColour(const int colour);
		// Switch colour of buffer text
		void SwitchTextColour(const int colour);
		void SwitchBackgroundColour(const int colour);

		// Colour constants for SetColour methods
		static const int BLACK = 0;
		static const int DARK_BLUE = 1;
		static const int DARK_GREEN = 2;
		static const int DARK_CYAN = 3;
		static const int DARK_RED = 4;
		static const int DARK_PURPLE = 5;
		static const int DARK_YELLOW = 6;
		static const int DARK_WHITE = 7;
		static const int GREY = 8;
		static const int BLUE = 9;
		static const int GREEN = 10;
		static const int CYAN = 11;
		static const int RED = 12;
		static const int PURPLE = 13;
		static const int YELLOW = 14;
		static const int WHITE = 15;

	private:

		W32Console(const int width, const int height, const int bgColour);
		W32Console(const W32Console&);
		~W32Console();


		static W32Console* mInstance;
		HANDLE	mConsoleHandle;
		CONSOLE_SCREEN_BUFFER_INFO mConsoleInfo;
		CONSOLE_CURSOR_INFO mCursor;

		void RedirectSTDIO();

		short mForegroundColour;
		short mBackgroundColour;
	};
}

