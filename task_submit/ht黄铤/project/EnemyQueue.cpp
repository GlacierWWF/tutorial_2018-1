#include "EnemyQueue.h"


template <typename T>EnemyQueue<T>::EnemyQueue()
{
	front=0;    
    rear=maxqueue-1;    
    count=0;   
}


template <typename T>EnemyQueue<T>::~EnemyQueue()
{;
}

template <typename T> Error_code EnemyQueue<T>::append(const T &item){    
    
    if (count >= maxqueue) return overflow;    
    count++;    
    rear=((rear+1)==maxqueue)? 0:(rear+1);    
    entry[rear]=item;    
    return success;    
    
}    
template <typename T> bool EnemyQueue<T>::empty()const{    
    if(count==0) return true;    
    else return false;    
}    
template <typename T> Error_code EnemyQueue<T>::retrieve(T &item) const{ 
    
    if(empty()== false){    
        item=entry[front];    
    }else return underflow;    
}    
template <typename T> Error_code EnemyQueue<T>::serve(){    
    
    if(count==0) return underflow;    
    front=(front==(maxqueue-1))?0:(front+1);    
    count--;    
    return success;    
}    
