#include <iostream>
#include <sync/mutex.hpp>
#include <thread>

struct Toy {
  void play() {
    std::cout << "Thread: " << std::this_thread::get_id()
              << " playing with a toy\n";
  }
};

int main([[maybe_unused]] const int argc,
         [[maybe_unused]] const char* const* const argv) {
  using pva::mutex;
  mutex m{Toy{}};

  auto play_with_toy = [](mutex<Toy>& toy) {
    constexpr int LOOP_COUNT{8};
    for (auto i = 0; i < LOOP_COUNT; ++i) {
      {
        auto lock = toy.lock();
        lock->play();
      }
      std::this_thread::sleep_for(std::chrono::milliseconds{500});
    }
  };

  std::thread t1{play_with_toy, std::ref(m)};
  std::thread t2{play_with_toy, std::ref(m)};

  t1.join();
  t2.join();

  return 0;
}
