/*
 * LoRaMaDoR (LoRa-based mesh network for hams) project
 * Copyright (c) 2019 PU5EPX
 */

#ifndef __PACKET_H
#define  __PACKET_H

#include "Vector.h"
#include "Dict.h"
#include "Buffer.h"
#include "Pointer.h"

typedef Dict<Buffer> Params;
// value of a naked Params key
#define None "@, NONE, @"

struct Packet {
	Packet(const char *to, const char *from, unsigned long int ident, 
		const Params& params, const Buffer& msg);
	~Packet();

	static Ptr<Packet> decode_l2(const char* data, unsigned int len);
	static int get_decode_error();

	/* public for unit testing */
	static Ptr<Packet> decode_l3(const char* data, unsigned int len);
	static Ptr<Packet> decode_l3(const char *data);

	Packet(const Packet &) = delete;
	Packet(Packet &&);
	Packet() = delete;
	Packet& operator=(const Packet &) = delete;
	bool operator==(const Packet &) = delete;

	Ptr<Packet> change_msg(const Buffer&) const;
	Ptr<Packet> change_params(const Params&) const;
	Buffer encode_l2() const;

	/* public for unit testing */
	Buffer encode_l3() const;

	bool is_dup(const Packet& other) const;
	Buffer repr() const;
	const char *signature() const;
	const char *to() const;
	const char *from() const;
	unsigned long int ident() const;
	const Params& params() const;
	const char *sparams() const;
	const Buffer& msg() const;

	/* public for unit testing */
	static bool check_callsign(const Buffer&);
	static bool parse_params(const char *data, unsigned int len,
		unsigned long int &ident, Params &params);
	static bool parse_params(const char *data,
		unsigned long int &ident, Params &params);
	static Buffer encode_params(unsigned long int ident, const Params&);

private:
	Buffer _to;
	Buffer _from;
	const unsigned long int _ident;
	const Params _params;
	Buffer _sparams;
	Buffer _signature;
	const Buffer _msg;
};

#endif
