//
//  main.cpp
//  BaseTest
//
//  Created by TYY on 2019/4/14.
//  Copyright © 2019 ZXHY. All rights reserved.
//
#include <type_traits>
#include <iostream>
#include "base/rand_util.h"
#include "base/at_exit.h"
#include "base/bind.h"
#include "base/base_time.h"
#include "base/linked_list.h"

void exit_first(void * ptr)
{
    std::cout << "first" << ptr << std::endl;
}

void exit_second(void * ptr)
{
    std::cout << "second" << ptr << std::endl;
}

void exit_task(void *data)
{
    std::cout<< "user bind"<< std::endl;
}

class Task
{
public:
    void Fun(){
        std::cout << "Task::Func" << std::endl;
    }
};


class Node : public base::LinkNode<Node>
{
public:
    
    explicit Node(int id) : id_(id) {}
    
    int id() const { return id_; }
    
private:
    
    int id_;
};


int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    std::cout << "-----------------base::AtExitManager Test-------------"<< std::endl;
    base::AtExitManager manager;

    base::AtExitManager::RegisterCallback(&exit_first, nullptr);
    base::AtExitManager::RegisterCallback(&exit_second, nullptr);
    
    Task task;
    base::AtExitManager::RegisterTask(base::Bind(&exit_task, nullptr));
    base::AtExitManager::RegisterTask(base::Bind(&Task::Fun, base::Unretained(&task)));

    base::AtExitManager::ProcessCallbacksNow();
    
    std::cout << "-----------------base::RandInt Test-------------"<< std::endl;
    int randvalue =base::RandInt(1,100);
    randvalue ++;
    std::cout << "randvalue is "<< randvalue <<std::endl;
 
    
    std::cout << "-----------------base::Time Test-------------"<< std::endl;
    base::Time time = base::Time::Now();
    std::cout << "now time is "<< time.is_null()<<std::endl ;// << "." << exploded.month << "." << exploded.day_of_month << " "\
    //<< exploded.hour <<":"<<exploded.minute <<":" <<exploded.second << std::endl;
    
    std::cout << "-----------------base::LinkedList Test-------------"<< std::endl;
    base::LinkedList<Node> list;
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);
    list.Append(&n1);
    list.Append(&n2);
    list.Append(&n3);
    list.Append(&n4);
    list.Append(&n5);
    
    n3.RemoveFromList();
    printf("\n1-----\n");
    for (const base::LinkNode<Node>* node = list.head(); node != list.end(); node = node->next() )
    {
        printf("id = %d," ,node->value()->id() );
    }
    list.Append(&n3);
    printf("\n2-----\n");
    for (const base::LinkNode<Node>* node = list.head(); node != list.end(); node = node->next() )
    {
        printf("id = %d," ,node->value()->id() );
    }
    n3.InsertBefore(&n2);
    printf("\n3-----\n");
    for (const base::LinkNode<Node>* node = list.head(); node != list.end(); node = node->next() )
    {
        printf("id = %d," ,node->value()->id() );
    }
    n4.InsertAfter(&n1);
    printf("\n4-----\n");
    for (const base::LinkNode<Node>* node = list.head(); node != list.end(); node = node->next() )
    {
        printf("id = %d," ,node->value()->id() );
    }
    
    printf("\n5-----\n");
    for (const base::LinkNode<Node>* node = list.tail(); node != list.end(); node = node->previous() )
    {
        printf("id = %d," ,node->value()->id() );
    }
    
    std::cout << "-----------------base:: Test-------------"<< std::endl;
    
    std::cout << "Hi MAC OS, See you later"<< std::endl;
    return 0;
}
