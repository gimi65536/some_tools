#include <type_traits>
#include <vector>
#include <map>
using namespace std;

template <typename T>
using expr_type = remove_cv_t<remove_reference_t<T>>;
template <typename T, typename U, typename ...Args>
struct is_contain_first : bool_constant<is_same_v<expr_type<T>, expr_type<U>> || is_contain_first<expr_type<T>, Args...>::value>{};
template <typename T, typename U>
struct is_contain_first<T, U> : bool_constant<is_same_v<expr_type<T>, expr_type<U>>>{};

template<typename C>
void total_size_helper(size_t& sol, const C& c1){
	sol += c1.size();
}
template<typename C, typename ...Containers>
void total_size_helper(size_t& sol, const C& c1, const Containers&... cs){
	sol += c1.size();
	total_size_helper(sol, cs...);
}

template<typename ...Containers>
size_t total_size(const Containers&... cs){
	size_t sol = 0;
	total_size_helper(sol, cs...);
	return sol;
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
	concatsv_helper(sol, vs...);
	return sol;
}
template<typename R, typename S, typename T, typename U>
void concatsm_helper(map<R, S>& sol, const map<T, U>& m){
	for(const auto& [key, value] : m){
		sol[key] = value;
	}
}
template<typename R, typename S, typename T, typename U, typename ...Maps>
void concatsm_helper(map<R, S>& sol, const map<T, U>& m1, const Maps&... ms){
	for(const auto& [key, value] : m1){
		sol[key] = value;
	}
	concatsm_helper(sol, ms...);
}
template<typename ...Maps>
auto concatsm(const Maps&... ms){
	map<common_type_t<typename Maps::key_type...>, common_type_t<typename Maps::mapped_type...>> sol;
	concatsm_helper(sol, ms...);
	return sol;
}
template<typename T, typename U>
vector<T> keys(const map<T, U>& m){
	vector<T> sol;
	sol.reserve(m.size());
	for(const auto& [key, value] : m){
		sol.push_back(key);
	}
	return sol;
}
template<typename T, typename U>
vector<U> values(const map<T, U>& m){
	vector<U> sol;
	sol.reserve(m.size());
	for(const auto& [key, value] : m){
		sol.push_back(value);
	}
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