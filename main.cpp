// task_7_bulk.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <thread>

#include "async.h"

using namespace std;

void recv_th(async::handle_t h)
{
    while (1)
    {
        //getline(cin, cmd);
        //async::receive(h, cmd.c_str(), cmd.length());
        async::receive(h, "1\n2\n3\n4\n5\n", sizeof("1\n2\n3\n4\n5\n"));
        //_sleep(4);
    }
}

int main(int argc, char* argv[])
{
    auto h = async::connect(5);

    string cmd;
    
    //thread th = thread(recv_th, h);
    size_t counter = 7;

    while (counter--)
    {
        getline(cin, cmd);
        async::receive(h, cmd.c_str(), cmd.length());
    }

    async::disconnect(h);

    /*
    std::size_t bulk = 5;
    auto h = async::connect(bulk);
    auto h2 = async::connect(bulk);
    async::receive(h, "1", 1);
    async::receive(h2, "1\n", 2);
    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);
    async::disconnect(h);
    async::disconnect(h2);
    */

    return 0;
}