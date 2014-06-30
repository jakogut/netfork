#ifndef NETFORK_PACKAGE_H_
#define NETFORK_PACKAGE_H_

#include <netfork_constants.h>

#include <stdlib.h>

struct nf_package
{
	void* payload;
	size_t payload_size;

	// MD5 digest used as weak verification that the payload has not been altered
	char payload_digest[16];
};

// Compute the MD5 digest of the payload
void nf_sign_package(struct nf_package* p);

// Verify the MD5 digest of the payload, return NF_TRUE if it matches, and NF_FALSE if not.
int nf_verify_package(struct nf_package* p);

#endif
