#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>

#include "Hash.h"

using std::vector;
using std::pair;

// Can be used for tracking lazy deletion for each element in your table
enum EntryState
{
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K, V>
{ // derived from Hash
private:
    // Needs a table and a size.
    // Table should be a vector of std::pairs for lazy deletion

    // content of each buckets
    struct SLOT
    {
        enum EntryState state;
        std::pair<K, V> pair;
    };

    std::vector<struct SLOT> buckets;
    int _size;
    int _bucket_count;
public:

    // constructor
    ProbingHash(int n = 11)
    {
        _bucket_count = n;
        buckets.resize(n);
        _size = 0;
        for (int i = 0; i < _bucket_count; i++)
        {
            buckets[i].state = EntryState::EMPTY;
        }
    }

    ~ProbingHash()
    {
        this->clear();
    }

    int size()
    {
        return _size;
    }

    // get the key
    V operator[](const K& key)
    {
        size_t pos = hash(key) % _bucket_count;

        while (1)
        {
            if (buckets[pos].state == EntryState::VALID && buckets[pos].pair.first == key)
            {
                return buckets[pos].pair.second;
            }

            if (buckets[pos].state == EntryState::EMPTY)
            {
                // cannot find key
                break;
            }
            pos = (pos + 1) % _bucket_count;
        }


        // error happen
        return -1;
    }

    bool insert(const std::pair<K, V>& pair)
    {
        size_t pos = hash(pair.first) % _bucket_count;
        while (1)
        {
            if (buckets[pos].state == EntryState::VALID && buckets[pos].pair.first == pair.first)
            {
                // update
                buckets[pos].pair = pair;
                return true;
            }

            if (buckets[pos].state != EntryState::VALID)
            {
                break;
            }
            pos = (pos + 1) % _bucket_count;
        }
        _size++;
        buckets[pos].state = EntryState::VALID;
        buckets[pos].pair = pair;

        if (load_factor() >= 0.75)
        {
            rehash();
        }

        return true;
    }

    void erase(const K& key)
    {
        size_t pos = hash(key) % _bucket_count;

        while (1)
        {
            if (buckets[pos].state == EntryState::VALID && buckets[pos].pair.first == key)
            {
                buckets[pos].state = EntryState::DELETED;
                _size--;
                break;
            }

            if (buckets[pos].state == EntryState::EMPTY)
            {
                // cannot find key
                break;
            }
            pos = (pos + 1) % _bucket_count;
        }


    }

    void clear()
    {
        _size = 0;
        for (int i = 0; i < _bucket_count; i++)
        {
            buckets[i].state = EntryState::EMPTY;
        }
    }

    int bucket_count()
    {
        return _bucket_count;
    }

    float load_factor()
    {
        return 1.0f * _size / _bucket_count;
    }

private:

    // rehash the table
    void rehash()
    {
        int newSize = findNextPrime(_bucket_count * 2);

        ProbingHash<K, V> newHash(newSize);

        for (int pos = 0; pos < this->_bucket_count; pos++)
        {
            if (buckets[pos].state == EntryState::VALID)
            {
                newHash.insert(buckets[pos].pair);
            }
        }

        this->buckets = newHash.buckets;
        this->_bucket_count = newHash._bucket_count;
    }


    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }

    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key)
    {
        std::hash<K> hashFun;
        int ret = (int)hashFun(key);
        if (ret < 0)
        {
            ret = -ret;
        }
        return ret;
    }

};

#endif //__PROBING_HASH_H
