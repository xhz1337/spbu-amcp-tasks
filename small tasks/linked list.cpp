#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node* next;
    Node(int v) : value(v), next(nullptr) {}
};

struct List
{
    Node* first;
    List() : first(nullptr) {}
    bool empty()
    {
        if (first == nullptr)
        {
            return 1;
        }
        return 0;
    }
    void add(int n)
    {
        Node* t = new Node(n);
        if (empty())
        {
            first = t;
        }
        else
        {
            Node* temp = first;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = t;
        }
    }
    int size()
    {
        int c = 0;
        Node* temp = first;
        while (true)
        {
            if (empty())
            {
                return 0;
            }
            else if (temp->next != nullptr)
            {
                c++;
                temp = temp->next;
            }
            else
            {
                return c + 1;
            }
        }
    }
    int find(int t)
    {
        int c = 1;
        Node* temp = first;
        while (true)
        {
            if (empty())
            {
                return -1;
            }
            else if (temp->value == t)
            {
                return c;
            }
            else if (temp->next == nullptr)
            {
                return -1;
            }
            else
            {
                c++;
                temp = temp->next;
            }
        }
    }
    void del(int t)
    {
        if (find(t) == -1)
        {
            cout << "элемент не найден" << "\n";
            return;
        }
        else if (first->value == t)
        {
            first = first->next;
            return;
        }
        else
        {
            Node* f = first;
            Node* tmp = first->next;
            while (true)
            {
                if (tmp->value == t)
                {
                    f->next = tmp->next;
                    return;
                }
                else
                {
                    f = f->next;
                    tmp = tmp->next;
                }
            }
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    List a;
    int k;
    cin >> k;
    cout << "введите элементы" << "\n";
    for (int i = 0; i < k; i++)
    {
        int t;
        cin >> t;
        a.add(t);
    }
    cout << "размер:" << a.size() << "\n";
    cout << "сколько элементов вы хотите найти" << "\n";
    int b;
    cin >> b;
    for (int i = 0; i < b; i++)
    {
        int t;
        cin >> t;
        cout << a.find(t) << "\n";
    }
    cout << "введите элемент, который хотели бы удалить" << "\n";
    int q; cin >> q;
    a.del(q);
    cout << "размер" << a.size() << "\n";
    return 1;
}
