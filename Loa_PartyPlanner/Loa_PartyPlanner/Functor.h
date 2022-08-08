#pragma once
#include <codecvt>
#include <locale>

using convert_type = std::codecvt_utf8<wchar_t>;
extern std::wstring_convert<convert_type, wchar_t> converter;

template <typename T>
void SafeDelete(T& pointer)
{
	if (NULL != pointer)
	{
		delete pointer;
		pointer = NULL;
	}
}

inline std::string PathToString()
{
	wchar_t path[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, path, MAX_PATH);

	std::string strpath = converter.to_bytes(std::wstring(path));

	auto p = strpath.find_last_of('\\');
	strpath.erase(p, strpath.length());

	return strpath;
}

#define NO_COPY(ClassName)						\
private:										\
	ClassName(const ClassName& Obj);			\
	ClassName& operator=(const ClassName& Obj);

#define DECLARE_SINGLETON(ClassName)		\
		NO_COPY(ClassName)					\
public:										\
	static ClassName* GetInstance()			\
	{										\
		if(nullptr == m_pInstance)			\
		{									\
			m_pInstance = new ClassName;	\
		}									\
		return m_pInstance;					\
	}										\
	void DestroyInstance()					\
	{										\
		if(m_pInstance)						\
		{									\
			delete m_pInstance;				\
			m_pInstance = nullptr;			\
		}									\
	}										\
private:									\
	static ClassName*	m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)		\
ClassName* ClassName::m_pInstance = nullptr;

#define DECLARE_STATE(STATENAME, OWNER)                     \
NO_COPY(STATENAME)                              \
public:                                             \
   static   STATENAME* Instance();                        \
