

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H


#include <iostream>
#include <vector>

class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);

public:
    Polynomial();

    Polynomial(const std::vector<int>& coef);

    Polynomial(const Polynomial &rhs);

    Polynomial operator+(const Polynomial& rhs);

    Polynomial& operator+=(const Polynomial& rhs);

    bool operator!=(const Polynomial& rhs);

    bool operator==(const Polynomial& rhs);

    Polynomial& operator=(const Polynomial& rhs);

    ~Polynomial();

    void setDegree();

    int evaluate(const int& xValue);

    void cleanup() const;

private:
    struct Node { // Singly-linked list, stores ints
        explicit Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}

        int data;
        Node* next;
    };
    int degree;
    Node* headPtr;
};


#endif //HW_08_POLYNOMIAL_H
