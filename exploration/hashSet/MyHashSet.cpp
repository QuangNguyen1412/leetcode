class MyHashSet {
class HashNode
{
public:
    HashNode(int val) :
            next(nullptr),
            _val(val) { }
    int value() { return _val; }
    void set_value(int val) { _val = val; }
    HashNode* next;

private:
    int _val;
};

public:
    const static int BUCKET_SIZE = 1000;
    MyHashSet() {
        _hashSet.fill(nullptr);
    }
    
    void add(int key) {
        auto hash = MyHashFunction(key);
        if (_hashSet[hash] == nullptr)
        {
            _hashSet[hash] = new HashNode(key);
        }
        else if (!contains(key))
        {
            auto* newNode = new HashNode(key);
            newNode->next = _hashSet[hash]->next;
            _hashSet[hash]->next = newNode;
        }
    }

    void remove(int key) {
        remove_node(key);
    }
    
    bool contains(int key) {
        bool ret = find_node(key) != nullptr;
        return ret;
    }
private:
    // return the node or nullptr
    HashNode* find_node(int key)
    {
        auto entry = _hashSet[MyHashFunction(key)];
        while (entry && entry->value() != key)
        {
            entry = entry->next;
        }
        return entry;
    }

    void remove_node(int key)
    {
        HashNode* entry = _hashSet[MyHashFunction(key)];
        HashNode* prevEntry = nullptr;
        while (entry)
        {
            if (entry->value() == key)
            {
                if (prevEntry == nullptr)
                {
                    _hashSet[MyHashFunction(key)] = entry->next;
                }
                else
                {
                    if (entry->next)
                        prevEntry->next = entry->next;
                    else prevEntry->next = nullptr;
                }
                break;
            }
            prevEntry = entry;
            entry = entry->next;
        }
    }
    // void print_node(HashNode* head)
    // {
    //     while (head)
    //     {
    //         cout << head->value() << " ";
    //         head = head->next;
    //     }
    //     cout << endl;
    // }

    int MyHashFunction(int key) {
        return key % BUCKET_SIZE;
    }
    std::array<HashNode*, BUCKET_SIZE> _hashSet;
};
/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */