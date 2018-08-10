///
/// @file    singleton.h
/// @author  LiuhuiDing@gmail.com
/// @date    2018-08-03 20:04:46
///

#ifndef SINGLETON_H_
#define SINGLETON_H_
#include <pthread.h>
#include <iostream>
#include <string>
namespace WdCoding
{
	template <typename Object>
	class Singleton
	{
		public:
			template <typename ...Args>
			static Object * getInstance(Args && ...args)
			{
				if(NULL == pInstance)
				{
					pInstance = new Object(std::forward<Args>(args)...);
				}
				atexit(destroy);
				return pInstance;
			}
			static void destroy()
			{
				if(pInstance)
					delete pInstance;
			}
			//do something
		private:
			Singleton();
			~Singleton();
			static Object *pInstance;
	};

	template <typename Object>
	Object * Singleton<Object>::pInstance = NULL;

}

#endif
