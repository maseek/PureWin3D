#ifndef PW_INPUT_MESSAGE_H
#define PW_INPUT_MESSAGE_H

#include "InputDevices.h"

namespace pw
{
	class InputMessage
	{
	public:
		enum class Type : unsigned char
		{
			Close,
			KeyDown,
			KeyUp,
			MouseButtonDown,
			MouseButtonUp,
			MouseMove,
			MouseWheel,
			Text,
			Count
		};
		struct KeyMessage
		{
			unsigned char type;
			bool lCtrl;
			bool rCtrl;
			bool lAlt;
			bool rAlt;
			bool lShift;
			bool rShift;
		};
		struct MouseButtonMessage
		{
			unsigned short x;
			unsigned short y;
			MouseButton type;
			bool ctrl;
			bool lButton;
			bool mButton;
			bool rButton;
			bool shift;
			bool xButton1;
			bool xButton2;
		};
		struct MouseMoveMessage
		{
			unsigned short x;
			unsigned short y;
			bool ctrl;
			bool lButton;
			bool mButton;
			bool rButton;
			bool shift;
			bool xButton1;
			bool xButton2;
		};
		struct MouseWheelMessage
		{
			unsigned short x;
			unsigned short y;
			unsigned short delta;
			bool ctrl;
			bool lButton;
			bool mButton;
			bool rButton;
			bool shift;
			bool xButton1;
			bool xButton2;
		};
		struct TextMessage
		{
			unsigned unicode;
		};

		InputMessage( )
		{
		}
		InputMessage( const InputMessage::Type type ) : type( type )
		{
		}

		bool operator==( const InputMessage::Type type ) const
		{
			return InputMessage::type == type;
		}

		Type type;
		union
		{
			KeyMessage key;
			MouseButtonMessage mouseButton;
			MouseMoveMessage mouseMove;
			MouseWheelMessage mouseWheel;
			TextMessage text;
		};
	};
}

#endif