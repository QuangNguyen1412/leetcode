class MyHashMap {
class HashNode
{
public:
    HashNode(int key, int val) :
            next(nullptr),
            _val(val) { this->bucketKey = key; }
    int value() { return _val; }
    void set_value(int val) { _val = val; }
    HashNode* next;
    int bucketKey;
private:
    int _val;
};

public:
    const static int BUCKET_SIZE = 1000;
    MyHashMap() {
        _buckets.fill(nullptr);
    }

    void put(int key, int value) {
        auto hash = MyHashFunction(key);
        if (_buckets[hash] == nullptr)
        {
            _buckets[hash] = new HashNode(key / BUCKET_SIZE, value);
            // cout << "Put: ";
            // print_node(key);
            return;
        }
        auto entry = find_node(key);
        if (entry)
        {
            entry->set_value(value);
        }
        else
        {
            auto* newNode = new HashNode(key / BUCKET_SIZE, value);
            newNode->next = _buckets[hash]->next;
            _buckets[hash]->next = newNode;
        }
        // cout << "Put: ";
        // print_node(key);
    }

    void remove(int key) {
        remove_node(key);
        // cout << "Remove: " ;
        // print_node(key);
    }
    
    int get(int key) {
        auto retEntry = find_node(key);
        return retEntry != nullptr ? retEntry->value() : -1;
    }
private:
    // return the node or nullptr
    HashNode* find_node(int key)
    {
        auto bucketKey = key / BUCKET_SIZE;
        auto entry = _buckets[MyHashFunction(key)];
        while (entry && entry->bucketKey != bucketKey)
        {
            entry = entry->next;
        }
        return entry;
    }

    void remove_node(int key)
    {
        HashNode* entry = _buckets[MyHashFunction(key)];
        HashNode* prevEntry = nullptr;
        auto bucketKey = key / BUCKET_SIZE;
        while (entry)
        {
            if (entry->bucketKey == bucketKey)
            {
                if (prevEntry == nullptr)
                {
                    _buckets[MyHashFunction(key)] = entry->next;
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
    // void print_node(int key)
    // {
    //     auto head = _buckets[MyHashFunction(key)];
    //     cout << "Bucket " << MyHashFunction(key) << " - key " << key << ": ";
    //     while (head)
    //     {
    //         cout << "[" << head->bucketKey << "," << head->value() << "], ";
    //         head = head->next;
    //     }
    //     cout << endl;
    // }

    int MyHashFunction(int key) {
        return key % BUCKET_SIZE;
    }
    std::array<HashNode*, BUCKET_SIZE> _buckets;
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */