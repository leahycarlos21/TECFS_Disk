//
// Created by leahycarlos21 on 22/11/18.
//

#ifndef TECFS_DISK_NODE_H
#define TECFS_DISK_NODE_H

#endif //TECFS_DISK_NODE_H


template<class T>
class Node {
private:
    Node<T> *next;
    T data;

public:
    Node(T data) {
        Node::data = data;
        next = nullptr;
    }

    void setData(T data) {
        Node::data = data;
    }

    T getData() {
        return data;
    }

    void setNext(Node *next) {
        Node::next = next;
    }

    Node *getNext() {
        return next;
    }
};
