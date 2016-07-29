#ifndef FORESTANZA_COMMON_FACTORY_H
#define FORESTANZA_COMMON_FACTORY_H

#include <functional>
#include <string>
#include <map>


// Universal factory 'make' wrapper
template <typename T>
T* new_maker() { return new T(); }

// Specialize by abstract ifc
template <typename T>
class MakeFactory
{
public:
    using string = std::string;
    using maker = std::function<T*()>;

    bool add(string const& key, maker const& f)
    {
        return map_.insert(std::make_pair(key, f)).second;
    }
    T* get(string const& key) const
    {
        auto it = map_.find(key);
        if (it == map_.end()) {
            return nullptr;
        }
        return (it->second)();
    }

private:
    std::map<string, maker> map_ = {};
};


// Singleton
template<typename T>
MakeFactory<T>&
factorySingleton() { static MakeFactory<T> factory; return factory; }


#endif // FORESTANZA_COMMON_FACTORY_H
