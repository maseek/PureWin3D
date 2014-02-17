#ifndef PW_INPUT_DEVICES_H
#define PW_INPUT_DEVICES_H

namespace pw
{
#	ifdef PW_PLATFORM_WIN32
	// TODO: add other VKs - http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
	enum class Key : unsigned char
	{
		Tab = VK_TAB,
		Return = VK_RETURN,
		Shift = VK_SHIFT,
		Ctrl = VK_CONTROL,
		Alt = VK_MENU,
		Esc = VK_ESCAPE,
		Space = VK_SPACE,
		ArrowLeft = VK_LEFT,
		ArrowUp = VK_UP,
		ArrowRight = VK_RIGHT,
		ArrowDown = VK_DOWN,
		A = 'A',
		B = 'B',
		C = 'C',
		D = 'D',
		E = 'E',
		F = 'F',
		G = 'G',
		H = 'H',
		I = 'I',
		J = 'J',
		K = 'K',
		L = 'L',
		M = 'M',
		N = 'N',
		O = 'O',
		P = 'P',
		Q = 'Q',
		R = 'R',
		S = 'S',
		T = 'T',
		U = 'U',
		V = 'V',
		W = 'W',
		X = 'X',
		Y = 'Y',
		Z = 'Z',
		Num0 = VK_NUMPAD0,
		Num1 = VK_NUMPAD1,
		Num2 = VK_NUMPAD2,
		Num3 = VK_NUMPAD3,
		Num4 = VK_NUMPAD4,
		Num5 = VK_NUMPAD5,
		Num6 = VK_NUMPAD6,
		Num7 = VK_NUMPAD7,
		Num8 = VK_NUMPAD8,
		Num9 = VK_NUMPAD9,
		F1 = VK_F1,
		F2 = VK_F2,
		F3 = VK_F3,
		F4 = VK_F4,
		F5 = VK_F5,
		F6 = VK_F6,
		F7 = VK_F7,
		F8 = VK_F8,
		F9 = VK_F9,
		F10 = VK_F10,
		F11 = VK_F11,
		F12 = VK_F12
	};
#	endif
	enum class MouseButton : unsigned char
	{
		LeftButton,
		MiddleButton,
		RightButton,
		XButton1,
		XButton2,
		Count
	};
}

#endif