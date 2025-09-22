
#pragma once

#include <iostream>
#include <list>
#include <algorithm>

#include "Data/Dictionary/Background.hpp"
#include "Data/Dictionary/Character.hpp"
#include "Utils.hpp"

namespace GNCApp::Data
{

template<typename U>
class Dictionary : public Utils::Singleton<Dictionary<U>>
{
    public:
        void load(void (*loadFunc)(std::list<U> &))
        {
            loadFunc(_list);
        }

        void print()
        {
            for (auto &it : _list) {
                std::cout << it << std::endl;
            }
        }


        size_t size() const
        {
            return _list.size();
        }

        std::list<std::string> list() const
        {
            std::list<std::string> list;
            for (auto &it : _list) {
                list.push_back(static_cast<std::string>(it));
            }

            return list;
        }


        U find(U key)
        {
            auto it = std::find(_list.begin(), _list.end(), key);
            if (it == _list.end()) {
                throw std::out_of_range("can't find dictionnary element");
            }
            return *it;
        }

        U find(std::string key)
        {
            auto it = std::find(_list.begin(), _list.end(), key);
            if (it == _list.end()) {
                throw std::out_of_range("can't find dictionnary element");
            }
            return *it;
        }

        U find(size_t key)
        {
            if (key >= _list.size()) {
                throw std::out_of_range("index exceed dictionary size");
            }

            auto it = _list.begin();
            std::advance(it, key);
            return *it;
        }

    private:
        friend class Utils::Singleton<Dictionary<U>>;
        Dictionary() = default;

        std::list<U> _list;
};

typedef Dictionary<BackgroundMKWorld>   DictBackgroundMKWorld;
typedef Dictionary<BackgroundMK8>       DictBackgroundMK8;
typedef Dictionary<Character>           DictCharacter;

} // namespace GNCApp::Data
