// task_7_bulk.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <thread>

#include "async.h"

using namespace std;

void recv_th(async::handle_t h)
{
    size_t counter = 20;

    while (counter--)
    {
        //getline(cin, cmd);
        //async::receive(h, cmd.c_str(), cmd.length());
        async::receive(h, "1\n2\n3\n4\n5\n", sizeof("1\n2\n3\n4\n5\n"));
    }
}

int main()
{
    /*
    auto h = async::connect(5);
    
    thread th = thread(recv_th, h);
    th.join();

    async::disconnect(h);
    */
   
    std::size_t bulk = 5;
    auto h = async::connect(bulk);
    auto h2 = async::connect(bulk);
    async::receive(h, "1", 1);
    async::receive(h2, "1\n", 2);
    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);
    async::disconnect(h);
    async::disconnect(h2);
    
    return 0;
}