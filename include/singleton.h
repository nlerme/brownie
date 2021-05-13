#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <cstdio>
#include "singleton_base.h"
#include "singleton_manager.h"


template <typename Type> class CSingleton : public CSingletonBase
{
     private :
	static Type * m_Instance;

	void _kill()
	{
		delete m_Instance;
		m_Instance = NULL;
	}

     protected :
	CSingleton(){}
	virtual ~CSingleton(){}

     public :
	static Type* instance()
	{
		if( !m_Instance )
		{
			m_Instance = new Type;
			CSingletonManager::add(m_Instance);
		}

		return m_Instance;
	}
};

template<typename Type> Type * CSingleton<Type>::m_Instance = NULL;

#endif //__SINGLETON_H__
