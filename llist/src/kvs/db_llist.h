#define kvs_key_t uint32_t
#define kvs_value_t uint32_t
#include <stdint.h>

class Node
{
    public:
        char* key;
        kvs_key_t klen;
        char* value;
        kvs_value_t vlen;
        uint64_t hash;
        Node* left;
        Node* right;
    
    public:
        int InsertNode(Node* node, uint64_t hash);
        int GetNode(Node* node, uint64_t hash, char* result);
        int DeleteNode(Node* node, uint64_t hash);

        Node(char* ikey, char* ivalue, kvs_key_t iklen, kvs_value_t ivlen, uint64_t ihash);
};