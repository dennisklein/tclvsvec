#include <memory>
#include <memory_resource>
#include <vector>

namespace fairroot {

template <typename T> struct stltca {
  using data_type = std::vector<std::unique_ptr<T>>;
  using size_type = typename data_type::size_type;
  using reference = T &;
  using const_reference = T const &;

  template <typename... Args> auto emplace_back(Args &&...args) -> reference {
    // C++20
    std::pmr::polymorphic_allocator<T> alloc{pool_};
    return *data_.emplace_back(
        alloc.template new_object<T>(std::forward<Args>(args)...),
        [=](T *p) { alloc.template delete_object<T>(p); });

    // C++17 allocator
    // std::pmr::polymorphic_allocator<T> alloc{pool_};
    // auto obj = alloc.allocate(1);
    // try {
    //   alloc.construct(obj, std::forward<Args>(args)...);
    // } catch (...) {
    //   alloc.deallocate(obj, 1);
    //   throw;
    // }
    // return *data_.emplace_back(obj, [=](T *p) {
    //   alloc.destroy(p);
    //   alloc.deallocate(p, 1);
    // });

    // C++17 memory_resource
    // auto obj = pool_.allocate(sizeof(T));
    // try {
    //   new (obj) T(std::forward<Args>(args)...);
    // } catch (...) {
    //   pool_.deallocate(obj, sizeof(T));
    //   throw;
    // }
    // return *data_.emplace_back(obj, [=](T *p) {
    //   p->~T();
    //   pool_.deallocate(p, sizeof(T));
    // });
  }

  auto at(size_type pos) -> reference { return *(data_.at(pos)); }
  auto at(size_type pos) const -> const_reference { return *(data_.at(pos)); }

private:
  std::pmr::unsynchronized_pool_resource pool_{{0, sizeof(T)}};
  data_type data_;
};

} // namespace fairroot
