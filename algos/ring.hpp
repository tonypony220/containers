/// размер буфера - должен быть степенью двойки,
template<int SIZE, class T = unsigned char>
class RingBuffer {
	static_assert((SIZE & (SIZE-1)) == 0, "size of ring buffer must be power of 2!" );
 public:
	typedef uint16t 		 index_type;
 private:
	T 			     	 	 data[SIZE];
	volatile index_type      readCount;
	volatile index_type 	 writeCount;
	static const index_type  mask = SIZE - 1;
 public:
	bool Write(T value) {
		if(IsFull())
			return false;
		data[writeCount++ & mask] = value;
		return true;
	}

	bool Read(T & value) {
		if(IsEmpty())
			return false;
		value = data[readCount++ & mask];
		return true;
	}

	T First() const { return operator[](0); }

	T Last()  const { return operator[](Count()); }

	T& operator[] (index_type i)
	{
		if(IsEmpty() || i > Count())
			return T();
		return data[(readCount + i) & mask];
	}

	const T operator[] (index_type i)const
	{
		if(IsEmpty())
			return T();
		return data[(readCount + i) & mask];
	}

	bool IsEmpty()const { return writeCount == readCount; }

	bool IsFull() const {
		index_type diff  = (writeCount - readCount);
		return ( diff & static_cast<index_type>(~mask)) != 0;
	}

	index_type Count()const { return (writeCount - readCount) & mask; }

	void Clear() {
		readCount=0;
		writeCount=0;
	}
};