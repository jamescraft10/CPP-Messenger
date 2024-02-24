# C++ Server

TODO:
theres a bug that looks like this and idk where its coming from
```
jamescraft@James:~/Programming/CPP-Server$ make
g++ -o server src/server.cpp
./server
Server is running on
        http://localhost:3002/
        http://127.0.0.1:3002/
        http://example.com:3002/
terminate called after throwing an instance of 'std::out_of_range'
  what():  basic_string::substr: __pos (which is 18446744073709551611) > this->size() (which is 0)
make: *** [makefile:2: all] Aborted
```

## what this does
so the code is going to served on a port which is connected to and our server (server.cpp) is going to have a api so with fetch and js on the front end then can be a libary thats going to be used as a replacement for socket io

## socket io thing:

### client:
every second check for fetch at an example path (api/chat.json) w/post
chat.json will contain a msg and a state of a bool witch is 1 or 0
so if the fetch is 1 and the last one saved in memory is 1 then it does nothing
if the fetch is 0 then we do something with the data passed (could be string or json)
we can send a fetch to another example path (api/send/chat) to send the latest message in api/chat.json

### server:
when a post req is sent to an example path (api/chat.json) we send the response for the client to do the work
when a client sends a request to another example path (api/send/chat) we flip the current changed bit and replace the data with whats sent
after that the client should handle the rest.

also dont use the file system during this only use it to save msgs when you get there
