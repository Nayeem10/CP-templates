//#pragma GCC optimize("Ofast")
//#pragma GCC optimization ("O3")
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
//find_by_order(k) --> returns iterator to the kth largest element counting from 0
//order_of_key(val) --> returns the number of items in a set that are strictly smaller than our item
os.erase (os.find_by_order (os.order_of_key(v[i]))) //to erase i-th element from ordered multiset
template <typename DT> 
using ordered_set = tree <DT, null_type, less<DT>, rb_tree_tag,tree_order_statistics_node_update>;
struct custom_hash {  static uint64_t splitmix64 (uint64_t x) {    x += 0x9e3779b97f4a7c15;    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;    return x ^ (x >> 31);  }  size_t operator () (uint64_t x) const {    static const uint64_t FIXED_RANDOM = chrono::steady_clock :: now ().time_since_epoch ().count ();    return splitmix64 (x + FIXED_RANDOM);  }} Rng;
typedef gp_hash_table<int, int, custom_hash> gp;

int leap_years(int y) { return y / 4 - y / 100 + y / 400; }bool is_leap(int y) { return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0); }bool __builtin_mul_overflow (type1 a, type2 b, type3 &res)cin.tie(0)->ios_base::sync_with_stdio(0);int getWeekday (int day, int month, int year) {  if (month <= 2) {    month += 12;    year -= 1;  }  int f = (day + (13 * (month + 1)) / 5 + year + year / 4 - year / 100 + year / 400) % 7;  return f;}
