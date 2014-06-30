#include <netfork_package.h>

#include <openssl/md5.h>

void nf_sign_package(struct nf_package* p)
{
}

int nf_verify_package(struct nf_package* p)
{
	return NF_TRUE;
}
