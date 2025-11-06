#include <iostream>
#include "SortedSet.h"

using namespace std;

SortedSet::SortedSet() : IntList() {}

SortedSet::SortedSet(const SortedSet &copySet) : IntList(copySet) {}

SortedSet::SortedSet(const IntList &otherSet) : IntList(otherSet) {
    this->selection_sort();
    this->remove_duplicates();
}

SortedSet::~SortedSet() {
    clear();
}

bool SortedSet::in(int value) {
    bool isin = false; 
    IntNode* i = nullptr;
    for (i = head; i != nullptr; i = i->next) {
        if (i -> value == value) {
            isin = true; 
        }
    }
    return isin;
}

SortedSet SortedSet::operator|(const SortedSet &set) {
    SortedSet temp = *this;
    IntNode* i = set.head;
    while (i != nullptr) {
        temp.insert_ordered(i -> value);
        i = i -> next;
    }
    return temp;
}

SortedSet SortedSet::operator&(const SortedSet &set) {
    SortedSet intersection;
    IntNode* i = nullptr;
    for (i = set.head; i != nullptr; i = i->next) {
        if (in(i -> value) == true) {
            intersection.push_back(i -> value);
        }
    }
    return intersection;
}

void SortedSet::add(int value) {
    if (in(value) == false) {
        IntList::insert_ordered(value);
    }
}

void SortedSet::push_front(int value) {
    add(value);
}

void SortedSet::push_back(int value) {
    add(value);
}

void SortedSet::insert_ordered(int value) {
    add(value);
}

SortedSet& SortedSet::operator|=(const SortedSet &temp) {
    *this = *this | temp;
    return *this;
}

SortedSet& SortedSet::operator&=(const SortedSet &temp) {
    *this = *this & temp;
    return *this;
}