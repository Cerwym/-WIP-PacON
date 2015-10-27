#include "W32Console.h"

#include <conio.h>
#include <limits>
#include <cassert>
#include <iostream>

using namespace std;


namespace Debug
{

	W32Console* W32Console::mInstance = nullptr;


	W32Console::W32Console(const int width, const int height, const int bgColour)
		: mConsoleHandle(nullptr), mForegroundColour(15), mBackgroundColour(0)
	{
		assert(bgColour >= 0 && bgColour < 16);

		AllocConsole();
		RedirectSTDIO();
		mConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		mCursor.dwSize = 100;
		mCursor.bVisible = true;

		COORD console_size = { width, height };
		SetConsoleScreenBufferSize(mConsoleHandle, console_size);
		SetConsoleCursorInfo(mConsoleHandle, &mCursor);
		GetConsoleScreenBufferInfo(mConsoleHandle, &mConsoleInfo);

		SetBackgroundColour(bgColour);
		SetTextColour(mForegroundColour);
		Clear();
	}

	W32Console::~W32Console()
	{
		fclose(stdin);
		fclose(stdout);
		fclose(stderr);
		FreeConsole();
	}

	void W32Console::Create(const int width, const int height, const int bg_colour)
	{
		if (mInstance) { throw std::exception("Tried to create multiple console instances."); }

		mInstance = new W32Console(width, height, bg_colour);
	}

	void W32Console::Destroy()
	{
		if (!mInstance) { throw std::exception("Tried to destroy non-existent console instance"); }

		delete mInstance;
		mInstance = nullptr;
	}



	void W32Console::Print(const int x, const int y, const std::string& text)
	{
		MoveCursorTo(x, y);
		cout << text;
	}

	void W32Console::Print(const std::string& text)
	{
		cout << text << std::endl;
	}

	void W32Console::MoveCursorTo(const int x, const int y)
	{

		//assert(x >= 0 && x < mConsoleInfo.dwSize.X);
		//assert(y >= 0 && y < mConsoleInfo.dwSize.Y);

		// Windows takes a short for cursor positioning
		// The asserts above ensure the cast will be valid
		short shortx = static_cast<short>(x);
		short shorty = static_cast<short>(y);
		COORD position = { shortx, shorty };
		SetConsoleCursorPosition(mConsoleHandle, position);
	}

	void W32Console::MoveCursorBy(const int x_inc, const int y_inc, bool wrap)
	{
		GetConsoleScreenBufferInfo(mConsoleHandle, &mConsoleInfo);
		COORD current_position = mConsoleInfo.dwCursorPosition;
		int new_x = current_position.X + x_inc;
		int new_y = current_position.Y + y_inc;

		if (wrap)
		{
			while (new_x < 0)
			{
				new_x = mConsoleInfo.dwSize.X + new_x;
			}
			while (new_y < 0)
			{
				new_y = mConsoleInfo.dwSize.Y + new_y;
			}
			new_x %= mConsoleInfo.dwSize.X;
			new_y %= mConsoleInfo.dwSize.Y;
		}
		else
		{
			if (new_x > mConsoleInfo.dwSize.X) { new_x = mConsoleInfo.dwSize.X; }
			if (new_y > mConsoleInfo.dwSize.Y) { new_y = mConsoleInfo.dwSize.Y; }
			if (new_x < 0) { new_x = 0; }
			if (new_y < 0) { new_y = 0; }
		}
		MoveCursorTo(new_x, new_y);
	}

	void W32Console::Clear(const int bg_colour)
	{
		assert((bg_colour >= 0 && bg_colour < 16) || bg_colour == -1);

		// Number of cells in current buffer
		int console_size = mConsoleInfo.dwSize.X * mConsoleInfo.dwSize.Y;

		if (bg_colour != -1)	SetBackgroundColour(bg_colour);

		DWORD cCharsWritten;
		COORD coordScreen = { 0, 0 };
		GetConsoleScreenBufferInfo(mConsoleHandle, &mConsoleInfo);
		// 		Fill screen with blanks
		FillConsoleOutputCharacter(mConsoleHandle, (TCHAR) ' ',
			console_size, coordScreen, &cCharsWritten);
		// Set buffer attributes
		FillConsoleOutputAttribute(mConsoleHandle, mConsoleInfo.wAttributes,
			console_size, coordScreen, &cCharsWritten);

		MoveCursorTo(0, 0);
	}

	void W32Console::ClearLine(const int line_no, const std::string& clear_char)
	{
		assert(line_no >= 0 && line_no <= mConsoleInfo.dwSize.Y);
		assert(clear_char.length() == 0 || clear_char.length() == 1);

		char clear_character = ' ';
		if (clear_char.length() == 1) { clear_character = clear_char[0]; }

		COORD start_point = { 0, line_no };
		DWORD cCharsWritten;

		GetConsoleScreenBufferInfo(mConsoleHandle, &mConsoleInfo);
		// Fill screen with blanks
		FillConsoleOutputCharacter(mConsoleHandle, (TCHAR)clear_character,
			mConsoleInfo.dwSize.X, start_point, &cCharsWritten);
		FillConsoleOutputAttribute(mConsoleHandle, mConsoleInfo.wAttributes,
			mConsoleInfo.dwSize.X, start_point, &cCharsWritten);
	}

	void W32Console::SetTextColour(const int colour)
	{
		assert(colour >= 0 && colour <= 16);
		mForegroundColour = static_cast<short>(colour);

		SetConsoleTextAttribute(mConsoleHandle,
			(WORD)((mBackgroundColour << 4) | mForegroundColour));
	}

	void W32Console::SetBackgroundColour(const int colour)
	{
		assert(colour >= 0 && colour <= 16);
		mBackgroundColour = static_cast<short>(colour);

		SetConsoleTextAttribute(mConsoleHandle,
			(WORD)((mBackgroundColour << 4) | mForegroundColour));
	}

	void W32Console::SwitchTextColour(const int colour)
	{
		SetTextColour(colour);

		// Number of cells in current buffer
		int console_size = mConsoleInfo.dwSize.X * mConsoleInfo.dwSize.Y;

		DWORD cCharsWritten;
		COORD coordScreen = { 0, 0 };
		GetConsoleScreenBufferInfo(mConsoleHandle, &mConsoleInfo);
		// Set buffer attributes
		FillConsoleOutputAttribute(mConsoleHandle, mConsoleInfo.wAttributes,
			console_size, coordScreen, &cCharsWritten);
	}

	void W32Console::SwitchBackgroundColour(const int colour)
	{
		SetBackgroundColour(colour);
		// Number of cells in current buffer
		int console_size = mConsoleInfo.dwSize.X * mConsoleInfo.dwSize.Y;

		DWORD cCharsWritten;
		COORD coordScreen = { 0, 0 };
		GetConsoleScreenBufferInfo(mConsoleHandle, &mConsoleInfo);
		// Set buffer attributes
		FillConsoleOutputAttribute(mConsoleHandle, mConsoleInfo.wAttributes,
			console_size, coordScreen, &cCharsWritten);
	}

	void W32Console::RedirectSTDIO()
	{
		freopen("CONIN$", "rb", stdin);   // reopen stdin handle as console window input
		freopen("CONOUT$", "wb", stdout); // reopen stout handle as console window output
		freopen("CONOUT$", "wb", stderr); // reopen stderr handle as console window output
	}
}