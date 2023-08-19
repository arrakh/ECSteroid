//
// Created by Arya Rakha on 6/8/2023.
//

#ifndef CMAKESFMLPROJECT_EVENTSYSTEM_H
#define CMAKESFMLPROJECT_EVENTSYSTEM_H

#include <map>
#include <functional>
#include <vector>
#include <algorithm>
#include <any>
#include <iostream>

struct Event {
    virtual ~Event() {}
};

typedef std::multimap<const std::type_info*, const std::function<void(const Event&)>> EventMap;

namespace Events {

    class Subscriber {
    public:
        Subscriber(EventMap* eventMap) : eventMap(eventMap){}

        template<typename EventType>
        void Subscribe(const std::function<void(const EventType&)>& callback) {
            eventMap->emplace(&typeid(EventType), [callback](const Event& event) {
                callback(dynamic_cast<const EventType&>(event));
            });
        }

        template<typename EventType>
        void Unsubscribe(const std::function<void(const EventType&)>& callback) {
            auto range = eventMap->equal_range(&typeid(EventType));
            for (auto it = range.first; it != range.second; ++it) {
                if (it->second.target_type() == callback.target_type()) {
                    eventMap->erase(it);
                    break;
                }
            }
        }
    private:
        EventMap* eventMap;
    };

    class Publisher {
    public:
        Publisher(EventMap* eventMap) : eventMap(eventMap){}

        template<typename EventType>
        void Publish(const EventType& event) {
            auto range = eventMap->equal_range(&typeid(event));
            for(auto it = range.first; it != range.second; ++it) {
                it->second(event);
            }
        }
    private:
        EventMap* eventMap;
    };
};

#endif //CMAKESFMLPROJECT_EVENTSYSTEM_H
