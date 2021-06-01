#include "polynomial.h"

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
    // If the degrees are not the same then they can't be equal.
    if (lhs.degree == rhs.degree) {
        Polynomial::Node* tempL = lhs.head;
        Polynomial::Node* tempR = rhs.head;
        // Check if all the values are identical, if not return false;
        while (tempL && tempR) {
            if (tempL->data != tempR->data) {
                return false;
            }
            tempL = tempL->next;
            tempR = tempR->next;
        }
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& rhs) {
    // If the polynomial is a zero polynomial only print the value.
    if (rhs.head->next == nullptr) {
        os << rhs.head->data;
        return os;
    }
    Polynomial::Node* tempHead = rhs.head;
    int tempDegree = rhs.degree;
    // Not printing the last item.
    while(tempHead->next) {
        // Not printing values of 0.
        if (tempHead->data != 0) {
            // Not printing the 1. i.e. 1x -> x.
            if (tempHead->data != 1) {
                os << tempHead->data;
            }
            os << "x";
            // If the degree is larger than one print a degree.
            if (tempDegree > 1) {
                os << "^" << tempDegree;
            }
            // Test for the sign.
            if (tempHead->next->data >= 0) {
                os << " + ";
            }
        }  
        --tempDegree;
        tempHead = tempHead->next;
    }
    // Printing the final element.
    os << tempHead->data;
    return os;
}

Polynomial::Polynomial() {
    head = new Node(0);
    degree = 0;
}

Polynomial::Polynomial(const std::vector<int> nums) : degree(nums.size() - 1) {
    // Get the index where the first non-zero element is.
    int count = 0;
    while (nums[count] == 0) {
        ++count;
    }
    Node* tempHead = new Node(nums[count]);
    head = tempHead;
    // Get the new degree.
    degree -= count;
    for(size_t index = count + 1; index < nums.size(); ++index) {
        tempHead->next = new Node(nums[index]);
        tempHead = tempHead->next;
    }
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
    Node* tempL = head;
    Node* tempR = rhs.head;
    int dif = 0;
    int shared = degree;
    // If the left side is empty, fill the left Polynomial with the values from the right.
    if (degree == 0 && rhs.degree != 0) {
        tempL = new Node(tempR->data);
        head = tempL;
        while (tempR->next) {
            tempL->next = new Node(tempR->next->data);
            tempL = tempL->next;
            tempR = tempR->next;
        }
        degree = rhs.degree;
        return *this;
    }
    // If the left polynomial is larger than the right just move the left until 
    // the polynomial degree's match.
    if (degree > rhs.degree) {
        dif = degree - rhs.degree;
        shared = rhs.degree;
        while (dif > 0) {
            tempL = tempL->next;
            --dif;
        }
    }
    // If the right polynomial is larger than the left, then insert the bigger degree values
    // in front of the left polynomial. Until the right and the left have the same degree.
    else if (degree < rhs.degree) {
        dif = rhs.degree - degree;
        Node* remaining = tempL;
        tempL = new Node(tempR->data);
        head = tempL;
        while (dif > 1) {
            tempL->next = new Node(tempR->next->data);
            tempL = tempL->next;
            tempR = tempR->next;
            --dif;
        }
        if (degree > 0) {
            tempL->next = remaining;
            tempL = tempL->next;
        }
        tempR = tempR->next;
    }
    // Add the right polynomial to the left polynomial.
    while (shared >= 0 && degree > 0) {
        tempL->data += tempR->data;
        tempL = tempL->next;
        tempR = tempR->next;
        --shared;
    } 
    // Change the degree.
    if (degree < rhs.degree) {
        degree = rhs.degree;
    }
    cleanup();
    return *this;
}

Polynomial::Polynomial(const Polynomial& rhs) : degree(rhs.degree) {
    Node* tempHead = new Node(rhs.head->data);
    head = tempHead;
    Node* temprhs = rhs.head;
    degree = rhs.degree;
    // Add the values to the next Node of the polynomial.
    while (temprhs->next) {
        tempHead->next = new Node(temprhs->next->data);
        tempHead = tempHead->next;
        temprhs = temprhs->next;
    }
}

Polynomial& Polynomial::operator=(const Polynomial& rhs) {
    if (*this == rhs) {
        return *this;
    }
    Node* temp = head;
    // Delete the current polynomial.
    while (temp) {
       Node* deleteN = temp;
       temp = temp->next;
       delete deleteN;
    }
    // Copy the new node.
    Node* tempHead = new Node(rhs.head->data);
    head = tempHead;
    Node* temprhs = rhs.head;
    degree = rhs.degree;
    while (temprhs->next) {
        tempHead->next = new Node(temprhs->next->data);
        tempHead = tempHead->next;
        temprhs = temprhs->next;
    }
    return *this;
}

Polynomial::~Polynomial() {
    Node* temp = head;
    // Loop through the linked list and delete the values;
    while (temp) {
       Node* deleteN = temp;
       temp = temp->next;
       delete deleteN;
    }
}

int Polynomial::evaluate(const int& x) const {
    int answer = 0;
    int tempDegree = degree;
    Node* tempPoly = head;
    // Check if the polynomial is not a zero polynomial.
    while (tempDegree > 0) {
        int exponent = x;
        // Exponent function.
        for(int num = 0; num < tempDegree - 1; ++num) {
            exponent *= x;
        }
        answer += tempPoly->data * exponent;
        tempPoly = tempPoly->next;
        --tempDegree;
    }
    answer += tempPoly->data;
    return answer;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial newP;
    newP += lhs;
    newP += rhs;
    return newP;
}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
    return !(lhs == rhs);
}

void Polynomial::cleanup() {
    Node* tempH = head;
    int count = 0;
    // Find the first non-zero coefficient.
    while (tempH) {
        ++count;
        if (tempH->data != 0) {
            head = tempH;
            break;
        }
        tempH = tempH->next;
    }
    degree = 0;
    tempH = head->next;
    // Get the new degree.
    while (tempH) {
        ++degree;
        tempH = tempH->next;
    }
}
