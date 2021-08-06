#define XXH_INLINE_ALL
#include "xxhash.h"
#define kvs_key_t uint32_t
#define kvs_value_t uint32_t
#include <stdint.h>
#include <stdio.h>
#include "my_kvs.h"

void print_hash(Node* step);

Node::Node(char* ikey, char* ivalue, kvs_key_t iklen, kvs_value_t ivlen)
    : klen(iklen), vlen(ivlen), hash(XXH64(ikey, iklen, 0)), left(NULL), right(NULL)
{
    key = new char[klen];
    memcpy(key, ikey, iklen);
    value = new char[vlen];
    memcpy(value, ivalue, ivlen);
}

Node::~Node()
{
    if(key)
        delete[] key;
    if(value)
        delete[] value;
}

Node* root;

int InsertNode(Node* node, uint64_t hash)
{
    Node* step = root;
    Node* prev = root;

    while (hash > step->hash)
    {
        prev = step;
        step = step->right;
        if(step==NULL)
            break;
        if(hash == step->hash)
        {
            step->left->right = node;
            node->left = step->left;
            node->right = step->right;
            step->right->left = node;
            delete step;
            return 0;
        }
    }
    step = prev;

    if(step->right)
    {
        step->right->left = node;
        node->right = step->right;
    }
    step->right = node;
    node->left = step;
    return 0;
}

int GetNode(Node* start, uint64_t hash, char* result)
{
    Node* step = root;
    while(step)
    {
        if(step->hash == hash)
        {
            memcpy(result, step->value, step->vlen);
            return 0;
        }
        step = step->right;
    }
    return -1;
}

int DeleteNode(Node* start, uint64_t hash)
{
    Node* step = root;
    while(hash >= step->hash)
    {   
        if(step->hash == hash)
            {
                if(step->right)
                    step->right->left = step->left;
                step->left->right = step->right;
                delete step;
                return 0;
            }
        step = step->right;
        if(step==NULL)
            return -1;
    }
    return -1;
}

void print_hash(Node* step)
{
    if (step == NULL) {
        printf("Node is NULL\n");
        return;
    }

    printf("left: %lu\t", step->left ? step->left->hash : 0);
    printf("me: %lu\t", step->hash);
    printf("right: %lu\n", step->right ? step->right->hash : 0);
}

void PrintNode(Node *node)
{
    printf("%s++\n", __func__);
    while (node) {
        print_hash(node);
        node = node->right;
    }
    printf("%s--\n", __func__);
}
