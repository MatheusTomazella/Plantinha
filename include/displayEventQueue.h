#pragma once
#include "vector"

enum DisplayEvent {
    /* 0 */ DisplayEvent_NextTab,
    /* 1 */ DisplayEvent_NavigateHome
    /* 2 */
    /* 3 */
    /* 4 */
};

std::vector<DisplayEvent> displayEventQueue;

void addToDisplayEventQueue(DisplayEvent event) {
    displayEventQueue.push_back(event);
}