/*****************************************************************//**
 * @file   Base.hpp
 * @brief  Core defines
 * 
 * @author Lolitron
 * @date   May 2023
 *********************************************************************/
#pragma once
#include <memory>

#ifdef LT_PLATFORM_WINDOWS
	#ifdef LT_BUILD_STATIC
		#define LITHE_API //__declspec(dllexport)
	#else
		#define LITHE_API //__declspec(dllimport)
	#endif
#else
	#error Lithe only supports Windows!
#endif

#ifdef LT_DEBUG
	#ifdef LT_PLATFORM_WINDOWS
		#define LT_DEBUGBREAK() __debugbreak()
	#endif

	#define LT_ASSERTIONS
#endif

/// Needed to stop substitution and pass only a name (if x is a macro name)
#define LT_EXPAND(x) x

#define BIT(x) (1<<x)

/// Since all event functions are member (and need 'this' pointer) we need to wrap them in lambdas hooking 'this'
#define LT_BIND_EVENT_FN(fn) [this](auto&&... params) -> decltype(auto) {return this->fn(std::forward<decltype(params)>(params)...);}
#define LT_BIND_EVENT_FN_CASTED_THIS(func, type) [this](auto&&... params) -> decltype(auto) { return static_cast<type*>(this)->func(std::forward<decltype(params)>(params)...); }


namespace Lithe
{
	#define SCRAP_BUFFER_SIZE 1024
    inline char g_ScrapBuffer[SCRAP_BUFFER_SIZE];

	template<class T>
	using Scope = std::unique_ptr<T>;
    template<class T, class... Args>
    Scope<T> MakeScope(Args&&... args) { return std::make_unique<T>(std::forward<Args>(args)...); }

	template<class T>
	using Ref = std::shared_ptr<T>;
    template<class T, class... Args>
	Ref<T> MakeRef(Args&&... args) { return std::make_shared<T>(std::forward<Args>(args)...); }

	struct NullType {};

	template<class... T>
	struct TypeList 
	{
		using Head = NullType;
		using Tail = NullType;
	};

	using EmptyTypeList = TypeList<>;

	template<class H, class... T>
	struct TypeList<H, T...>
	{
		using Head = H;
		using Tail = TypeList<T...>;
	};

	template <class TL>
	struct IsEmpty : std::true_type {};

	template <>
	struct IsEmpty<EmptyTypeList> : std::true_type {};

	template<class... Args>
	struct IsEmpty<TypeList<Args...>>
		: std::integral_constant<bool,
		std::is_same<typename TypeList<Args...>::Head, NullType>::value && 
		IsEmpty<typename TypeList<Args...>::Tail>::value>  //inheriting whole constant type to have ::value 
	{};

	template<class T, class TL>
	struct Contains : std::false_type {};

	template<class... Args>
	struct Contains<NullType, Args...> : std::false_type {};

	template<class T, class... Args>
	struct Contains<T, TypeList<Args...>>
		: std::integral_constant<bool,
		std::is_same<T, typename TypeList<Args...>::Head>::value ||
		Contains<T, typename TypeList<Args...>::Tail>::value
		>
	{};

	/**
	 * @brief Helper type to iterate through TypeList
	 * @tparam StaicFunctor is a (template) class/struct with static void Call(...) function
	*/
	template<class TL, template<class T> class StaticFunctor>
	struct ForEach;

	template<class Last, template<class T> class StaticFunctor>
	struct ForEach<TypeList<Last>, StaticFunctor>
	{
	public:
		template<class... Args>
		static void Iterate(Args&& ...args)
		{
			StaticFunctor<Last>::Call(std::forward<Args>(args)...);
		}
	};

	template<class Hd, class... Tl, template<class T> class StaticFunctor>
	struct ForEach<TypeList<Hd, Tl...>, StaticFunctor>
	{
	public:
        template<class... Args>
        static void Iterate(Args&& ...args)
        {
            StaticFunctor<Hd>::Call(std::forward<Args>(args)...);
			ForEach<TypeList<Tl...>, StaticFunctor>::Iterate(std::forward<Args>(args)...);
        }
	};
}
