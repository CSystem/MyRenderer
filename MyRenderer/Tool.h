
#ifndef _TOOL_H
#define _TOOL_H
#define DEBUG
// #define  DEBUG
// 
// #ifdef DEBUG
// #define Debug(x) std::cout<<x<<endl;
// #else
// #define Debug(x)
// #endif // DEBUG
// class MyString;
// 
// std::ostream& operator<<(std::ostream& os, MyString& str) 
// {
// 	os<<str;
// 	return os;
// }
// 
// class  MyString
// {
// 	friend std::ostream& operator <<(std::ostream&, MyString&);
// public:
// 	MyString();
// 	MyString(std::string const &str){ _str = str; };
// private:
// 	std::string _str;
// };

#ifdef DEBUG
class  Debug
{
public:
	static void DebugLog(const std::string& str) {	
		std::cout<<str.c_str()<<": "<<__LINE__<<std::endl;
	}
private:
};
#else
class  Debug
{
public:
	static void DebugLog(const std::string& str) {}
private:
};
#endif // DEBUG
#endif

