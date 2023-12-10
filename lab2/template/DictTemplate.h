//
// Created by Николай Головнев on 10.12.2023.
//

#ifndef DICTTEMPLATE_H
#define DICTTEMPLATE_H

#include <iostream>
#include <vector>
using namespace std;

template <class Key, class Value> class Dictionary {
private:
    typedef struct Item {
        Value value;
        Key key;
    } Item;
    vector<Item> _data;

public:
    void clear() {
        _data.clear();
    }

    long size() {
        return _data.size();
    }

    bool hasKey(Key key) {
        for (int i = 0; i < size(); i++) {
            if (_data[i].key == key) return true;
        }
        return false;
    }

    bool add(Key key, Value value) {
        if (hasKey(key)) return false;
        Item new_item;
        new_item.key = key;
        new_item.value = value;
        _data.push_back(new_item);
        return true;
    }

    Value &operator[](Key key) {
        for (int i = 0; i < size(); i++) {
            if (_data[i].key == key) return _data[i].value;
        }
        long idx = size();
        Item new_item;
        new_item.key = key;
        _data.push_back(new_item);
        return _data[idx].value;
    }

    Key findKey(long index) {
        if (index < 0) index = 0;
        for (int i = 0; i < size(); i++)
            if (i == index) return _data[i].key;
        return NULL;
    }

    Value &operator[](long index) {
        if (index < 0) index = 0;
        for (int i = 0; i < size(); i++) {
            if (i == index) return _data[i].value;
        }
        return _data[0].value;
    }
};

#endif //DICTTEMPLATE_H
