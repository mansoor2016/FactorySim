#pragma once

#include <type_traits>

template <class T>
struct IComparable
{
	constexpr bool operator==(const T& rhs) const noexcept
	{
		return true;
	}

	constexpr bool operator!=(const T& rhs) const noexcept
	{
		return !operator==(rhs);
	}

	template <class U>
	constexpr bool operator==(const U& rhs) const noexcept
	{
		return false;
	}

	template <class U>
	constexpr bool operator!=(const U& rhs) const noexcept
	{
		return !operator==<U>(rhs);
	}
};