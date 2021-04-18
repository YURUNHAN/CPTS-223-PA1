/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

 // Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include
using std::vector;
using std::list;
using std::pair;

using std::cout;
using std::endl;

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K, V>
{
private:
    int _bucket_count;
    int _size;
    vector<list<pair<K, V> > > buckets;
public:
    ChainingHash(int n = 11)
    {
        _bucket_count = n;
        buckets.resize(n);
        _size = 0;
    }

    ~ChainingHash()
    {
        this->clear();
    }

    int size()
    {
        return _size;
    }

    V operator[](const K& key)
    {
        size_t pos = hash(key) % _bucket_count;

        typename list<pair<K, V> >::iterator iter;
        for (iter = buckets[pos].begin(); iter != buckets[pos].end(); iter++)
        {
            if (iter->first == key)
            {
                return iter->second;
            }
        }

        return -1;
    }

    bool insert(const std::pair<K, V>& pair)
    {
        size_t pos = hash(pair.first) % _bucket_count;

        // find from buckets
        typename std::list<std::pair<K, V> >::iterator iter;
        for (iter = buckets[pos].begin(); iter != buckets[pos].end(); iter++)
        {
            if (iter->first == pair.first)
            {
                // just update it
                iter->second = pair.second;
                return true;
            }
        }

        // insert new pair
        _size++;
        buckets[pos].push_back(pair);
        if (load_factor() >= 0.75)
        {
            rehash();
        }
        return true;
    }

    void erase(const K& key)
    {
        size_t pos = hash(key) % _bucket_count;

        // find from the buckets
        typename std::list<std::pair<K, V> >::iterator iter;
        for (iter = buckets[pos].begin(); iter != buckets[pos].end(); iter++)
        {
            if (iter->first == key)
            {
                break;
            }
        }

        // if find success
        if (iter != buckets[pos].end())
        {
            _size--;
            buckets[pos].erase(iter);
        }
    }

    void clear()
    {
        _size = 0;
        for (int i = 0; i < _bucket_count; i++)
        {
            buckets[i].clear();
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

        ChainingHash<K, V> newHash(newSize);

        for (int pos = 0; pos < this->_bucket_count; pos++)
        {
            typename std::list<std::pair<K, V> >::iterator iter;
            for (iter = buckets[pos].begin(); iter != buckets[pos].end(); iter++)
            {
                newHash.insert(*iter);
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

#endif //__CHAINING_HASH_H
