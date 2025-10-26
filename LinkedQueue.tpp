template <typename T>
LinkedQueue<T>::LinkedQueue() {
    //TODO
    this->length = 0;
    head = nullptr;
    last = nullptr;
}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template <typename T>
T LinkedQueue<T>::back() const {
    if (isEmpty()) {
        throw string("back() error: queue is empty.");
    }
    return last->value;
}

template <typename T>
void LinkedQueue<T>::clear() {
    //todo
    while (head != nullptr) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
        this->length = 0;
        last = nullptr;
}


template <typename T>
void LinkedQueue<T>::copy(const LinkedQueue<T>& copyObj) {
    // start from an empty state
    head = nullptr;
    last = nullptr;
    Node* copyCurr = copyObj.head;
    while(copyCurr != nullptr) {
        Node* n = new Node(copyCurr->value);
        n->next = nullptr;
        if (head == nullptr) {
            head = n;
        } else {
            last->next = n;
        }

        last = n;
        copyCurr = copyCurr->next;
    }

    this->length = copyObj.length;
}

template <typename T>
void LinkedQueue<T>::dequeue() {
    if (isEmpty()) {
        throw string("dequeue() error: queue is empty.");
    }
    Node* tmp = head;
    head = head->next;
    if (head == nullptr) {
        last = nullptr;
    }
    delete tmp;
    --this->length;
}

template <typename T>
void LinkedQueue<T>::enqueue(const T& elem) {
    //TODO
    Node* node = new Node(elem, nullptr);
    if (isEmpty()) {
        head = last = node;
    } else {
        last->next = node;
        last = node;
    }
    ++this->length;
}

template <typename T>
T LinkedQueue<T>::front() const {
    if (isEmpty()) {
        throw string("front() error: queue is empty.");
    }
    return head->value;
}

template <typename T>
int LinkedQueue<T>::getLength() const {
    return this->length;
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const {
    return this->length == 0;
}