#ifndef __MY_KVS_H__
#define __MY_KVS_H__

#include "datalab_store.h"
class Node
{
    public:
    char* key;
    kvs_key_t klen;
    char* value;
    kvs_value_t vlen;
    uint64_t key_hash;
    uint64_t value_hash;
	Node* right;
    Node(const char* ikey, const char* ivalue, kvs_key_t iklen, kvs_value_t ivlen, uint64_t ikey_hash, uint64_t ivalue_hash);
	Node(char* ikey, char* ivalue, kvs_key_t iklen, kvs_value_t ivlen);
    ~Node();
};

class Table
{
    public:
    Node** BucketArray;

    Table();
	~Table();
    int InsertNode(Node* Node);
    int DeleteNode(char* key, uint64_t key_hash);
    int GetNode(char* key, char* result, uint64_t key_hash);
};

struct my_kvs {
	struct my_kvs *my_kvs;
	KVS_SET set;
	KVS_GET get;
	KVS_DEL del;
	void (*set_env) (struct my_kvs *my_kvs, KVS_SET my_kvs_set, KVS_GET my_kvs_get, KVS_DEL my_kvs_del); 
};

int my_kvs_init (struct my_kvs **my_kvs);
int my_kvs_destroy (struct my_kvs *my_kvs);
void  my_kvs_set_env (struct my_kvs *my_kvs, KVS_SET my_kvs_set, KVS_GET my_kvs_get, KVS_DEL my_kvs_del);

int my_kvs_set (struct my_kvs *my_kvs, struct kvs_key *key, struct kvs_value *value, struct kvs_context *ctx);
int my_kvs_get (struct my_kvs *my_kvs, struct kvs_key *key, struct kvs_value *value, struct kvs_context *ctx);
int my_kvs_del (struct my_kvs *my_kvs, struct kvs_key *key, struct kvs_context *ctx);

#endif
