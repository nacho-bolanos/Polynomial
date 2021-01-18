

#include "Polynomial.h"

using namespace std;



Polynomial::Polynomial() {
    degree = 0;
    headPtr = new Node(0);
}

Polynomial::Polynomial(const vector<int>& coef) {
    Node* temp = new Node(coef[coef.size() - 1]);
    headPtr = temp;
    if (coef.size() > 1) {
        for(int index = (coef.size() - 2); index >= 0; --index) {
            temp->next = new Node(coef[index]);
            temp = temp->next;
        }
    }
    cleanup();
    setDegree();
}

Polynomial::Polynomial(const Polynomial &rhs) {
    Node* temp = rhs.headPtr->next;
    Node* newNode = new Node(rhs.headPtr->data);
    degree = rhs.degree;
    headPtr = newNode;
    while (temp != nullptr) {
        newNode->next = new Node(temp->data);
        newNode = newNode->next;
        temp = temp->next;
    }
}

std::ostream& operator<<(std::ostream& os, const Polynomial& rhs) {
    if (rhs.degree == 0) {
        os << rhs.headPtr->data;
    } else {
        Polynomial tempPoly = rhs;
        int index = rhs.degree;
        int* reversedPoly = new int[index];
        while (tempPoly.headPtr != nullptr) {
            reversedPoly[index] = tempPoly.headPtr->data;
            tempPoly.headPtr = tempPoly.headPtr->next;
            --index;
        }
        for (size_t index = 0; index < (rhs.degree + 1); ++index) {
            if (index == rhs.degree || tempPoly.degree < 1) {os << reversedPoly[index];}
            else {
                if (reversedPoly[index] != 0) {
                    if (reversedPoly[index] != 1) {
                        if (tempPoly.degree == 1) {os << reversedPoly[index] << "x";}
                        else {os << reversedPoly[index] << "x^" << tempPoly.degree;}
                    }
                    if (reversedPoly[index] == 1) {
                        os << "x";
                        if (tempPoly.degree > 1) {os << "^" << tempPoly.degree;}
                    }
                    os << " + ";
                }
            }
            --tempPoly.degree;
        }
    }
    return os;
}

void Polynomial::setDegree(){
    int newDegree = 0;
    Node* tempHeadPTR = this->headPtr;
    while (tempHeadPTR->next != nullptr) {
        ++newDegree;
        tempHeadPTR = tempHeadPTR->next;
    }
    this->degree = newDegree;
}

Polynomial Polynomial::operator+(const Polynomial& rhs) {
    Node* tempPolyRHS = rhs.headPtr;
    Node* tempPolyLHS = this->headPtr;
    Polynomial newPoly;
    if (rhs.degree > this->degree) {
        Node* newData = new Node();
        newPoly.headPtr = newData;
        while (tempPolyLHS != nullptr && newData != nullptr) {
            newData->data = tempPolyRHS->data + tempPolyLHS->data;
            tempPolyLHS = tempPolyLHS->next;
            tempPolyRHS = tempPolyRHS->next;
            newData->next = new Node();
            newData = newData->next;
        }
        while (tempPolyRHS != nullptr && newData != nullptr) {
            newData->data = tempPolyRHS->data;
            tempPolyRHS = tempPolyRHS->next;
            newData->next = new Node();
            newData = newData->next;
        }
    } else {
        Node* newData = new Node();
        newPoly.headPtr = newData;
        while (tempPolyRHS != nullptr && newData != nullptr) {
            newData->data = tempPolyRHS->data + tempPolyLHS->data;
            tempPolyLHS = tempPolyLHS->next;
            tempPolyRHS = tempPolyRHS->next;
            newData->next = new Node();
            newData = newData->next;
        }
        while (tempPolyLHS != nullptr && newData != nullptr) {
            newData->data = tempPolyLHS->data;
            tempPolyLHS = tempPolyLHS->next;
            newData->next = new Node();
            newData = newData->next;
        }
    }
    newPoly.cleanup();
    newPoly.setDegree();
    return newPoly;
}

Polynomial& Polynomial::operator+=(const Polynomial &rhs) {
    Node *tempPolyRHS = rhs.headPtr;
    Node *tempPolyLHS = this->headPtr;
    if (rhs.degree > this->degree) {
        while (tempPolyLHS != nullptr) {
            tempPolyRHS->data += tempPolyLHS->data;
            tempPolyLHS = tempPolyLHS->next;
            tempPolyRHS = tempPolyRHS->next;
        }
        this->headPtr = tempPolyRHS;
    } else {
        while (tempPolyRHS != nullptr) {
            tempPolyLHS->data += tempPolyRHS->data;
            tempPolyLHS = tempPolyLHS->next;
            tempPolyRHS = tempPolyRHS->next;
        }
    }
    setDegree();
    cleanup();
    return *this;
}

bool Polynomial::operator!=(const Polynomial &rhs) const {
    if (this->degree != rhs.degree) {return true;}
    Node *tempPolyRHS = rhs.headPtr;
    Node *tempPolyLHS = this->headPtr;
    bool test = false;
    while (tempPolyLHS != nullptr && tempPolyRHS != nullptr) {
        if (tempPolyRHS->data != tempPolyLHS->data) {
            test = true;
        }
        tempPolyLHS = tempPolyLHS->next;
        tempPolyRHS = tempPolyRHS->next;
    }
    return test;
}

bool Polynomial::operator==(const Polynomial &rhs) const {
    if (this->degree != rhs.degree) {return false;}
    Node *tempPolyRHS = rhs.headPtr;
    Node *tempPolyLHS = this->headPtr;
    bool test = false;
    while (tempPolyLHS != nullptr && tempPolyRHS != nullptr) {
        if (tempPolyRHS->data == tempPolyLHS->data) {
            test = true;
        }
        tempPolyLHS = tempPolyLHS->next;
        tempPolyRHS = tempPolyRHS->next;
    }
    return test;
}

Polynomial &Polynomial::operator=(const Polynomial &rhs) {
    Node* temp = rhs.headPtr->next;
    Node* newNode = new Node(rhs.headPtr->data);
    degree = rhs.degree;
    headPtr = newNode;
    while (temp != nullptr) {
        newNode->next = new Node(temp->data);
        newNode = newNode->next;
        temp = temp->next;
    }
    return *this;
}

int Polynomial::evaluate(const int &xValue) const {
    int answer = 0;
    Node *tempPoly = this->headPtr;
    int& lastCoef = this->headPtr->data;
    int tempDegree = 1;
    while (tempPoly != nullptr) {
        if (&tempPoly->data == &lastCoef) {
            answer += tempPoly->data;
        }
        else {
            int coefVal = xValue;
            for (int mult = 2; mult <= tempDegree; mult++) {
                coefVal *= xValue;
            }
            answer += tempPoly->data * coefVal;
            ++tempDegree;
        }
        tempPoly = tempPoly->next;
    }
    return answer;
}

Polynomial::~Polynomial() {
    while (headPtr != nullptr) {
        Node* toRemove = headPtr;
        headPtr = headPtr->next;
        delete toRemove;
    }
    degree = 0;
}

void Polynomial::cleanup() const {
    Node* tempNode = headPtr;
    Node* realLeadingCoef;
    while (tempNode!= nullptr) {
        if (tempNode->data != 0) {
            realLeadingCoef = tempNode;
        }
        tempNode = tempNode->next;
    }
    delete realLeadingCoef->next;
    realLeadingCoef->next = nullptr;
}
