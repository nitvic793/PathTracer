#pragma once

#include <string>

namespace nv
{
	template <typename T>
	constexpr std::string_view TypeName() noexcept {
		std::string_view name, prefix, suffix;
#ifdef __clang__
		name = __PRETTY_FUNCTION__;
		prefix = "auto type_name() [T = ";
		suffix = "]";
#elif defined(__GNUC__)
		name = __PRETTY_FUNCTION__;
		prefix = "constexpr auto type_name() [with T = ";
		suffix = "]";
#elif defined(_MSC_VER)
		name = __FUNCSIG__;
		prefix = "auto __cdecl type_name<";
		suffix = ">(void) noexcept";
#endif
		name.remove_prefix(prefix.size() - 1);
		name.remove_suffix(suffix.size());
		return name;
	}
}