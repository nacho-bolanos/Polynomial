#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>

class Polynomial {

    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);

    public:
        Polynomial();

        Polynomial(const std::vector<int> nums);

        Polynomial& operator+=(const Polynomial& rhs);

        Polynomial(const Polynomial& rhs);

        Polynomial& operator=(const Polynomial& rhs);

        ~Polynomial();

        int evaluate(const int& x) const;

        void cleanup();

    private:
        struct Node {
            Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}

            int data;
            Node* next;
        };
        int degree;
        Node* head;
};

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);

bool operator!=(const Polynomial& lhs, const Polynomial& rhs);

#endif
