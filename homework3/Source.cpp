#include <iostream>
#include <cmath>  
using namespace std;

// 節點結構定義
struct Node {
    int coef;      // 系數
    int exp;       // 指數
    Node* next;    // 指向下一個節點
};

class Polynomial {
private:
    Node* head;

    // 創建節點
    Node* createNode(int coef, int exp) {
        Node* newNode = new Node;
        newNode->coef = coef;
        newNode->exp = exp;
        newNode->next = nullptr;
        return newNode;
    }

public:
  
    Polynomial() : head(nullptr) {}

    // 拷貝構造函數
    Polynomial(const Polynomial& a) {
        if (!a.head) { 
            head = nullptr;
            return;
        }
        
        head = createNode(a.head->coef, a.head->exp);
        Node* current = head;
        Node* temp = a.head->next;

        // 複製其餘節點
        while (temp != a.head) {
            current->next = createNode(temp->coef, temp->exp);
            current = current->next;
            temp = temp->next;
        }
        current->next = head; // 將鏈表連成循環
    }


    ~Polynomial() {
        if (!head) return; // 如果鏈表是空的則直接返回
        Node* current = head->next;
        while (current != head) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        delete head; 
        head = nullptr;
    }

    // 賦值運算符重載
    Polynomial& operator=(const Polynomial& a) {
        if (this == &a) return *this; 
        this->~Polynomial();         // 清空當前node
        if (!a.head) {             
            head = nullptr;
            return *this;
        }
        // 複製頭節點
        head = createNode(a.head->coef, a.head->exp);
        Node* current = head;
        Node* temp = a.head->next;

        // 複製其餘節點
        while (temp != a.head) {
            current->next = createNode(temp->coef, temp->exp);
            current = current->next;
            temp = temp->next;
        }
        current->next = head; // 將鏈表連成循環
        return *this;
    }

    // 插入節點
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

    // 輸入符重載 
    friend istream& operator>>(istream& is, Polynomial& x) {
        int n;
        is >> n; // 輸入項數
        if (n <= 0) return is;

        int coef, exp;
        for (int i = 0; i < n; ++i) {
            is >> coef >> exp; // 輸入系數和指數
            x.insert(coef, exp);
        }
        return is;
    }

    // 輸出符重載 <<
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

    // 相加
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

    // 求值
    float Evaluate(float x) const {
        float result = 0;
        if (!head) return result;

        Node* current = head;
        do {
            result += current->coef * pow(x, current->exp); // 使用公式計算值
            current = current->next;
        } while (current != head);

        return result;
    }
};

int main() {
    Polynomial p1, p2, p3;

    cout << "請輸入第一個多項式（項數 系數 指數）：";
    cin >> p1;

    cout << "請輸入第二個多項式（項數 系數 指數）：";
    cin >> p2;

    p3 = p1 + p2;

    cout << "第一個多項式為： " << p1 << endl;
    cout << "第二個多項式為： " << p2 << endl;
    cout << "相加後的多項式為： " << p3 << endl;

    float x;
    cout << "請輸入一個值以求多項式的值：";
    cin >> x;
    cout << "第一個多項式的值為： " << p1.Evaluate(x) << endl;

    return 0;
}
