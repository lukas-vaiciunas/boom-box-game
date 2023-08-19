#pragma once

#include <vector>

template<typename T>
class Pool
{
public:
	typedef uint8_t Size;

	Pool(Size capacity);

	virtual ~Pool();

	bool isEmpty() const;
protected:
	std::vector<T *> objects_;
	Size capacity_;
	Size numLive_;

	void add_(T *object);
	void remove_(Size index);

	bool isFull_() const;
};

template<typename T>
Pool<T>::Pool(Size capacity) :
	objects_(capacity, nullptr),
	capacity_(capacity)
{}

template<typename T>
Pool<T>::~Pool()
{
	for (Size i = 0; i < numLive_; ++i)
	{
		delete objects_[i];
	}
}

template<typename T>
bool Pool<T>::isEmpty() const
{
	return numLive_ == 0;
}

template<typename T>
void Pool<T>::add_(T *object)
{
	objects_[numLive_++] = object;
}

template<typename T>
void Pool<T>::remove_(Size index)
{
	delete objects_[index];
	objects_[index] = objects_[--numLive_];
	objects_[numLive_] = nullptr;
}

template<typename T>
bool Pool<T>::isFull_() const
{
	return numLive_ >= capacity_;
} 