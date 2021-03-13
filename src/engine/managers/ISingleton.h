#pragma once
#ifndef ISINGLETON_H_
#define ISINGLETON_H_

namespace LittleEngine 
{
	template <typename T> class ISingleton 
	{
	public:
		static T* instance() 
		{
			static T instance;
			return &instance;
		}
	protected:
		ISingleton<T>() {};
	public:
		ISingleton<T>(ISingleton<T> const&) = delete;
		void operator=(T const&) = delete;
	};
}

#endif // !ISINGLETON_H_

