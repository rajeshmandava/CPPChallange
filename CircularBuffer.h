#include <stddef.h>
#include <vector>

template <class T>
class CircularBuffer final{
private:
  CircularBuffer() = delete;
  typedef CircularBufferIterator<T> const_iterator; 
  size_t nextPosition()
  {
    return size == 0 ? 0 :(head+1) % data.size();
  }
  size_t  firstPosition()
  {
    return size == 0 ? 0 : (head+data.size()-size+1)%data.size();
  }
public:
  explicit CircularBuffer(const size_t s):size{s}
  {}
  bool empty() {return size == 0;}
  bool full() {return size == data.size();}
  size_t getSize() {return size;}
  size_t capacity() {return data.size();}
  bool clear()
  {
    head = -1;
    size = 0;
  }
  void push(const T element)
  {
    head = nextPosition();
  }
  T pop()
  {
    if(empty())
    throw std::runtime_error("Empty Buffer");
    auto curr = firstPosition();
    size--;
    return data[curr];
  }
private:
  std::vector<T> data;
  size_t head{-1}
  size_t size{0};
  size_t MAX_SIZE{100};
  friend class CicrularBufferIterator<T>;
};

template <class T>
class CircularBufferIterator
{
  typedef CircularBufferIterator selfType;
  typedef T valueType;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* pointer;
  typedef std::random_access_iterator_tag iteratorType;
  typedef ptrdiff_t differeneType;
  
  bool compatible(selfType const& other) const
  {
    return &buffer == &other.buffer;
  }

public:
  CircularBufferIterator(CircularBuffer<T> const& buf, size_t const curr, 
                         size_t const l):buffer(buf),index(curr),last(l)
  {}

  selfType& operator++()
  {
    if(last)
    throw std::out_of_range("End of range reached");
    index = (index+1) % buffer.data.size();
    last = index == buffer.nextPosition();
    return *this;
  }   

  selfType operator++(int) 
  {
    selfType tmp = *this;
    ++*this;
    return tmp;
  }

  bool operator==(selfType const& other) const
  {
    assert(compatible(other));
    return index == other.index && last == other.last;
  }

  bool operator!=(selfType const& other) const
  {
    return!(*this == other);
  }

  const_reference operator*() const
  {
    return buffer.data[index];
  }

  const_reference operator->() const
  {
    return buffer.data[index];
  }
  

private:                  
  CircularBuffer<T> const& buffer;
  size_t index;
  bool last;

};