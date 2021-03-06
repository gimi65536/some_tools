//mainly written in C++17. attempt to support C++14.
//some methods may be different from ways to use between those in C++14 and C++17
#ifndef _DoYouNeedHelp_
#define _DoYouNeedHelp_

#include <type_traits>
#include <vector>
#include <map>
#include <cstdint>
#include <numeric>
#include <cmath>
#include <string>
#include <sstream>
#include <list>
using namespace std;

string cts(char c){
	return string(1, c);
}

#ifdef __cpp_concepts
template<typename T>
concept bool Sizeable = requires(T t){
	{t.size()} -> size_t;
};
#endif

#if __cplusplus >= 201703L
template <typename T>
using expr_type = remove_cv_t<remove_reference_t<T>>;
template <typename T, typename U, typename ...Args>
struct is_contain_first : bool_constant<is_same_v<expr_type<T>, expr_type<U>> || is_contain_first<expr_type<T>, Args...>::value>{};
template <typename T, typename U>
struct is_contain_first<T, U> : bool_constant<is_same_v<expr_type<T>, expr_type<U>>>{};
#else
template <typename T>
using expr_type = typename remove_cv<typename remove_reference<T>::type>::type;
template <typename T, typename U, typename ...Args>
struct is_contain_first : integral_constant<bool, is_same<expr_type<T>, expr_type<U>>::value || is_contain_first<expr_type<T>, Args...>::value>{};
template <typename T, typename U>
struct is_contain_first<T, U> : integral_constant<bool, is_same<expr_type<T>, expr_type<U>>::value>{};
#endif

#ifdef __cpp_concepts
template<Sizeable C>
#else
template<typename C>
#endif
void total_size_helper(size_t& sol, const C& c){
	sol += c.size();
}

#ifdef __cpp_concepts
template<Sizeable C, typename ...Containers>
#else
template<typename C, typename ...Containers>
#endif
void total_size_helper(size_t& sol, const C& c1, const Containers&... cs){
	sol += c1.size();
	#if __cpp_if_constexpr >= 201606
	if constexpr(sizeof...(Containers) > 0){
		total_size_helper(sol, cs...);
	}
	#else
	total_size_helper(sol, cs...);
	#endif
}

#ifdef __cpp_concepts
template<Sizeable ...Containers>
#else
template<typename ...Containers>
#endif
size_t total_size(const Containers&... cs){
	#if __cpp_fold_expressions >= 201411
	return (cs.size() + ...);
	#else
	size_t sol = 0;
	total_size_helper(sol, cs...);
	return sol;
	#endif
}

template<typename R, typename T>
void concatsv_helper(vector<R>& sol, const vector<T>& v){
	for(const auto& i : v){
		sol.push_back(i);
	}
}
template<typename R, typename T, typename ...Vectors>
void concatsv_helper(vector<R>& sol, const vector<T>& v1, const Vectors&... vs){
	for(const auto& i : v1){
		sol.push_back(i);
	}
	concatsv_helper(sol, vs...);
}
template<typename ...Vectors>
auto concatsv(const Vectors&... vs){
	vector<common_type_t<typename Vectors::value_type...>> sol;
	sol.reserve(total_size(vs...));
	#if __cpp_fold_expressions >= 201411
	(sol.insert(sol.end(), vs.begin(), vs.end()) ,...);
	#else
	concatsv_helper(sol, vs...);
	#endif
	return sol;
}
template<typename R, typename S, typename T, typename U>
void concatsm_helper(map<R, S>& sol, const map<T, U>& m){
	#if __cpp_structured_bindings >= 201606
	for(const auto& [key, value] : m){
		sol[key] = value;
	}
	#else
	for(const auto& p : m){
		sol[p.first] = p.second;
	}
	#endif
}
template<typename R, typename S, typename T, typename U, typename ...Maps>
void concatsm_helper(map<R, S>& sol, const map<T, U>& m1, const Maps&... ms){
	#if __cpp_structured_bindings >= 201606
	for(const auto& [key, value] : m1){
		sol[key] = value;
	}
	#else
	for(const auto& p : m1){
		sol[p.first] = p.second;
	}
	#endif
	concatsm_helper(sol, ms...);
}
template<typename ...Maps>
auto concatsm(const Maps&... ms){
	map<common_type_t<typename Maps::key_type...>, common_type_t<typename Maps::mapped_type...>> sol;
	#if __cpp_fold_expressions >= 201411
	(sol.insert(ms.begin(), ms.end()) ,...);
	#else
	concatsm_helper(sol, ms...);
	#endif
	return sol;
}
template<typename T, typename U>
vector<T> keys(const map<T, U>& m){
	vector<T> sol;
	sol.reserve(m.size());
	#if __cpp_structured_bindings >= 201606
	for(const auto& [key, value] : m){
		sol.push_back(key);
	}
	#else
	for(const auto& p : m){
		sol.push_back(p.first);
	}
	#endif
	return sol;
}
template<typename T, typename U>
vector<U> values(const map<T, U>& m){
	vector<U> sol;
	sol.reserve(m.size());
	#if __cpp_structured_bindings >= 201606
	for(const auto& [key, value] : m){
		sol.push_back(value);
	}
	#else
	for(const auto& p : m){
		sol.push_back(p.second);
	}
	#endif
	return sol;
}
template<typename Vector>
string join(string sep, const Vector& v){
	string sol;
	bool success = false;
	for(const auto& i : v){
		if(success){
			sol += sep;
		}
		success = true;
		sol += i;
	}
	return sol;
}
namespace MathConstexpr{ //define math functions that in cmath without constexpr
	template<typename T>
	constexpr T abs(T a){
		return (a >= 0 ? a : -a);
	}
}
namespace MathAddition{ //define math functions that C++14 lacks
	#if __cpp_lib_gcd >= 201606
	using std::gcd;
	using std::lcm;
	template<typename A, typename B>
	constexpr common_type_t<A, B> easygcd(A a, B b){ //avoid type check if std::gcd has
		return (a == 0 ? MathConstexpr::abs(b) : (b == 0 ? MathConstexpr::abs(a) : easygcd(b, a % b)));
	}
	template<typename A, typename B>
	constexpr common_type_t<A, B> easylcm(A a, B b){
		return ((a != 0 && b != 0) ? (MathConstexpr::abs(a) / easygcd(a, b) * MathConstexpr::abs(b)) : static_cast<common_type_t<A, B>>(0));
	}
	#else
	template<typename A, typename B>
	constexpr common_type_t<A, B> gcd(A a, B b){
		return (a == 0 ? MathConstexpr::abs(b) : (b == 0 ? MathConstexpr::abs(a) : gcd(b, a % b)));
	}
	template<typename A, typename B>
	constexpr common_type_t<A, B> lcm(A a, B b){
		return ((a != 0 && b != 0) ? (MathConstexpr::abs(a) / gcd(a, b) * MathConstexpr::abs(b)) : static_cast<common_type_t<A, B>>(0));
	}
	template<typename A, typename B>
	constexpr common_type_t<A, B> easygcd(A a, B b){ //avoid type check if std::gcd has
		return gcd(a, b);
	}
	template<typename A, typename B>
	constexpr common_type_t<A, B> easylcm(A a, B b){
		return lcm(a, b);
	}
	#endif
}
namespace Math{
	using namespace MathConstexpr;
	using namespace MathAddition;
}
namespace StaticSort{
	template<typename T, T a, T b>
	struct less_than    : conditional_t<(a < b), true_type, false_type> {};
	template<typename T, T a, T b>
	struct greater_than : conditional_t<(a > b), true_type, false_type> {};

	template<typename Int, Int ...Args>
	struct _Array{
		static constexpr int element[sizeof...(Args)] = {Args...};
	};
#if __cplusplus < 201703L
	//make Array::element linked
	//In C++17, static member var can be inline, and not need to (but you still can) link outside.
	//And, constexpr is implicitly inline.
	//C++14, of course, still make you to do so:
	template<typename Int, Int ...Args>
	constexpr int _Array<Int, Args...>::element[sizeof...(Args)];
#endif
	using MathConstexpr::abs;
	using Math::gcd;
	template<typename Int>
	class _ratio{
	private:
		Int num;
		Int den;
	public:
		constexpr _ratio(const Int& n, const Int& d = 1) : num(StaticSort::abs(n)), den(StaticSort::abs(d)){
			Int g = StaticSort::gcd(n, d);
			num /= g;
			den /= g;
			if((n > 0 && d < 0) || (n < 0 && den > 0)){
				num = -num;
			}
		}
	};
	using ratio = _ratio<intmax_t>;
	#define newtypeARRAY(name, type) template<type ...Args> struct name : _Array<type, Args...>{}
	newtypeARRAY(Array, int);

#if __cplusplus >= 201703L
	template<size_t Now, size_t Begin, size_t End, typename A, auto...>
	struct Picker{
		//when Picker<_, _, _, Array<>>, no way to deduce Int.
		using sol = A;
	};
	template<size_t Now, size_t Begin, size_t End, typename Int, template<Int...> class List, Int ...Args>
	struct Picker<Now, Begin, End, List<Args...>>{
		//Base case
		using sol = List<Args...>;
	};
	template<size_t Now, size_t Begin, size_t End, typename Int, template<Int...> class List, Int ...Args, Int N, Int ...Rem>
	struct Picker<Now, Begin, End, List<Args...>, N, Rem...>{
		using sol = conditional_t<(Begin >= End || Now >= End), List<Args...>,
			conditional_t<(Begin > Now), typename Picker<Now + 1, Begin, End, List<Args...>, Rem...>::sol,
										 typename Picker<Now + 1, Begin, End, List<Args..., N>, Rem...>::sol>
		>;
	};

	template<size_t Begin, size_t End, typename T>
	struct Pick;
	template<size_t Begin, size_t End, typename Int, template<Int...> class List, Int ...Args>
	struct Pick<Begin, End, List<Args...>>{
		using sol = conditional_t<(Begin >= End), List<>, typename Picker<0, Begin, End, List<>, Args...>::sol>;
	};

	template<typename T, typename A, typename B, template<typename, auto...> class U>
	struct Merger{
		//Merger<Array<>, Array<>, Array<>, Comp>, no way to deduce Int.
		using sol = T;
	};
	template<typename Int, template<Int...> class List, template<class, Int, Int> class Comp, Int ...Args, Int ...Args1>
	struct Merger<List<Args...>, List<Args1...>, List<>, Comp>{
		using sol = List<Args..., Args1...>;
	};
	template<typename Int, template<Int...> class List, template<class, Int, Int> class Comp, Int N2, Int ...Args, Int ...Args2>
	struct Merger<List<Args...>, List<>, List<N2, Args2...>, Comp>{
		using sol = List<Args..., N2, Args2...>;
	};
	template<typename Int, template<Int...> class List, template<class, Int, Int> class Comp, Int N1, Int N2, Int ...Args, Int ...Args1, Int ...Args2>
	struct Merger<List<Args...>, List<N1, Args1...>, List<N2, Args2...>, Comp>{
		using sol = conditional_t<!(Comp<Int, N2, N1>::value),
								  typename Merger<List<Args..., N1>, List<Args1...>, List<N2, Args2...>, Comp>::sol,
								  typename Merger<List<Args..., N2>, List<N1, Args1...>, List<Args2...>, Comp>::sol>;
	};

	template<typename A, typename B, template<typename, auto...> class U>
	struct Merge{
		//called if both A, B is List<>
		using sol = A;
	};
	template<typename Int, template<Int...> class List, template<class, Int, Int> class Comp, Int ...Args1, Int ...Args2>
	struct Merge<List<Args1...>, List<Args2...>, Comp>{
		using sol = typename Merger<List<>, List<Args1...>, List<Args2...>, Comp>::sol;
	};

	template<typename T, template<typename, auto...> class U>
	struct MSort{
		//called if T is List<>, or argument less than 2
		using sol = T;
	};
	template<typename Int, template<Int...> class List, template<class, Int, Int> class Comp, Int N1, Int N2, Int ...Args>
	struct MSort<List<N1, N2, Args...>, Comp>{
		using sol = typename Merge<typename MSort<typename Pick<0, (sizeof...(Args) + 2) / 2, List<N1, N2, Args...>>::sol, Comp>::sol,
								   typename MSort<typename Pick<(sizeof...(Args) + 2) / 2, (sizeof...(Args) + 2), List<N1, N2, Args...>>::sol, Comp>::sol, Comp>::sol;
	};
#else
	//Where you cannot deduce template template.
	template<typename Int, size_t Now, size_t Begin, size_t End, typename A, Int...>
	struct Picker; //Int is given explicitly, no need to complete this case.
	template<typename Int, size_t Now, size_t Begin, size_t End, template<Int...> class List, Int ...Args>
	struct Picker<Int, Now, Begin, End, List<Args...>>{
		//Base case
		using sol = List<Args...>;
	};
	template<typename Int, size_t Now, size_t Begin, size_t End, template<Int...> class List, Int ...Args, Int N, Int ...Rem>
	struct Picker<Int, Now, Begin, End, List<Args...>, N, Rem...>{
		using sol = conditional_t<(Begin >= End || Now >= End), List<Args...>,
			conditional_t<(Begin > Now), typename Picker<Int, Now + 1, Begin, End, List<Args...>, Rem...>::sol,
										 typename Picker<Int, Now + 1, Begin, End, List<Args..., N>, Rem...>::sol>
		>;
	};

	template<typename Int, size_t Begin, size_t End, typename T>
	struct Pick;
	template<typename Int, size_t Begin, size_t End, template<Int...> class List, Int ...Args>
	struct Pick<Int, Begin, End, List<Args...>>{
		using sol = conditional_t<(Begin >= End), List<>, typename Picker<Int, 0, Begin, End, List<>, Args...>::sol>;
	};

	template<typename Int, typename T, typename A, typename B, template<typename, Int...> class U>
	struct Merger{}; //Int is given explicitly, no need to complete this case.
	template<typename Int, template<Int...> class List, template<class, Int, Int> class Comp, Int ...Args, Int ...Args1>
	struct Merger<Int, List<Args...>, List<Args1...>, List<>, Comp>{
		using sol = List<Args..., Args1...>;
	};
	template<typename Int, template<Int...> class List, template<class, Int, Int> class Comp, Int N2, Int ...Args, Int ...Args2>
	struct Merger<Int, List<Args...>, List<>, List<N2, Args2...>, Comp>{
		using sol = List<Args..., N2, Args2...>;
	};
	template<typename Int, template<Int...> class List, template<class, Int, Int> class Comp, Int N1, Int N2, Int ...Args, Int ...Args1, Int ...Args2>
	struct Merger<Int, List<Args...>, List<N1, Args1...>, List<N2, Args2...>, Comp>{
		using sol = conditional_t<!(Comp<Int, N2, N1>::value),
								  typename Merger<Int, List<Args..., N1>, List<Args1...>, List<N2, Args2...>, Comp>::sol,
								  typename Merger<Int, List<Args..., N2>, List<N1, Args1...>, List<Args2...>, Comp>::sol>;
	};

	template<typename Int, typename A, typename B, template<typename, Int...> class U>
	struct Merge{}; //Int is given explicitly, no need to complete this case.
	template<typename Int, template<Int...> class List, template<class, Int, Int> class Comp, Int ...Args1, Int ...Args2>
	struct Merge<Int, List<Args1...>, List<Args2...>, Comp>{
		using sol = typename Merger<Int, List<>, List<Args1...>, List<Args2...>, Comp>::sol;
	};

	template<typename Int, typename T, template<typename, Int...> class U>
	struct MSort{
		//called if argument less than 2
		using sol = T;
	};
	template<typename Int, template<Int...> class List, template<class, Int, Int> class Comp, Int N1, Int N2, Int ...Args>
	struct MSort<Int, List<N1, N2, Args...>, Comp>{
		using sol = typename Merge<Int, typename MSort<Int, typename Pick<Int, 0, (sizeof...(Args) + 2) / 2, List<N1, N2, Args...>>::sol, Comp>::sol,
										typename MSort<Int, typename Pick<Int, (sizeof...(Args) + 2) / 2, (sizeof...(Args) + 2), List<N1, N2, Args...>>::sol, Comp>::sol, Comp>::sol;
	};
#endif
}

//only apply for a > 0 && b > 0
//whether there is a positive integer N satisfies a^N == b
template<typename T>
constexpr bool ispow(const T& a, const T& b){
	using Math::gcd;
	if(a == b){
		return true;
	}
	if(a > b){
		return false;
	}
	if(a == 1){return false;}
	if(gcd(a, b) != a){
		return false;
	}
	return ispow(a, b / a);
	//return (a == b ? true : (a > b ? ispow(b, a) : (gcd(a, b) == 1 ? false : (ispow(a, b / gcd(a, b))))));
}
template<typename T>
constexpr bool ispow_exchange(const T& a, const T& b){
	return ispow(a, b) || ispow(b, a);
}
//0 iff a == b or ispow_exchange(a, b) is false
//behavior like log_a(b)
template<typename I, typename T>
constexpr I _howpow(const T& a, T b){
	//static_assert(is_signed_v<I>);
	using Math::gcd;
	if(a == b){return 0;}
	if(a > b){
		return -_howpow<I>(b, a);
	}
	if(a == 1){return 0;} //error
	if(gcd(a, b) != a){return 0;}
	T tmp = 0;
	do{
		b /= a;
		tmp++;
	}while(b > a && gcd(a, b) == a);
	if(a == b){return tmp;}
	return 0;
}
template<typename T>
constexpr int howpow(const T& a, const T& b){
	return _howpow<int>(a, b);
}
template<typename T, typename U>
string numtostr_with_notation(T a, const U& notation){
	static constexpr int alphabet = 'Z' - 'A' + 1;
	using MathConstexpr::abs;
	if(notation == 10){
		return to_string(a);
	}
	if(a == 0){
		return "0";
	}
	bool negative = false;
	#if __cpp_if_constexpr >= 201606
	if constexpr(is_signed_v<T>){
	#else
	if(is_signed<T>::value){
	#endif
		if(a < 0){
			negative = true;
			a = abs(a);
		}
	}
	list<string> l;
	do{
		T t = a % notation;
		if(notation >= 10 + alphabet || t < 10){
			l.push_front(to_string(t));
		}else if(t < 10 + alphabet){
			l.push_front(cts(static_cast<char>('A' + (t - 10))));
		}
		a /= notation;
	}while(a != 0);
	if(notation >= 10 + alphabet){
		return join("|", l);
	}
	return join("", l);
}
int count_char(const string& str, char c){
	int sol = 0;
	size_t pos = str.find(c);
	while(pos != string::npos){
		sol++;
		pos = str.find(c, pos + 1);
	}
	return sol;
}
string repeat_str(const string& str, size_t n){
	size_t size = str.length();
	string sol;
	sol.reserve(size * n);
	for(int i = 0;i < n;i++){
		sol.append(str);
	}
	return sol;
}
#ifdef __helper_warn__
#include "helper_warn.h"
#endif

#endif