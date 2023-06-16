#include "Lithe/Core/Assert.hpp"

namespace Lithe
{
    template<class T>
    class Singleton
    {
    public:
        static T& GetInstance()
        {
            if (!Singleton::s_Instance)
                Singleton::s_Instance = createInstance();
            return *Singleton::s_Instance;
        }

    protected:
        explicit Singleton()
        {
            LITHE_CORE_ASSERT(!Singleton::s_Instance, "Singleton instance already exists");
            Singleton::s_Instance = static_cast<T*>(this);
        }

        ~Singleton()
        {
            Singleton::s_Instance = 0;
        }

        static T* createInstance() { return new T(); }
    private:
        static T* s_Instance;

        explicit Singleton(const Singleton&) {}
        Singleton& operator=(const Singleton&) { return *this; }

    };

    template<class T>
    T* Singleton<T>::s_Instance = 0;
}