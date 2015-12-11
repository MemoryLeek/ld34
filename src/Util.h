#ifndef UTIL_H
#define UTIL_H

#include <math.h>
#include <vector>

enum GamepadButtons
{
	Accept = 0,
	Reject = 1
};

enum GamepadAxis
{
	Horizontal = 0,
	Vertical = 1
};

template<class T1, class T2>
std::vector<T1> &operator <<(std::vector<T1> &vector, T2 element)
{
	vector.push_back(element);

	return vector;
}

template <typename T>
void UNUSED(T &&)
{

}

#endif // UTIL_H
