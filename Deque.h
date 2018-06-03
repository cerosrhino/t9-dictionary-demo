#pragma once

#include <stdexcept>

template <typename T>
class Deque
{
private:
    const int ARRAY_SIZE = 1 << 20; // 1048576
    T* array;
    int _tail;
    int _head;
    int _size;

    void copy(const Deque& other)
    {
        _tail = other._tail;
        _head = other._head;
        _size = other._size;

        for (int i = 0; i < _size; i++) {
            int index = (_tail + i) % ARRAY_SIZE;
            array[index] = other.array[index];
        }
    }

public:
    Deque() : _tail(0), _head(0), _size(0)
    {
        array = new T[ARRAY_SIZE];
    }

    Deque(const Deque& other) : Deque()
    {
        copy(other);
    }
    
    ~Deque()
    {
        delete[] array;
    }

    Deque& operator=(Deque other)
    {
        copy(other);
    }
    
    void push_front(T x)
    {
        if (_size >= ARRAY_SIZE) {
            throw std::out_of_range("Brak miejsca w tablicy");
        }
        
        if (_size == 0) {
            _tail = _head = 0;
            array[_head] = x;
        } else {
            _head = (_head + ARRAY_SIZE + 1) % ARRAY_SIZE;
            array[_head] = x;
        }

        _size++;
    }
    
    T pop_front()
    {
        if (_size == 0) {
            throw std::out_of_range("Kolejka jest pusta");
        }
        
        T value = array[_head];
        _head = (_head + ARRAY_SIZE - 1) % ARRAY_SIZE;
        
        _size--;
        
        return value;
    }

    T& head()
    {
        return array[_tail];
    }
    
    void push_back(T x)
    {
        if (_size >= ARRAY_SIZE) {
            throw std::out_of_range("Brak miejsca w tablicy");
        }
        
        if (_size == 0) {
            _tail = _head = 0;
            array[_tail] = x;
        } else {
            _tail = (_tail + ARRAY_SIZE - 1) % ARRAY_SIZE;
            array[_tail] = x;
        }
        
        _size++;
    }
    
    T pop_back()
    {
        if (_size == 0) {
            throw std::out_of_range("Kolejka jest pusta");
        }
        
        T value = array[_tail];
        _tail = (_tail + ARRAY_SIZE + 1) % ARRAY_SIZE;
        
        _size--;
        
        return value;
    }

    T& back()
    {
        return array[_head];
    }

    int size()
    {
        return _size;
    }

    bool empty()
    {
        return _size == 0;
    }
};
