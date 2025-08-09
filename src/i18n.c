/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * Copyright (c) 2025, Awe Morris. All rights reserved.
 */

/*
 * Pseudo gettext support.
 */

#if defined(USE_TRANSLATION)

#include <stratohal/platform.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

/*
 * NoctLang's language code.
 */
extern const char *noct_lang_code;

/*
 * Initialized the locale.
 */
void noct2d_init_locale(void)
{
	/* Initialize NoctLang's i18n system manually. */
	noct_lang_code = get_system_language();
}

#endif	/* defined(USE_TRANSLATION) */
