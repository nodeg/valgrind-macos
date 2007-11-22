
/*--------------------------------------------------------------------*/
/*--- Command line options.                                        ---*/
/*---                                                  m_options.c ---*/
/*--------------------------------------------------------------------*/

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2000-2007 Nicholas Nethercote
      njn@valgrind.org

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/

#include "pub_core_basics.h"
#include "pub_core_options.h"
#include "pub_core_libcassert.h"
#include "pub_core_libcprint.h"

// See pub_{core,tool}_options.h for explanations of all these.


/* Define, and set defaults. */
VexControl VG_(clo_vex_control);
Bool   VG_(clo_error_limit)    = True;
Int    VG_(clo_error_exitcode) = 0;
Bool   VG_(clo_db_attach)      = False;
Char*  VG_(clo_db_command)     = GDB_PATH " -nw %f %p";
Int    VG_(clo_gen_suppressions) = 0;
Int    VG_(clo_sanity_level)   = 1;
Int    VG_(clo_verbosity)      = 1;
Bool   VG_(clo_xml)            = False;
HChar* VG_(clo_xml_user_comment) = NULL;
Bool   VG_(clo_demangle)       = True;
Bool   VG_(clo_trace_children) = False;
Bool   VG_(clo_child_silent_after_fork) = False;
Int    VG_(clo_log_fd)         = 2; /* must be signed, as -1 is possible. */
Char*  VG_(clo_log_name)       = NULL;
Char*  VG_(clo_log_file_qualifier) = NULL;
Bool   VG_(clo_time_stamp)     = False;
Int    VG_(clo_input_fd)       = 0; /* stdin */
Int    VG_(clo_n_suppressions) = 0;
Char*  VG_(clo_suppressions)[VG_CLO_MAX_SFILES];
UChar  VG_(clo_trace_flags)    = 0; // 00000000b
UChar  VG_(clo_profile_flags)  = 0; // 00000000b
Int    VG_(clo_trace_notbelow) = 999999999;
Bool   VG_(clo_trace_syscalls) = False;
Bool   VG_(clo_trace_signals)  = False;
Bool   VG_(clo_trace_symtab)   = False;
HChar* VG_(clo_trace_symtab_patt) = "*";
Bool   VG_(clo_trace_cfi)      = False;
Bool   VG_(clo_debug_dump_syms) = False;
Bool   VG_(clo_debug_dump_line) = False;
Bool   VG_(clo_debug_dump_frames) = False;
Bool   VG_(clo_trace_redir)    = False;
Bool   VG_(clo_trace_sched)    = False;
Bool   VG_(clo_trace_pthreads) = False;
Int    VG_(clo_dump_error)     = 0;
Int    VG_(clo_backtrace_size) = 12;
Char*  VG_(clo_sim_hints)      = NULL;
Bool   VG_(clo_sym_offsets)    = False;
Bool   VG_(clo_run_libc_freeres) = True;
Bool   VG_(clo_track_fds)      = False;
Bool   VG_(clo_show_below_main)= False;
Bool   VG_(clo_show_emwarns)   = False;
Word   VG_(clo_max_stackframe) = 2000000;
Bool   VG_(clo_wait_for_gdb)   = False;
VgSmc  VG_(clo_smc_check)      = Vg_SmcStack;
HChar* VG_(clo_kernel_variant) = NULL;


/*====================================================================*/
/*=== Command line errors                                          ===*/
/*====================================================================*/

static void revert_to_stderr ( void )
{
   vg_assert( !VG_(logging_to_socket) );
   VG_(clo_log_fd) = 2; /* stderr */
}

__attribute__((noreturn))
void VG_(err_bad_option) ( Char* opt )
{
   revert_to_stderr();
   VG_(printf)("valgrind: Bad option '%s'; aborting.\n", opt);
   VG_(printf)("valgrind: Use --help for more information.\n");
   VG_(exit)(1);
}

__attribute__((noreturn))
void VG_(err_missing_prog) ( void  )
{
   revert_to_stderr();
   VG_(printf)("valgrind: no program specified\n");
   VG_(printf)("valgrind: Use --help for more information.\n");
   VG_(exit)(1);
}

__attribute__((noreturn))
void VG_(err_config_error) ( Char* msg )
{
   revert_to_stderr();
   VG_(printf)("valgrind: Startup or configuration error:\n   %s\n", msg);
   VG_(printf)("valgrind: Unable to start up properly.  Giving up.\n");
   VG_(exit)(1);
}


/*--------------------------------------------------------------------*/
/*--- end                                              m_options.c ---*/
/*--------------------------------------------------------------------*/
