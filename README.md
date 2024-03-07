# C++ Server

TODO:
do the socket io thing;

## what this does
so the code is going to served on a port which is connected to and our server (server.cpp) is going to have a api so with fetch and js on the front end then can be a libary thats going to be used as a replacement for socket io

## socket io thing:
### socket io thing is done now i make it real time msging app

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

for the server theres going to be a file thats edited to a json when it gets responsed and its going to store the data of chat.json
its going to be called chat.data and its going to look like this
```
message0
```
so its going to be read like this
```cpp
// data is chat.data's data
// we keep everything as a string so its easyier to responsed
char state = data[data.length()-1];
data.pop_back();
std::string msg = data;
```