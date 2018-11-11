#pragma once
#include"Enemy.h"
using namespace std;  
const int maxqueue = 15;
//

const int max=maxqueue;
enum Error_code{success,underflow,overflow};  
template <class  T>class EnemyQueue
{
public:
	EnemyQueue();
	~EnemyQueue();    
    bool empty() const;    
    Error_code serve();    
    Error_code append(const 
		T &item);  
    Error_code retrieve(T &item) const;
protected:    
    int count;    
    int front,rear;    
    T entry[maxqueue];    

};

