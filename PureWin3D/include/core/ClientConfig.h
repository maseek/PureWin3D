#ifndef PW_CLIENT_CONFIG_H
#define PW_CLIENT_CONFIG_H

namespace pw
{
	enum class WindowStyle : unsigned
	{
		Windowed,
		Fullscreen,
		Default = Windowed
	};

	class ClientConfig
	{
	public:
		ClientConfig( );
		ClientConfig( const ClientConfig& ) = delete;
		const ClientConfig& operator=( const ClientConfig& ) = delete;
		ClientConfig( ClientConfig&& ) = delete;
		const ClientConfig& operator=( ClientConfig&& ) = delete;
	public:
		unsigned getWidth( ) const;
		unsigned getHeight( ) const;
		unsigned getBitsPerPx( ) const;
		WindowStyle getWindowStyle( ) const;
	private:
		unsigned		_width;
		unsigned		_height;
		unsigned		_bitsPerPx;
		WindowStyle		_windowStyle;
	};
}

#endif