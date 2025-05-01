#pragma once

#include <string>
using namespace std;

// https://en.cppreference.com/w/cpp/container/priority_queue

typedef enum message_type {
    CREATE_TOPIC,
    SUBSCRIBE,
    PUBLISH
} MESSAGE_TYPE;

typedef struct message_ {
    MESSAGE_TYPE type;
    string topic_name;
    int priority;
    string content;
} Message;

typedef struct customComparator {
    bool operator()(const Message l, const Message r) const { return l.priority > r.priority; }
} MessageComparator;