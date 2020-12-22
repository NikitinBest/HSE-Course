#include "list.h"

task::list::list():beg(nullptr), end(nullptr), _size(0){};
task::list::list(const list& other) {
	beg = end = nullptr;
	_size = 0;
	size_t cnt = 0;
	for (item* i = other.beg; cnt < other.size(); cnt++) {
		push_back(i->value);
		i = i->next;
	}
}
task::list::list(size_t count, const int& value){
    beg = end = nullptr;
    _size = 0;
    if (count == 0) return;
    for(size_t i = 0; i < count; i++) {
        push_back(value);
    }
};

task::list::~list(){
    clear();
    delete beg;
    delete end;
};

task::list& task::list::operator=(const list& other){
    if (this == &other){
        return *this;
    }
    if (other.empty()) {
        clear();
        return *this;
    }
    clear();
    for (auto item = other.beg; item!= nullptr; item = item->next){
        push_back(item->value);
    }

    return *this;
}

int& task::list::front(){
    return beg->value;
}
const int& task::list::front() const{
    return beg->value;
}

int& task::list::back(){
    return end->value;
}
const int& task::list::back() const{
    return end->value;
}


bool task::list::empty() const{
    return size() == 0;
}
size_t task::list::size() const{
    return _size;
}
void task::list::clear(){
    if(empty()) return;
    item* cur = beg;
    while(cur!= nullptr){
        auto next = cur->next;
        delete cur;
        cur = next;
    }
    _size = 0;
    beg = end = nullptr;
}

void task::list::push_front(const int& value){
    if(empty()){
        beg = end = new item{nullptr, nullptr, value};
        _size = 1;
    } else {
        beg->prev = new item{nullptr, beg, value};
        beg = beg->prev;
        _size++;
    }
}

void task::list::push_back(const int& value){
    if(empty()){
        beg = end = new item{nullptr, nullptr, value};
        _size = 1;
    }
    else {
        end->next = new item{end, nullptr, value};
        end = end->next;
        _size++;
    }
}

void task::list::delete_element(item* target) {
    if (target == nullptr) return;
    if (target->prev != nullptr) {
        if (target->next != nullptr) {
            target->prev->next = target->next;
            target->next->prev = target->prev;
        }
        else {
            target->prev->next = nullptr;
        }
    }
    else {
        if (target->next != nullptr) {
            target->next->prev = nullptr;
        }
    }
    if (target == beg && target == end) {
        beg = end = nullptr;
    }
    else if (target == beg) {
        if (target->next != nullptr) beg = target->next;
        else beg = nullptr;
    }
    else if (target == end) {
        if (target->prev != nullptr) end = target->prev;
        else end = nullptr;
    }
    delete target;
}

void task::list::pop_front() {
    if (beg == nullptr) return;
    _size--;
    if (end != beg) {
        item* next_tmp = beg->next;
        list::delete_element(beg);
        beg = next_tmp;
    }
    else {
        delete beg;
        beg = end = nullptr;
    }
}
void task::list::pop_back() {
    if (end == nullptr) return;
    _size--;
    if (end != beg) {
        item* prev_tmp = end->prev;
        list::delete_element(end);
        end = prev_tmp;
    }
    else {
        delete end;
        beg = end = nullptr;
    }
}


void task::list::resize(size_t count){
    if(count == 0){
        clear();
        return;
    }
    if (_size == count){
        return;
    } else if (_size > count){
        item* cur = beg;
        size_t pos = 0;
        while (pos < count){
            cur = cur->next;
            pos++;
        }
        end = cur->prev;
        end->next = nullptr;
        while (cur!= nullptr){
            item* next = cur->next;
            delete cur;
            cur = next;
        }
    } else {
        item* added = new item{nullptr, nullptr, int()};
        beg = added;
        for(size_t i = 1; i < count - _size; i++){
            added->next = new item{added, nullptr, int()};
            added = added->next;
        }
        end = added;
    }
    _size = count;
}

void task::list::swap(list& other){
    size_t temp = _size;
    _size = other._size;
    other._size = temp;
    item* temp_item = beg;
    beg = other.beg;
    other.beg = temp_item;
    temp_item = end;
    end = other.end;
    other.end = temp_item;
}

void task::list::remove(const int& value) {
    item* cur = beg;
    item* delete_later = nullptr;
    while (cur != nullptr) {
        if (cur->value == value) {
            if (cur->prev != nullptr) {
                cur->prev->next = cur->next;
            }
            if (cur->next != nullptr) {
                cur->next->prev = cur->prev;
            }

            item* next = cur->next;
            if (cur == beg) {
                beg = next;
            }
            if (cur == end) {
                end = cur->prev;
            }
            if (std::addressof(value) != std::addressof(cur->value)) {
                delete cur;
            } else {
                delete_later = cur;
            }

            cur = next;
            _size--;
        } else {
            cur = cur->next;
        }
    }
    if (delete_later != nullptr)
        delete delete_later;
}

void task::list::unique(){
    if (empty()) return;
    list tmp;
    tmp.push_front(front());
    pop_front();
    while(!empty()){
        if(front() == tmp.back()){
            pop_front();
        } else {
            tmp.push_back(front());
            pop_front();
        }
    }
    *this = tmp;
}
void task::list::sort(){
    if(empty() || _size == 1) return;
    bool not_sorted = true;
    item* l = nullptr, *r = nullptr;
    while(not_sorted){
        not_sorted = false;
        l = beg;
        while(l->next != r){
            if(l->value > l->next->value){
                int tmp = l->value;
                l->value = l->next->value;
                l->next->value = tmp;
                not_sorted = true;
            }
            l = l->next;
        }
        r = l;
    }
}
