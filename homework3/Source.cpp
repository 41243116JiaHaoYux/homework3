#include <iostream>
#include <cmath> // �Ω� Evaluate ��Ƥ��� pow
using namespace std;

// �`�I���c�w�q
struct Node {
    int coef;      // �t��
    int exp;       // ����
    Node* next;    // ���V�U�@�Ӹ`�I
};

class Polynomial {
private:
    Node* head;

    // �Ыظ`�I
    Node* createNode(int coef, int exp) {
        Node* newNode = new Node;
        newNode->coef = coef;
        newNode->exp = exp;
        newNode->next = nullptr;
        return newNode;
    }

public:
  
    Polynomial() : head(nullptr) {}

    // �����c�y���
    Polynomial(const Polynomial& a) {
        if (!a.head) { 
            head = nullptr;
            return;
        }
        
        head = createNode(a.head->coef, a.head->exp);
        Node* current = head;
        Node* temp = a.head->next;

        // �ƻs��l�`�I
        while (temp != a.head) {
            current->next = createNode(temp->coef, temp->exp);
            current = current->next;
            temp = temp->next;
        }
        current->next = head; // �N���s���`��
    }


    ~Polynomial() {
        if (!head) return; // �p�G���O�Ū��h������^
        Node* current = head->next;
        while (current != head) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        delete head; 
        head = nullptr;
    }

    // ��ȹB��ŭ���
    Polynomial& operator=(const Polynomial& a) {
        if (this == &a) return *this; 
        this->~Polynomial();         // �M�ŷ�enode
        if (!a.head) {             
            head = nullptr;
            return *this;
        }
        // �ƻs�Y�`�I
        head = createNode(a.head->coef, a.head->exp);
        Node* current = head;
        Node* temp = a.head->next;

        // �ƻs��l�`�I
        while (temp != a.head) {
            current->next = createNode(temp->coef, temp->exp);
            current = current->next;
            temp = temp->next;
        }
        current->next = head; // �N���s���`��
        return *this;
    }

    // ���J�`�I
    void insert(int coef, int exp) {
        Node* newNode = createNode(coef, exp);
        if (!head) { 
            head = newNode;
            head->next = head; 
            return;
        }

        Node* current = head;
        Node* prev = nullptr;

        
        do {
            if (current->exp < exp) break; 
            current = current->next;
        } while (current != head);

        if (prev == nullptr) {
            newNode->next = head;
            
            Node* tail = head;
            while (tail->next != head) {
                tail = tail->next;
            }
            tail->next = newNode;
            head = newNode; 
        }
        else { 
            prev->next = newNode;
            newNode->next = current;
        }
    }

    // ��J�ŭ��� 
    friend istream& operator>>(istream& is, Polynomial& x) {
        int n;
        is >> n; // ��J����
        if (n <= 0) return is;

        int coef, exp;
        for (int i = 0; i < n; ++i) {
            is >> coef >> exp; // ��J�t�ƩM����
            x.insert(coef, exp);
        }
        return is;
    }

    // ��X�ŭ��� <<
    friend ostream& operator<<(ostream& os, const Polynomial& x) {
        if (!x.head) {
            os << "0";
            return os;
        }
        Node* current = x.head;
        do {
            if (current->coef != 0) {
                os << current->coef << "x^" << current->exp;
                if (current->next != x.head) os << " + ";
            }
            current = current->next;
        } while (current != x.head);
        return os;
    }

    // �ۥ[
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        Node* aCurrent = head;
        Node* bCurrent = b.head;

        do {
            result.insert(aCurrent->coef, aCurrent->exp);
            aCurrent = aCurrent->next;
        } while (aCurrent != head);

        do {
            result.insert(bCurrent->coef, bCurrent->exp);
            bCurrent = bCurrent->next;
        } while (bCurrent != b.head);

        return result;
    }

    // �D��
    float Evaluate(float x) const {
        float result = 0;
        if (!head) return result;

        Node* current = head;
        do {
            result += current->coef * pow(x, current->exp); // �ϥΤ����p���
            current = current->next;
        } while (current != head);

        return result;
    }
};

int main() {
    Polynomial p1, p2, p3;

    cout << "�п�J�Ĥ@�Ӧh�����]���� �t�� ���ơ^�G";
    cin >> p1;

    cout << "�п�J�ĤG�Ӧh�����]���� �t�� ���ơ^�G";
    cin >> p2;

    p3 = p1 + p2;

    cout << "�Ĥ@�Ӧh�������G " << p1 << endl;
    cout << "�ĤG�Ӧh�������G " << p2 << endl;
    cout << "�ۥ[�᪺�h�������G " << p3 << endl;

    float x;
    cout << "�п�J�@�ӭȥH�D�h�������ȡG";
    cin >> x;
    cout << "�Ĥ@�Ӧh�������Ȭ��G " << p1.Evaluate(x) << endl;

    return 0;
}
