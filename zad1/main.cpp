#include <iostream>
#include <stdexcept>
#include <memory>

template <typename T> class ForwardList {
    private:
    struct Node {
        T data; //znach elementa
        std::unique_ptr<Node> next; //umni ukazatel
        explicit Node(const T& value) : data(value), next(nullptr) {} //konstructor 
    };
    std::unique_ptr<Node> head; //ukazatel na nachalo spiska

    public:
    ForwardList() : head(nullptr) {}

    void pushFront(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(head);
        head = std::move(newNode);
    } //kazdy novyi stanovitsya golovoi

    bool empty() const {
        return head == nullptr;
    }

    void popFront() {
        if (empty()) { //pust or net
            throw std::runtime_error("Oshibochka");
        }
        head = std::move(head->next); //peremeshayet ukazatel
    }

    const T& front() const {
        if (empty()) { //pust or net
           throw std::runtime_error("Oshibochka"); 
        }
        return head->data; //ssulochka na dannie
    }
};

int main() {
    ForwardList<int> list;
    
    list.pushFront(10);
    list.pushFront(20);
    list.pushFront(30); 
    std::cout << "Pervyi: " << list.front() << std::endl;
    list.popFront();
    std::cout << "New pervyi: " << list.front() << std::endl;
    while (!list.empty()) {
        std::cout << "Delete pervyi: " << list.front() << std::endl;
        list.popFront();
    }
    
    return 0;
}