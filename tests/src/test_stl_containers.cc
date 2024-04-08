#include <list>
#include <random>
#include <sync/mutex.hpp>
#include <thread>
#include <unordered_map>
#include <vector>

using Vec = std::vector<int32_t>;
using List = std::list<int32_t>;
using UMap = std::unordered_map<int32_t, std::string>;

template <typename T>
auto feed_container(T& container) -> std::enable_if_t<std::is_same_v<T, UMap>, void> {
  std::mt19937 ENG;
  constexpr int32_t UPPER_BOUND{8192};
  std::uniform_int_distribution<int32_t> gen(1, UPPER_BOUND);
  auto rand_num = gen(ENG);
  container.insert({rand_num, std::to_string(rand_num)});
}

template <typename T>
auto feed_container(T& container) -> std::enable_if_t<!std::is_same_v<T, UMap>, void> {
  typename T::value_type value{};
  container.push_back(value);
}

template <typename T>
void feed_loop(const pva::mutex<T>& container) {
  constexpr size_t LOOP_CNT{10};
  for (auto i = size_t{0}; i < LOOP_CNT; ++i) {
    auto lock = container.lock();
    feed_container(*lock);
  }
}

template <typename T>
void spawn() {
  pva::mutex m{T{}};
  std::thread t1{feed_loop<T>, std::cref(m)};
  std::thread t2{feed_loop<T>, std::cref(m)};

  t1.join();
  t2.join();
}

auto main([[maybe_unused]] const int argc,
         [[maybe_unused]] const char* const* const argv) -> int {
  using pva::mutex;

  spawn<Vec>();
  spawn<List>();
  spawn<UMap>();

  return 0;
}
