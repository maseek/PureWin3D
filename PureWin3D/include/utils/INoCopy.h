#ifndef PW_I_NO_COPY_H
#define PW_I_NO_COPY_H

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