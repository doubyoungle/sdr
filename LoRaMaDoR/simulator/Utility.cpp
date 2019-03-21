/*
 * LoRaMaDoR (LoRa-based mesh network for hams) project
 * Copyright (c) 2019 PU5EPX
 */

#include <stdlib.h>
#include "Utility.h"

Dict::Dict()
{
	contents = (StringPair**) malloc(0);
	len = 0;
}

Dict::Dict(const Dict &model)
{
	contents = (StringPair**) malloc(model.len * sizeof(StringPair*));
	len = model.len;
	for (int i = 0; i < len; ++i) {
		contents[i] = new StringPair(*model.contents[i]);
	}
}

int Dict::indexOf(const String &key) const
{
	for (int i = 0; i < len; ++i) {
		if (key == contents[i]->a) {
			return i;
		}
	}

	return -1;
}

bool Dict::has(const String& key) const
{
	return indexOf(key) != -1;
}

const String *Dict::get(const String& key) const
{
	int pos = indexOf(key);
	if (pos <= -1) {
		return 0;
	}
	return &contents[pos]->b;
}

bool Dict::put(const String& key, const String& value)
{	
	int pos = indexOf(key);
	bool ret = false;

	if (pos <= -1) {
		len += 1;
		contents = (StringPair**) realloc(contents, len * sizeof(StringPair*));
		pos = len - 1;
		ret = true;
	} else {
		delete contents[pos];
	}
	contents[pos] = new StringPair(key, value);

	return ret;
}

void Dict::foreach(void* cargo, bool (*f)(const String&, const String&, void*)) const
{
	for (int i = 0; i < len; ++i) {
		if (! f(contents[i]->a, contents[i]->b, cargo)) {
			break;
		}
	}
}

int Dict::length() const
{
	return len;
}

Buffer::Buffer(int len)
{
	this->len = len;
	this->buf = (char*) calloc(len, sizeof(char));
}

Buffer::Buffer(const char *buf, int len)
{
	this->len = len;
	this->buf = (char*) malloc(len);
	memcpy(this->buf, buf, len);
	this->buf[len] = 0;
}

String Buffer::Str() const
{
	return String(this->buf);
}
