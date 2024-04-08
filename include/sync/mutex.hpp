#pragma once
#include <algorithm>
#include <memory>
#include <mutex>
#include <utility>

namespace pva {

template <typename T>
class mutex_guard {
 private:
  using lock_type = std::scoped_lock<std::mutex>;

 public:
  explicit mutex_guard(T &res, std::mutex &mtx) : _lock_{mtx}, _res_{res} {}

  auto operator*() const -> T & { return _res_; }
  auto operator->() const -> T * { return &_res_; }

  mutex_guard() = delete;
  mutex_guard(const mutex_guard &) = delete;
  mutex_guard(mutex_guard &&) = delete;

  auto operator=(const mutex_guard &) -> mutex_guard & = delete;
  auto operator=(mutex_guard &&) -> mutex_guard & = delete;

  ~mutex_guard() noexcept = default;

 private:
  lock_type _lock_;
  T &_res_;
};

template <class T>
class mutex {
 private:
  using resource_type = std::unique_ptr<T>;

 public:
  explicit mutex(T &&res) : _data_{std::make_unique<T>(std::move(res))} {}
  auto lock() const -> mutex_guard<T> {
    return mutex_guard<T>{*_data_, _mutex_};
  }

 private:
  mutable std::mutex _mutex_;
  resource_type _data_;
};

}  // namespace pva
