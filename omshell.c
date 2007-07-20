/* omshell.c
 * This is the implementation of the build-in shell output module.
 *
 * shell support was initially written by bkalkbrenner 2005-09-20
 *
 * File begun on 2007-07-20 by RGerhards (extracted from syslogd.c)
 * This file is under development and has not yet arrived at being fully
 * self-contained and a real object. So far, it is mostly an excerpt
 * of the "old" message code without any modifications. However, it
 * helps to have things at the right place one we go to the meat of it.
 *
 * Copyright 2007 Rainer Gerhards and Adiscon GmbH.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * A copy of the GPL can be found in the file "COPYING" in this distribution.
 */
#include "config.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "rsyslog.h"
#include "syslogd.h"
#include "syslogd-types.h"
#include "srUtils.h"
#include "omshell.h"


/* call the shell action
 * returns 0 if it succeeds, something else otherwise
 */
int doActionShell(selector_t *f, time_t now)
{
	uchar *psz;

	assert(f != NULL);
	/* TODO: using f->f_un.f_file.f_name is not clean from the point of
	 * modularization. We'll change that as we go ahead with modularization.
	 * rgerhards, 2007-07-20
	 */
	f->f_time = now; /* TODO: find out, if we can not simply replace this with time(NULL) */
	dprintf("\n");
	iovCreate(f);
	psz = (uchar*) iovAsString(f);
	if(execProg((uchar*) f->f_un.f_file.f_fname, 1, (uchar*) psz) == 0)
		logerrorSz("Executing program '%s' failed", f->f_un.f_file.f_fname);

	return 0;
}

/*
 * vi:set ai:
 */
