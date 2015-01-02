#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <class T>
class TSingleton
{
protected:

	static T *m_pSingleton;   // Statisches Objekt

public:


	virtual ~TSingleton()
	{
	}

	// Get
	inline static T* Get()
	{
		// Existiert schon eine Instanz?
		if (!m_pSingleton)
			m_pSingleton = new T;   // Nein, dann neue Instanz erzeugen

		// Zeiger auf die Instanz zurückgeben
		return (m_pSingleton);

	}

	
	static void Del()
	{
		// Gab es eine Instanz?
		if (m_pSingleton)
		{
			delete (m_pSingleton);  // Ja, dann freigeben
			m_pSingleton = NULL;    // und Zeiger auf NULL setzen
		}

	}

};

// Die statische Variable erzeugen
//
template <class T>
T* TSingleton<T>::m_pSingleton = 0;

#endif
