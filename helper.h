#include <type_traits>
#include <vector>
#include <map>
using namespace std;

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
template<typename T>
string join(string sep, const vector<T>& v){
	string sol;
	for(int i = 0;i < v.size();i++){
		if(i > 0){
			sol += sep;
		}
		sol += v[i];
	}
	return sol;
}