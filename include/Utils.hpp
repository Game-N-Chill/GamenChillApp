
#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <random>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Utils
{

class Randomizer
{
    public:
        Randomizer()
        {
            this->_seed = nullptr;
            UnsetSeed();
        }

        Randomizer(size_t seed)
        {
            SetSeed(seed);
        }

        ~Randomizer() = default;

        void UnsetSeed()
        {
            this->_gen.seed(this->_rd());
            this->_seed.reset();
        }

        void SetSeed(size_t seed)
        {
            if (this->_seed == nullptr) {
                this->_seed = std::make_unique<size_t>(seed);
            } else {
                *this->_seed = seed;
            }
            this->_gen.seed(*this->_seed);
        }

        size_t GetSeed() const
        {
            return *this->_seed;
        }

        template <typename T>
        T GetRandomInRange(T min, T max)
        {
            static_assert(std::is_integral<T>::value, "T must be an integral");

            if (min > max) {
                std::swap(min, max);
            }

            std::uniform_int_distribution<T> dist(min, max);
            return dist(this->_gen);
        }

        template <typename T>
        T GetRandom(T max)
        {
            static_assert(std::is_integral<T>::value, "T must be an integral");

            std::uniform_int_distribution<T> dist;
            return dist(this->_gen) % max;
        }

    private:
        std::mt19937_64 _gen;
        std::random_device _rd;
        std::unique_ptr<size_t> _seed;
};

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

std::string getTimeFormat(std::string format);
std::string stringToUpper(std::string str);
std::string getCompleteName(std::string name, json &tags);
std::string getFullPath(std::string path);;
void createProcess(std::string path);

} // namespace Utils
