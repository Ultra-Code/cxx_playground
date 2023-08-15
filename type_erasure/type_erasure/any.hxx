#include <iostream>
#include <string>
#include <utility>

// NOTE: The class name indicates the underlying type erasure technique

// this behaves like the Boost.Any type w.r.t. implementation details
class Any_Virtual
{
  struct holder_base
  {
    virtual ~holder_base() = default;
    [[nodiscard]] virtual auto
    clone() const -> holder_base * = 0;
  };

  template<class T> struct holder : holder_base
  {
    holder()
        : held_()
    {
    }

    explicit holder(T t)
        : held_(std::move(t))
    {
    }

    ~holder() override = default;

    [[nodiscard]] auto
    clone() const -> holder_base * override
    {
      return new holder<T>(*this);
    }

    T held_;
  };

public:
  Any_Virtual() = default;

  Any_Virtual(Any_Virtual const &other)
      : storage_(other.storage_->clone())
  {
  }

  template<class T>
  explicit Any_Virtual(T const &t)
      : storage_(new holder<T>(t))
  {
  }

  ~Any_Virtual() { Clear(); }

  auto
  operator=(Any_Virtual const &other) -> Any_Virtual &
  {
    Clear();
    storage_ = other.storage_->clone();
    return *this;
  }

  template<class T>
  auto
  operator=(T const &t) -> Any_Virtual &
  {
    Clear();
    storage_ = new holder<T>(t);
    return *this;
  }

  void
  Clear()
  {
    delete storage_;
  }

  template<class T>
  auto
  As() -> T &
  {
    return static_cast<holder<T> *>(storage_)->held_;
  }

private:
  holder_base *storage_{};
};

// the following demonstrates the use of void pointers
// and function pointers to templated operate functions
// to safely hide the type

enum Operation
{
  CopyTag,
  DeleteTag
};

template<class T>
void
Operate(void *const &in, void *&out, Operation op)
{
  switch (op)
    {
    case CopyTag:
      out = new T(*static_cast<T *>(in));
      return;
    case DeleteTag:
      delete static_cast<T *>(out);
    }
}

class Any_VoidPtr
{
public:
  Any_VoidPtr() = default;

  Any_VoidPtr(Any_VoidPtr const &other)
      : operate_(other.operate_)
  {
    if (other.object_ != nullptr)
      {
        operate_(other.object_, object_, CopyTag);
      }
  }

  template<class T>
  explicit Any_VoidPtr(T const &t)
      : object_(new T(t))
      , operate_(&Operate<T>)
  {
  }

  ~Any_VoidPtr() { Clear(); }

  Any_VoidPtr &
  operator=(Any_VoidPtr const &other)
  {
    Clear();
    operate_ = other.operate_;
    operate_(other.object_, object_, CopyTag);
    return *this;
  }

  template<class T>
  auto
  operator=(T const &t) -> Any_VoidPtr &
  {
    Clear();
    object_ = new T(t);
    operate_ = &Operate<T>;
    return *this;
  }

  void
  Clear()
  {
    if (object_ != nullptr)
      {
        operate_(nullptr, object_, DeleteTag);
      }
    object_ = nullptr;
  }

  template<class T>
  auto
  As() -> T &
  {
    return *static_cast<T *>(object_);
  }

private:
  using OperateFunc = void (*)(void *const &, void *&, Operation);

  void *object_{};
  OperateFunc operate_{};
};
