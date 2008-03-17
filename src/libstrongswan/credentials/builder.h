/*
 * Copyright (C) 2008 Martin Willi
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

/**
 * @defgroup builder builder
 * @{ @ingroup credentials
 */

#ifndef BUILDER_H_
#define BUILDER_H_

typedef struct builder_t builder_t;
typedef enum builder_part_t builder_part_t;

/**
 * Constructor function which creates a new builder instance.
 *
 * @param subtype	constructor specific subtype, e.g. certificate_type_t
 * @return			builder to construct a instance of type
 */
typedef builder_t* (*builder_constructor_t)(int subtype);

#include <library.h>

/**
 * Parts to build credentials from.
 */
enum builder_part_t {
	/** DER encoded ASN1 blob, argument is a chunk_t */
	BUILD_BLOB_ASN1_DER,
	/** key size in bits, as used for key generation, as u_int */
	BUILD_KEY_SIZE,
	/** private key to use for signing, private_key_t* */
	BUILD_SIGNING_KEY,
	/** certificate used for signing, certificate_t* */
	BUILD_SIGNING_CERT,
	/** public key to include, public_key_t* */
	BUILD_PUBLIC_KEY,
	/** subject for e.g. certificates, identification_t* */
	BUILD_SUBJECT,
	/** additional subject name, identification_t* */
	BUILD_SUBJECT_ALTNAME,
	/** issuer for e.g. certificates, identification_t* */
	BUILD_ISSUER,
	/** additional issuer name, identification_t* */
	BUILD_ISSUER_ALTNAME,
	/** a CA certificate, certificate_t* */
	BUILD_CA_CERT,
	/** a certificate, certificate_t* */
	BUILD_CERT,
	/** enforce an additional X509 flag, x509_flag_t */
	BUILD_X509_FLAG,
	/** end of variable argument builder list */
	BUILD_END,
};

/**
 * enum names for build_part_t
 */
extern enum_name_t *builder_part_names;

/**
 * Credential construction API.
 *
 * The builder allows the construction of credentials in a generic and
 * flexible way.
 */
struct builder_t {

	/**
	 * Add a part to the construct.
	 *
	 * Any added parts get owned by the builder/construct, so clone/refcount
	 * them if needed.
	 *
	 * @param part		kind of part
	 * @param ...		part specific variable argument
	 */
	void (*add)(builder_t *this, builder_part_t part, ...);
	
	/**
	 * Build the construct with all supplied parts.
	 *
	 * Once build() is called, the builder gets destroyed.
	 *
	 * @return			specific interface, as requested with constructor.
	 */
	void* (*build)(builder_t *this);
};

#endif /* BUILDER_H_ @}*/
