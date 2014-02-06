#ifndef I_NO_COPY_H
#define I_NO_COPY_H

namespace pw
{
	class INoCopy
	{
	protected:
		INoCopy( ) { }
		~INoCopy( ) { }
	private:
		INoCopy( const INoCopy& );
		const INoCopy& operator=( const INoCopy& );
	};
}

#endif