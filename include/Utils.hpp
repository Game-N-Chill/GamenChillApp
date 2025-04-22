
#pragma once

#include <iostream>
#include <memory>
#include <mutex>

namespace Utils
{

template <typename T>
T getRandom(T max)
{
    if (max <= 0)
        return 0;

    std::mt19937_64 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<long long> distribution(0, max - 1);

    T nbr = (T)distribution(gen);
    return (nbr % max);
}

template <typename T>
class Singleton
{
    public:
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;

        static T *getInstance()
        {
            std::call_once(_flag, []() {
                _instance = new T();
            });
            return _instance;
        }

        static void destroyInstance()
        {
            std::lock_guard<std::mutex> lock(_mutex);

            if (_instance == nullptr)
                return;

            delete _instance;
            _instance = nullptr;
        }

    protected:
        Singleton() = default;
        virtual ~Singleton() = default;

    private:
        static T* _instance;
        static std::once_flag _flag;
        static std::mutex _mutex;
};

template <typename T>
T* Singleton<T>::_instance = nullptr;

template <typename T>
std::once_flag Singleton<T>::_flag;

template <typename T>
std::mutex Singleton<T>::_mutex;


} // namespace Utils
