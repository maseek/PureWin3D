#ifndef ITIMER_H
#define ITIMER_H

#include <type_traits>
#include "../INoCopy.h"

namespace pw
{
	template <typename T>
	class ITimer : INoCopy
	{
	public:
		double update( )
		{
			return static_cast< const T* >( this )->test( );
		}
		void reset( )
		{
			static_cast< const T* >( this )->reset( );
		}
		double timeInMs( ) const
		{
			return static_cast< const T* >( this )->timeInMs( );
		}
		double inverseFps( ) const
		{
			return static_cast< const T* >( this )->inverseFps( );
		}
		double fps( ) const
		{
			return 1 / inverseFps( );
		}
	private:
		ITimer( ) 
		{
			static_assert( !std::is_same<decltype( &T::update ), decltype( &ITimer<T>::update )>::value, "Static polymorphic function test() was not overriden." );
			static_assert( !std::is_same<decltype( &T::reset ), decltype( &ITimer<T>::reset )>::value, "Static polymorphic function reset() was not overriden." );
			static_assert( !std::is_same<decltype( &T::timeInMs ), decltype( &ITimer<T>::timeInMs )>::value, "Static polymorphic function timeInMs() was not overriden." );
			static_assert( !std::is_same<decltype( &T::inverseFps ), decltype( &ITimer<T>::inverseFps )>::value, "Static polymorphic function inverseFps() was not overriden." );
		}
		friend T;
	};
}

#endif