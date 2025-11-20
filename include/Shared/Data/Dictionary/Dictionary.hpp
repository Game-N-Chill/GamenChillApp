
#pragma once

#include <iostream>
#include <list>
#include <algorithm>
#include <GoGuLib.hpp>

#include "Shared/Data/Dictionary/Background.hpp"
#include "Shared/Data/Dictionary/Character.hpp"

namespace GNCApp::Data
{

template<typename U>
class Dictionary : public  GGL::Singleton<Dictionary<U>>
{
    public:
        void load(void (*loadFunc)(std::list<U> &))
        {
            loadFunc(_list);
        }

        void print()
        {
            for (auto &it : _list) {
                Log() << it << GGL::end;
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
        friend class  GGL::Singleton<Dictionary<U>>;
        Dictionary() = default;

        std::list<U> _list;
};

typedef Dictionary<BackgroundMKWorld>   DictBackgroundMKWorld;
typedef Dictionary<BackgroundMK8>       DictBackgroundMK8;
typedef Dictionary<Character>           DictCharacter;

} // namespace GNCApp::Data
