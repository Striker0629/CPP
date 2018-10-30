#ifndef STACK_H
#define STACK_H
#include<cstdlib>
#include<algorithm>
#include<iostream>



template<typename T>
class Stack final
{
    using ptr=T*;
    using ref=T&;
    using val=T;
    inline ptr Allocate(size_t size)
    {
        return new T[size];
    }

    void Reallocate()
    {

            //size_t old_size=reserved_;
            auto buf=Allocate(reserved_);
            std::copy(data_,data_+size_,buf);
            delete[] data_;
            auto new_reserved=reserved_+(reserved_*1.25);
            data_=Allocate(new_reserved);
            std::copy(buf,buf+size_,data_);
            reserved_=new_reserved;
            delete[]buf;

    }

public:
    explicit Stack()noexcept:data_{nullptr},size_{0},head_{0}
    {

    }
    explicit Stack(size_t reserved):size_{0},head_{0},reserved_{reserved}
    {
        data_=new T[reserved_];
    }
    Stack(const Stack&copy):size_{copy.size_},head_{copy.head_},reserved_{copy.reserved_}
    {
        data_=new T[size_];

        std::copy(copy.data_,copy.data_+copy.size_,data_);

    }
    Stack(Stack&&move)noexcept:size_{move.size_},head_{move.head_},data_{move.data_},reserved_{move.reserved_}
    {
        move.data_=nullptr;
        move.size_=0;
        move.reserved_=0;
    }
    inline bool IsEmpty()const
    {
        return size_==0;
    }

    inline val Top()const
    {
        return data_[size_-1];
    }
    Stack& operator=(const Stack& right)
    {
        auto temp{right};
        Swap(*this,temp);
        
        return *this;
    }


    inline friend void Swap(Stack& lhs,Stack&rhs)noexcept
    {
        using std::swap;
        swap(lhs.data_,rhs.data_);
        swap(lhs.reserved_,rhs.reserved_);
        swap(lhs.head_,rhs.head_);
        swap(lhs.size_,rhs.size_);

    }
    void Push(const T&value)
    {
        if(data_==nullptr)
        {
            reserved_=3;
            data_=Allocate(reserved_);


        }
        else if(size_==reserved_)
        {
               Reallocate();
        }

        data_[size_]=value;
	++size_;
    }
    inline size_t Size()const
    {
        return size_;
    }
    void Pop()
    {
        --size_;
    }
    void Resize(const size_t value)
    {
        size_=value;
    }
    void ShrinkToFit()
    {
            auto copy=Allocate(size_);
            std::copy(data_,data_+size_,copy);
            delete [] data_;
            
            data_=Allocate(size_);
            std::copy(copy,copy+size_,data_);
            reserved_=size_;
            delete[]copy;
    }
    ~Stack() noexcept
    {
        delete[]data_;
    }



private:
    T* data_;
    size_t size_;
    size_t head_;
    size_t reserved_;

};

#endif // STACK_H
