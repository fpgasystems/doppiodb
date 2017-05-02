/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2016 - 2017 Systems Group, ETH Zurich
 */
#ifndef F_REGEX
#define F_REGEX

#define MAX_CHARS 128
#define MAX_STATES 32

	#ifndef DEBUG
	#define DEBUG true
	#endif

#define bool short
#define true 1
#define false 0

#define SUPPORTS_CASE_INSENSITIVE false

int fregex_get_config(const char* regex_string, int char_cnt, int state_cnt, unsigned char* config_data, int* config_len);

#endif 
