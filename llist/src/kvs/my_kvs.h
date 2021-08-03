#ifndef __MY_KVS_H__
#define __MY_KVS_H__

#include "../datalab_store.h"

struct my_kvs {
	struct my_kvs *my_kvs;
	KVS_SET set;
	KVS_GET get;
	KVS_DEL del;
	void (*set_env) (struct my_kvs *my_kvs, KVS_SET my_kvs_set, KVS_GET my_kvs_get, KVS_DEL my_kvs_del); 
};

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
        Node(char* ikey, char* ivalue, kvs_key_t iklen, kvs_value_t ivlen);
        ~Node();
};

extern Node* root;
extern Node* start;
extern Node* end;

int my_kvs_init (struct my_kvs **my_kvs);
int my_kvs_destroy (struct my_kvs *my_kvs);
void  my_kvs_set_env (struct my_kvs *my_kvs, KVS_SET my_kvs_set, KVS_GET my_kvs_get, KVS_DEL my_kvs_del);

int my_kvs_set (struct my_kvs *my_kvs, struct kvs_key *key, struct kvs_value *value, struct kvs_context *ctx);
int my_kvs_get (struct my_kvs *my_kvs, struct kvs_key *key, struct kvs_value *value, struct kvs_context *ctx);
int my_kvs_del (struct my_kvs *my_kvs, struct kvs_key *key, struct kvs_context *ctx);

int InsertNode(Node* node, uint64_t hash);
int GetNode(Node* start, uint64_t hash, char* result);
int DeleteNode(Node* start, uint64_t hash);
void PrintNode(Node *node);
void print_hash(Node* step);

#endif
