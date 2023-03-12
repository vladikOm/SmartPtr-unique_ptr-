#pragma once
#define _NODISCARD [[nodiscard]] //Атрибут

#include <iostream>
#include <memory>

template<class T>
struct deleter
{
    constexpr deleter() noexcept = default;

    deleter(const deleter<T> &) noexcept  { }


    void operator()(T* ptr) const noexcept
    {
        if (ptr)
            std::cout << "I'm delete ptr" << std::endl;
        delete ptr;

    }
 
};

template<class T, class D = deleter<T>>
class Unique_ptr
{
private:
    T* m_pointer;
    D m_deleter;

public:
     
    constexpr Unique_ptr() noexcept :  m_pointer(nullptr)             //Коструктор за замовчуванням    
    {
        std::cout << "Unique_ptr()\n";
    }
    constexpr  Unique_ptr(nullptr_t) noexcept : m_pointer(nullptr) 
    {
         std::cout << "Unique_ptr(nullptr_t)\n";
    }
    
    explicit Unique_ptr(T* ptr) noexcept : m_pointer(ptr)             //Коструктор(ініціалізований явно) який приймає один параметр
      
    {
       std:: cout << "explicit Unique_ptr(T* ptr = nullptr)\n";
    }

  
    //// * Коструктора копії  unique_ptr не існує тому що тільки 1 вказівник вказує на об'єкт
  
    Unique_ptr(const Unique_ptr& obj) = delete;            // DELETED COPY CONSTRUCTOR

    Unique_ptr& operator=(const Unique_ptr& obj) = delete; // DELETED COPY ASSIGNMENT OPERATOR

   
   
    
    Unique_ptr(T* ptr, const D&del ) noexcept :
        m_pointer(ptr), m_deleter(del)                   
    {
        std::cout << "Unique_ptr(T* ptr, const D& del)\n";
    }

   Unique_ptr(T* ptr, D&& del) noexcept :                  //Тут ми передаємовказівник і  вказівник на функцію власну для видалення ()
        m_pointer(ptr), m_deleter(std::move(del))
    {
        std::cout << " Unique_ptr(T* ptr, D&& del)\n";
    }
   template<class U>
    Unique_ptr(Unique_ptr<U>&& other) noexcept :              //Конструктор переміщення передаємо посилання на об'єкт 
        m_pointer(other.release()), m_deleter(std::move(other.m_deleter)) 
    {
        std::cout << "Unique_ptr(Unique_ptr&& other)\n";
    }

     

    ~Unique_ptr() noexcept
    {
        m_deleter(m_pointer);
    }

   Unique_ptr& operator= (nullptr_t) noexcept
    {
        reset();
        return *this;
    }

    Unique_ptr& operator=(Unique_ptr&& other) noexcept
    {
        reset(other.release());
        m_deleter = std::move(other.m_deleter);
        return *this;
    }

    
    _NODISCARD T* get() const noexcept
    {
        return m_pointer;
    }

    _NODISCARD D& get_deleter() noexcept
    {
        return m_deleter;
    }

    _NODISCARD const D& get_deleter() const noexcept
    {
        return m_deleter;
    }

    _NODISCARD  explicit operator bool() const noexcept
    {
        return m_pointer != nullptr;
    }

    _NODISCARD T& operator*() const noexcept
    {
        return *m_pointer;
    }

    _NODISCARD T* operator->() const noexcept
    {
        return m_pointer;
    }

    T* release() noexcept
    {
        T* ptr = m_pointer;
        m_pointer = nullptr;
        return ptr;
    }

    void reset(T* ptr = nullptr) noexcept
    {
        T* tmp = m_pointer;
        m_pointer = ptr;
        m_deleter(tmp);
    }
};
