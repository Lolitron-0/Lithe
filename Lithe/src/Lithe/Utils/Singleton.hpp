#include "Lithe/Core/Assert.hpp"

namespace Lithe
{
    template<class T>
    class Singleton
    {
    public:
        explicit Singleton()
        {
            LITHE_CORE_ASSERT(!Singleton::instance_);
            Singleton::instance_ = static_cast<T*>(this);
        }

    protected:

        ~Singleton()
        {
            Singleton::instance_ = 0;
        }

        T& GetInstance()
        {
            if (!Singleton::instance_)
                Singleton::instance_ = createInstance();
            return Singleton::instance_;
        }

        virtual T* createInstance() { return new T(); }
    private:
        static T* instance_;

        explicit Singleton(const Singleton&) {}
        Singleton& operator=(const Singleton&) { return *this; }

    };

    template<class T>
    T* Singleton<T>::instance_ = 0;
}