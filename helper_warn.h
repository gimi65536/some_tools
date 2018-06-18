/* Reference:
https://zhuanlan.zhihu.com/p/24835482
https://zhuanlan.zhihu.com/p/24910829
https://zhuanlan.zhihu.com/p/24928414
https://segmentfault.com/n/1330000008559854
*/
namespace StaticCounter{
	//Init as float cannot be template argument
	template<typename CounterLabel, typename T, T Init = 0>
	class Counter{
	private:
		template<T N>
		struct Flag_type{
			friend constexpr T flag(Flag_type<N>);
			static constexpr T n = N;
		};
		template<T N>
		struct Flag_writer{
			friend constexpr T flag(Flag_type<N>){
				return N;
			}
			static constexpr T n = N;
		};
		template<T N, T = flag(Flag_type<N>{})>
		static constexpr T Flag_finder(T, Flag_type<N>, T sol = Flag_finder(N + 1, Flag_type<N + 1>{})){
			return sol;
		}
		template<T N>
		static constexpr T Flag_finder(float, Flag_type<N>, T sol = Flag_writer<N>::n){
			return sol;
		}
		template<T N, T = flag(Flag_type<N>{})>
		static constexpr T currentFlag(T, Flag_type<N>, T sol = currentFlag(N + 1, Flag_type<N + 1>{})){
			return sol;
		}
		template<T N>
		static constexpr T currentFlag(float, Flag_type<N>, T sol = Flag_type<N - 1>::n){
			return sol;
		}
	public:
		template<T N = Init>
		static constexpr T next(T sol = Flag_finder(N, Flag_type<N>{})){
			return sol;
		}
		template<T N = Init>
		static constexpr T current(T sol = currentFlag(N, Flag_type<N>{})){
			return sol;
		}
	};
}