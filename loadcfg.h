#ifndef LOADCFG_H_INCLUDED
#define LOADCFG_H_INCLUDED
/*********************************************************************
 *
 * File        :  $Source: /cvsroot/ijbswa/current/loadcfg.h,v $
 *
 * Purpose     :  Loads settings from the configuration file into
 *                global variables.  This file contains both the
 *                routine to load the configuration and the global
 *                variables it writes to.
 *
 * Copyright   :  Written by and Copyright (C) 2001 members of the
 *                Privoxy team. https://www.privoxy.org/
 *
 *                Based on the Internet Junkbuster originally written
 *                by and Copyright (C) 1997 Anonymous Coders and
 *                Junkbusters Corporation.  http://www.junkbusters.com
 *
 *                This program is free software; you can redistribute it
 *                and/or modify it under the terms of the GNU General
 *                Public License as published by the Free Software
 *                Foundation; either version 2 of the License, or (at
 *                your option) any later version.
 *
 *                This program is distributed in the hope that it will
 *                be useful, but WITHOUT ANY WARRANTY; without even the
 *                implied warranty of MERCHANTABILITY or FITNESS FOR A
 *                PARTICULAR PURPOSE.  See the GNU General Public
 *                License for more details.
 *
 *                The GNU General Public License should be included with
 *                this file.  If not, you can view it at
 *                http://www.gnu.org/copyleft/gpl.html
 *                or write to the Free Software Foundation, Inc., 59
 *                Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 *********************************************************************/


/* Don't need project.h, only this: */
struct configuration_spec;

/* Global variables */

#ifdef FEATURE_TOGGLE
/* Privoxy's toggle state */
extern int global_toggle_state;
#endif /* def FEATURE_TOGGLE */

#ifdef FEATURE_FORWARD_CLASS
/* Unfortunately, project.h is required by MAX_FORWARD_CLASSES */
#include "project.h"
extern int global_forward_class_state[MAX_FORWARD_CLASSES];
#endif /* def FEATURE_FORWARD_CLASS */

#ifdef FEATURE_MANUAL_TAGGER
extern struct list* global_manual_tagger;
#endif /* def FEATURE_MANUAL_TAGGER */

extern const char *configfile;


/* The load_config function is now going to call:
 * init_proxy_args, so it will need argc and argv.
 * Since load_config will also be a signal handler,
 * we need to have these globally available.
 */
extern int Argc;
extern char * const * Argv;
extern short int MustReload;


extern struct configuration_spec * load_config(void);

#ifdef FEATURE_GRACEFUL_TERMINATION
void unload_current_config_file(void);
#endif

#endif /* ndef LOADCFG_H_INCLUDED */

/*
  Local Variables:
  tab-width: 3
  end:
*/
