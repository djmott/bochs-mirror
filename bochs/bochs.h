/////////////////////////////////////////////////////////////////////////
// $Id$
/////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2001-2017  The Bochs Project
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA B 02110-1301 USA

//
// bochs.h is the master header file for all C++ code.  It includes all
// the system header files needed by bochs, and also includes all the bochs
// C++ header files.  Because bochs.h and the files that it includes has
// structure and class definitions, it cannot be called from C code.
//

#ifndef BX_BOCHS_H
#  define BX_BOCHS_H 1

#include "config.h"      /* generated by configure script from config.h.in */

#ifndef __QNXNTO__
extern "C" {
#endif

#ifdef WIN32
// In a win32 compile (including cygwin), windows.h is required for several
// files in gui and iodev.  It is important to include it here in a header
// file so that WIN32-specific data types can be used in fields of classes.
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#if defined(__sun__)
#undef EAX
#undef ECX
#undef EDX
#undef EBX
#undef ESP
#undef EBP
#undef ESI
#undef EDI
#undef EIP
#undef CS
#undef DS
#undef ES
#undef SS
#undef FS
#undef GS
#endif
#include <assert.h>
#include <errno.h>

#ifndef WIN32
#  include <unistd.h>
#else
#  include <io.h>
#endif
#include <time.h>
#if BX_WITH_MACOS
#  include <types.h>
#  include <stat.h>
#  include <cstdio>
#  include <unistd.h>
#elif BX_WITH_CARBON
#  include <sys/types.h>
#  include <sys/stat.h>
#  include <sys/param.h> /* for MAXPATHLEN */
#  include <sys/time.h>
#  include <utime.h>
#else
#  ifndef WIN32
#    include <sys/time.h>
#  endif
#  include <sys/types.h>
#  include <sys/stat.h>
#endif
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#ifdef macintosh
#  define SuperDrive "[fd:]"
#endif

#ifndef __QNXNTO__
}
#endif

#include "osdep.h"       /* platform dependent includes and defines */
#include "bx_debug/debug.h"
#include "gui/siminterface.h"

// BX_SHARE_PATH should be defined by the makefile.  If not, give it
// a value of NULL to avoid compile problems.
#ifndef BX_SHARE_PATH
#define BX_SHARE_PATH NULL
#endif

// prototypes
int  bx_begin_simulation(int argc, char *argv[]);
void bx_stop_simulation();
char *bx_find_bochsrc(void);
const char *get_builtin_variable(const char *varname);
int  bx_parse_cmdline(int arg, int argc, char *argv[]);
int  bx_read_configuration(const char *rcfile);
int  bx_write_configuration(const char *rcfile, int overwrite);
void bx_reset_options(void);
void bx_set_log_actions_by_device(bx_bool panic_flag);
// special config parameter and options functions for plugins
void bx_init_std_nic_options(const char *name, bx_list_c *menu);
void bx_init_usb_options(const char *usb_name, const char *pname, int maxports);
int  bx_parse_param_from_list(const char *context, const char *input, bx_list_c *list);
int  bx_parse_nic_params(const char *context, const char *param, bx_list_c *base);
int  bx_parse_usb_port_params(const char *context, bx_bool devopt,
                              const char *param, int maxports, bx_list_c *base);
int  bx_write_param_list(FILE *fp, bx_list_c *base, const char *optname, bx_bool multiline);
int  bx_write_usb_options(FILE *fp, int maxports, bx_list_c *base);

Bit32u crc32(const Bit8u *buf, int len);

// used to print param tree from debugger
void print_tree(bx_param_c *node, int level = 0, bx_bool xml = BX_FALSE);

#if BX_ENABLE_STATISTICS
// print statistics
void print_statistics_tree(bx_param_c *node, int level = 0);
#define INC_STAT(stat) (++(stat))
#else
#define INC_STAT(stat)
#endif

//
// some macros to interface the CPU and memory to external environment
// so that these functions can be redirected to the debugger when
// needed.
//

#define BXRS_PARAM_SPECIAL(parent, name, maxvalue, save_handler, restore_handler) \
{ \
  bx_param_num_c *param = new bx_param_num_c(parent, #name, "", "", 0, maxvalue, 0); \
  param->set_base(BASE_HEX); \
  param->set_sr_handlers(this, save_handler, restore_handler); \
}

#define BXRS_PARAM_SPECIAL64(parent, name, save_handler, restore_handler) \
  BXRS_PARAM_SPECIAL(parent, name, BX_MAX_BIT64U, save_handler, restore_handler)
#define BXRS_PARAM_SPECIAL32(parent, name, save_handler, restore_handler) \
  BXRS_PARAM_SPECIAL(parent, name, BX_MAX_BIT32U, save_handler, restore_handler)
#define BXRS_PARAM_SPECIAL16(parent, name, save_handler, restore_handler) \
  BXRS_PARAM_SPECIAL(parent, name, BX_MAX_BIT16U, save_handler, restore_handler)
#define BXRS_PARAM_SPECIAL8(parent, name, save_handler, restore_handler) \
  BXRS_PARAM_SPECIAL(parent, name, BX_MAX_BIT8U,  save_handler, restore_handler)

#define BXRS_HEX_PARAM_SIMPLE32(parent, name) \
  new bx_shadow_num_c(parent, #name, (Bit32u*)&(name), BASE_HEX)
#define BXRS_HEX_PARAM_SIMPLE64(parent, name) \
  new bx_shadow_num_c(parent, #name, (Bit64u*)&(name), BASE_HEX)

#define BXRS_HEX_PARAM_SIMPLE(parent, name) \
  new bx_shadow_num_c(parent, #name, &(name), BASE_HEX)
#define BXRS_HEX_PARAM_FIELD(parent, name, field) \
  new bx_shadow_num_c(parent, #name, &(field), BASE_HEX)

#define BXRS_DEC_PARAM_SIMPLE(parent, name) \
  new bx_shadow_num_c(parent, #name, &(name), BASE_DEC)
#define BXRS_DEC_PARAM_FIELD(parent, name, field) \
  new bx_shadow_num_c(parent, #name, &(field), BASE_DEC)

#define BXRS_PARAM_BOOL(parent, name, field) \
  new bx_shadow_bool_c(parent, #name, (bx_bool*)(&(field)))

// =-=-=-=-=-=-=- Normal optimized use -=-=-=-=-=-=-=-=-=-=-=-=-=-=
// some pc_systems functions just redirect to the IO devices so optimize
// by eliminating call here
//
// #define BX_INP(addr, len)        bx_pc_system.inp(addr, len)
// #define BX_OUTP(addr, val, len)  bx_pc_system.outp(addr, val, len)
#define BX_INP(addr, len)           bx_devices.inp(addr, len)
#define BX_OUTP(addr, val, len)     bx_devices.outp(addr, val, len)
#define BX_TICK1()                  bx_pc_system.tick1()
#define BX_TICKN(n)                 bx_pc_system.tickn(n)
#define BX_INTR                     bx_pc_system.INTR
#define BX_RAISE_INTR()             bx_pc_system.raise_INTR()
#define BX_CLEAR_INTR()             bx_pc_system.clear_INTR()
#define BX_HRQ                      bx_pc_system.HRQ

#if BX_SUPPORT_SMP
#define BX_CPU(x)                   (bx_cpu_array[x])
#else
#define BX_CPU(x)                   (&bx_cpu)
#endif

#define BX_MEM(x)                   (&bx_mem)

#define BX_SET_ENABLE_A20(enabled)  bx_pc_system.set_enable_a20(enabled)
#define BX_GET_ENABLE_A20()         bx_pc_system.get_enable_a20()

#if BX_SUPPORT_A20
#  define A20ADDR(x)                ((bx_phy_address)(x) & bx_pc_system.a20_mask)
#else
#  define A20ADDR(x)                ((bx_phy_address)(x))
#endif

// you can't use static member functions on the CPU, if there are going
// to be 2 cpus.  Check this early on.
#if BX_SUPPORT_SMP
#  if BX_USE_CPU_SMF
#    error For SMP simulation, BX_USE_CPU_SMF must be 0.
#  endif
#endif

//
// Ways for the the external environment to report back information
// to the debugger.
//

#if BX_DEBUGGER
#  define BX_DBG_ASYNC_INTR bx_guard.async.irq
#  define BX_DBG_ASYNC_DMA  bx_guard.async.dma

#  define BX_DBG_DMA_REPORT(addr, len, what, val) \
        if (bx_guard.report.dma) bx_dbg_dma_report(addr, len, what, val)
#  define BX_DBG_IAC_REPORT(vector, irq) \
        if (bx_guard.report.irq) bx_dbg_iac_report(vector, irq)
#  define BX_DBG_A20_REPORT(val) \
        if (bx_guard.report.a20) bx_dbg_a20_report(val)
#  define BX_DBG_IO_REPORT(port, size, op, val) \
        if (bx_guard.report.io) bx_dbg_io_report(port, size, op, val)
#  define BX_DBG_LIN_MEMORY_ACCESS(cpu, lin, phy, len, memtype, rw, data) \
        bx_dbg_lin_memory_access(cpu, lin, phy, len, memtype, rw, data)
#  define BX_DBG_PHY_MEMORY_ACCESS(cpu, phy, len, memtype, rw, why, data) \
        bx_dbg_phy_memory_access(cpu, phy, len, memtype, rw, why, data)
#else  // #if BX_DEBUGGER
// debugger not compiled in, use empty stubs
#  define BX_DBG_ASYNC_INTR 1
#  define BX_DBG_ASYNC_DMA  1
#  define BX_DBG_DMA_REPORT(addr, len, what, val)                               /* empty */
#  define BX_DBG_IAC_REPORT(vector, irq)                                        /* empty */
#  define BX_DBG_A20_REPORT(val)                                                /* empty */
#  define BX_DBG_IO_REPORT(port, size, op, val)                                 /* empty */
#  define BX_DBG_LIN_MEMORY_ACCESS(cpu, lin, phy, len, memtype, rw, data)       /* empty */
#  define BX_DBG_PHY_MEMORY_ACCESS(cpu,      phy, len, memtype, rw, attr, data) /* empty */
#endif  // #if BX_DEBUGGER

#define MAGIC_LOGNUM 0x12345678

typedef class BOCHSAPI logfunctions
{
  char *name;
  char *prefix;
  int onoff[N_LOGLEV];
  class iofunctions *logio;
  // default log actions for all devices, declared and initialized
  // in logio.cc.
  BOCHSAPI_CYGONLY static int default_onoff[N_LOGLEV];
public:
  logfunctions(void);
  logfunctions(class iofunctions *);
  virtual ~logfunctions(void);

  void info(const char *fmt, ...)   BX_CPP_AttrPrintf(2, 3);
  void error(const char *fmt, ...)  BX_CPP_AttrPrintf(2, 3);
  void panic(const char *fmt, ...)  BX_CPP_AttrPrintf(2, 3);
  void ldebug(const char *fmt, ...) BX_CPP_AttrPrintf(2, 3);
  void fatal1(const char *fmt, ...) BX_CPP_AttrPrintf(2, 3);
  void fatal(int level, const char *prefix, const char *fmt, va_list ap, int exit_status);
  void warn(int level, const char *prefix, const char *fmt, va_list ap);
  void ask(int level, const char *prefix, const char *fmt, va_list ap);
  void put(const char *p);
  void put(const char *n, const char *p);
  void setio(class iofunctions *);
  void setonoff(int loglev, int value) {
    assert (loglev >= 0 && loglev < N_LOGLEV);
    onoff[loglev] = value;
  }
  const char *get_name() const { return name; }
  const char *getprefix() const { return prefix; }
  int getonoff(int level) const {
    assert (level>=0 && level<N_LOGLEV);
    return onoff[level];
  }
  static void set_default_action(int loglev, int action) {
    assert (loglev >= 0 && loglev < N_LOGLEV);
    assert (action >= 0 && action < N_ACT);
    default_onoff[loglev] = action;
  }
  static int get_default_action(int loglev) {
    assert (loglev >= 0 && loglev < N_LOGLEV);
    return default_onoff[loglev];
  }
} logfunc_t;

#define BX_LOGPREFIX_LEN 20

class BOCHSAPI iofunctions {
  int magic;
  char logprefix[BX_LOGPREFIX_LEN + 1];
  FILE *logfd;
  class logfunctions *log;
  void init(void);
  void flush(void);

// Log Class types
public:
  iofunctions(void);
  iofunctions(FILE *);
  iofunctions(int);
  iofunctions(const char *);
 ~iofunctions(void);

  void out(int level, const char *pre, const char *fmt, va_list ap);

  void init_log(const char *fn);
  void init_log(int fd);
  void init_log(FILE *fs);
  void exit_log();
  void set_log_prefix(const char *prefix);
  int get_n_logfns() const { return n_logfn; }
  logfunc_t *get_logfn(int index) { return logfn_list[index]; }
  void add_logfn(logfunc_t *fn);
  void remove_logfn(logfunc_t *fn);
  void set_log_action(int loglevel, int action);
  const char *getlevel(int i) const;
  const char *getaction(int i) const;
  int isaction(const char *val) const;

protected:
  int n_logfn;
#define MAX_LOGFNS 512
  logfunc_t *logfn_list[MAX_LOGFNS];
  const char *logfn;
};

typedef class iofunctions iofunc_t;

#define SAFE_GET_IOFUNC() \
  ((io==NULL)? (io=new iofunc_t("/dev/stderr")) : io)
#define SAFE_GET_GENLOG() \
  ((genlog==NULL)? (genlog=new logfunc_t(SAFE_GET_IOFUNC())) : genlog)

#if BX_NO_LOGGING

#define BX_INFO(x)
#define BX_DEBUG(x)
#define BX_ERROR(x)
#define BX_PANIC(x) (LOG_THIS panic) x
#define BX_FATAL(x) (LOG_THIS fatal1) x

#define BX_ASSERT(x)

#else

#define BX_INFO(x)  (LOG_THIS info) x
#define BX_DEBUG(x) (LOG_THIS ldebug) x
#define BX_ERROR(x) (LOG_THIS error) x
#define BX_PANIC(x) (LOG_THIS panic) x
#define BX_FATAL(x) (LOG_THIS fatal1) x

#if BX_ASSERT_ENABLE
  #define BX_ASSERT(x) do {if (!(x)) BX_PANIC(("failed assertion \"%s\" at %s:%d\n", #x, __FILE__, __LINE__));} while (0)
#else
  #define BX_ASSERT(x)
#endif

#endif

BOCHSAPI extern iofunc_t *io;
BOCHSAPI extern logfunc_t *genlog;

#ifndef UNUSED
#  define UNUSED(x) ((void)x)
#endif

//Generic MAX and MIN Functions
#define BX_MAX(a,b) ((a) > (b) ? (a) : (b))
#define BX_MIN(a,b) ((a) < (b) ? (a) : (b))

#if BX_SUPPORT_X86_64
#define FMT_ADDRX FMT_ADDRX64
#else
#define FMT_ADDRX FMT_ADDRX32
#endif

#if BX_PHY_ADDRESS_LONG
  #define FMT_PHY_ADDRX FMT_PHY_ADDRX64
#else
  #define FMT_PHY_ADDRX FMT_ADDRX32
#endif

#define FMT_LIN_ADDRX FMT_ADDRX

#if BX_GDBSTUB
// defines for GDB stub
void bx_gdbstub_init(void);
void bx_gdbstub_break(void);
int bx_gdbstub_check(unsigned int eip);
#define GDBSTUB_STOP_NO_REASON   (0xac0)

#if BX_SUPPORT_SMP
#error GDB stub was written for single processor support.  If multiprocessor support is added, then we can remove this check.
// The big problem is knowing which CPU gdb is referring to.  In other words,
// what should we put for "n" in BX_CPU(n)->dbg_xlate_linear2phy() and
// BX_CPU(n)->dword.eip, etc.
#endif
#endif

typedef struct {
  bx_bool interrupts;
  bx_bool exceptions;
  bx_bool print_timestamps;
#if BX_DEBUGGER
  bx_bool magic_break_enabled;
#endif
#if BX_GDBSTUB
  bx_bool gdbstub_enabled;
#endif
#if BX_SUPPORT_APIC
  bx_bool apic;
#endif
#if BX_DEBUG_LINUX
  bx_bool linux_syscall;
#endif
} bx_debug_t;

#if BX_SHOW_IPS
BOCHSAPI_MSVCONLY void bx_show_ips_handler(void);
#endif
void CDECL bx_signal_handler(int signum);
int bx_atexit(void);
BOCHSAPI extern bx_debug_t bx_dbg;

#if BX_SUPPORT_APIC
// determinted by XAPIC option
BOCHSAPI extern Bit32u apic_id_mask;
#endif

// memory access type (read/write/execute/rw)
#define BX_READ         0
#define BX_WRITE        1
#define BX_EXECUTE      2
#define BX_RW           3

// types of reset
#define BX_RESET_SOFTWARE 10
#define BX_RESET_HARDWARE 11

#include "memory/memory-bochs.h"
#include "pc_system.h"
#include "gui/gui.h"

/* --- EXTERNS --- */

#if BX_GUI_SIGHANDLER
extern bx_bool bx_gui_sighandler;
#endif

// This value controls how often each I/O device's timer handler
// gets called.  The timer is set up in iodev/devices.cc.
#define BX_IODEV_HANDLER_PERIOD 1000   // microseconds

#define BX_PATHNAME_LEN 512

#define BX_KBD_XT_TYPE        0
#define BX_KBD_AT_TYPE        1
#define BX_KBD_MF_TYPE        2

#define BX_N_OPTROM_IMAGES 4
#define BX_N_OPTRAM_IMAGES 4
#define BX_N_SERIAL_PORTS 4
#define BX_N_PARALLEL_PORTS 2
#define BX_N_PCI_SLOTS 5
#define BX_N_USER_PLUGINS 8

void bx_center_print(FILE *file, const char *line, unsigned maxwidth);

#include "instrument.h"

BX_CPP_INLINE Bit16u bx_bswap16(Bit16u val16)
{
  return (val16<<8) | (val16>>8);
}

#if !defined(__MORPHOS__)
#if BX_HAVE___BUILTIN_BSWAP32
#define bx_bswap32 __builtin_bswap32
#else
BX_CPP_INLINE Bit32u bx_bswap32(Bit32u val32)
{
  val32 = ((val32<<8) & 0xFF00FF00) | ((val32>>8) & 0x00FF00FF);
  return (val32<<16) | (val32>>16);
}
#endif

#if BX_HAVE___BUILTIN_BSWAP64
#define bx_bswap64 __builtin_bswap64
#else
BX_CPP_INLINE Bit64u bx_bswap64(Bit64u val64)
{
  Bit32u lo = bx_bswap32((Bit32u)(val64 >> 32));
  Bit32u hi = bx_bswap32((Bit32u)(val64 & 0xFFFFFFFF));
  return ((Bit64u)hi << 32) | (Bit64u)lo;
}
#endif
#endif // !MorphOS

// These are some convenience macros which abstract out accesses between
// a variable in native byte ordering to/from guest (x86) memory, which is
// always in little endian format.  You must deal with alignment (if your
// system cares) and endian rearranging.  Don't assume anything.  You could
// put some platform specific asm() statements here, to make use of native
// instructions to help perform these operations more efficiently than C++.

#ifdef BX_LITTLE_ENDIAN

#define WriteHostWordToLittleEndian(hostPtr, nativeVar16) \
    *((Bit16u*)(hostPtr)) = (nativeVar16)
#define WriteHostDWordToLittleEndian(hostPtr, nativeVar32) \
    *((Bit32u*)(hostPtr)) = (nativeVar32)
#ifdef ANDROID
// Resolve problems with unaligned access
#define WriteHostQWordToLittleEndian(hostPtr, nativeVar64) { \
    ((Bit8u *)(hostPtr))[0] = (Bit8u) (nativeVar64); \
    ((Bit8u *)(hostPtr))[1] = (Bit8u) ((nativeVar64)>>8); \
    ((Bit8u *)(hostPtr))[2] = (Bit8u) ((nativeVar64)>>16); \
    ((Bit8u *)(hostPtr))[3] = (Bit8u) ((nativeVar64)>>24); \
    ((Bit8u *)(hostPtr))[4] = (Bit8u) ((nativeVar64)>>32); \
    ((Bit8u *)(hostPtr))[5] = (Bit8u) ((nativeVar64)>>40); \
    ((Bit8u *)(hostPtr))[6] = (Bit8u) ((nativeVar64)>>48); \
    ((Bit8u *)(hostPtr))[7] = (Bit8u) ((nativeVar64)>>56); \
}
#else
#define WriteHostQWordToLittleEndian(hostPtr, nativeVar64) \
    *((Bit64u*)(hostPtr)) = (nativeVar64)
#endif
#define ReadHostWordFromLittleEndian(hostPtr, nativeVar16) \
    (nativeVar16) = *((Bit16u*)(hostPtr))
#define ReadHostDWordFromLittleEndian(hostPtr, nativeVar32) \
    (nativeVar32) = *((Bit32u*)(hostPtr))
#ifdef ANDROID
// Resolve problems with unaligned access
#define ReadHostQWordFromLittleEndian(hostPtr, nativeVar64) { \
    (nativeVar64) = ((Bit64u) ((Bit8u *)(hostPtr))[0]) | \
    (((Bit64u) ((Bit8u *)(hostPtr))[1])<<8) | \
    (((Bit64u) ((Bit8u *)(hostPtr))[2])<<16) | \
    (((Bit64u) ((Bit8u *)(hostPtr))[3])<<24) | \
    (((Bit64u) ((Bit8u *)(hostPtr))[4])<<32) | \
    (((Bit64u) ((Bit8u *)(hostPtr))[5])<<40) | \
    (((Bit64u) ((Bit8u *)(hostPtr))[6])<<48) | \
    (((Bit64u) ((Bit8u *)(hostPtr))[7])<<56); \
}
#else
#define ReadHostQWordFromLittleEndian(hostPtr, nativeVar64) \
    (nativeVar64) = *((Bit64u*)(hostPtr))
#endif

#else 

#ifdef __MORPHOS__

#define bx_bswap16 bx_ppc_bswap16
#define bx_bswap32 bx_ppc_bswap32
#define bx_bswap64 bx_ppc_bswap64

#define WriteHostWordToLittleEndian(hostPtr, nativeVar16) {        \
    bx_ppc_store_le16((Bit16u *)(hostPtr), (Bit16u)(nativeVar16)); \
}
#define WriteHostDWordToLittleEndian(hostPtr, nativeVar32) {       \
    bx_ppc_store_le32((Bit32u *)(hostPtr), (Bit32u)(nativeVar32)); \
}
#define WriteHostQWordToLittleEndian(hostPtr, nativeVar64) {       \
    bx_ppc_store_le64((Bit64u *)(hostPtr), (Bit64u)(nativeVar64)); \
}

#define ReadHostWordFromLittleEndian(hostPtr, nativeVar16) {  \
    (nativeVar16) =  bx_ppc_load_le16((Bit16u *)(hostPtr));   \
}
#define ReadHostDWordFromLittleEndian(hostPtr, nativeVar32) { \
    (nativeVar32) =  bx_ppc_load_le32((Bit32u *)(hostPtr));   \
}
#define ReadHostQWordFromLittleEndian(hostPtr, nativeVar64) { \
    (nativeVar64) =  bx_ppc_load_le64((Bit64u *)(hostPtr));   \
}

#else

#define WriteHostWordToLittleEndian(hostPtr,  nativeVar16) {  \
    *(Bit16u *)(hostPtr) = bx_bswap16((Bit16u)(nativeVar16)); \
}
#define WriteHostDWordToLittleEndian(hostPtr, nativeVar32) {  \
    *(Bit32u *)(hostPtr) = bx_bswap32((Bit32u)(nativeVar32)); \
}
#define WriteHostQWordToLittleEndian(hostPtr, nativeVar64) {  \
    *(Bit64u *)(hostPtr) = bx_bswap64((Bit64u)(nativeVar64)); \
}

#define ReadHostWordFromLittleEndian(hostPtr, nativeVar16) {  \
    (nativeVar16) =  bx_bswap16(*(Bit16u *)(hostPtr));        \
}
#define ReadHostDWordFromLittleEndian(hostPtr, nativeVar32) { \
    (nativeVar32) =  bx_bswap32(*(Bit32u *)(hostPtr));        \
}
#define ReadHostQWordFromLittleEndian(hostPtr, nativeVar64) { \
    (nativeVar64) =  bx_bswap64(*(Bit64u *)(hostPtr));        \
}

#endif

#endif

#define CopyHostWordLittleEndian(hostAddrDst,  hostAddrSrc)  \
    (* (Bit16u *)(hostAddrDst)) = (* (Bit16u *)(hostAddrSrc));
#define CopyHostDWordLittleEndian(hostAddrDst,  hostAddrSrc) \
    (* (Bit32u *)(hostAddrDst)) = (* (Bit32u *)(hostAddrSrc));
#define CopyHostQWordLittleEndian(hostAddrDst,  hostAddrSrc) \
    (* (Bit64u *)(hostAddrDst)) = (* (Bit64u *)(hostAddrSrc));

// multithreading support
#ifdef WIN32
#define BX_THREAD_ID(id) DWORD (id)
#define BX_THREAD_FUNC(name,arg) DWORD WINAPI name(LPVOID arg)
#define BX_THREAD_EXIT return 0
#define BX_THREAD_CREATE(name,arg,id) CreateThread(NULL, 0, name, arg, 0, &(id))
#define BX_LOCK(mutex) EnterCriticalSection(&(mutex))
#define BX_UNLOCK(mutex) LeaveCriticalSection(&(mutex))
#define BX_MUTEX(mutex) CRITICAL_SECTION (mutex)
#define BX_INIT_MUTEX(mutex)  InitializeCriticalSection(&(mutex))
#define BX_FINI_MUTEX(mutex) DeleteCriticalSection(&(mutex))
#define BX_MSLEEP(val) Sleep(val)
#else
#define BX_THREAD_ID(id) pthread_t (id)
#define BX_THREAD_FUNC(name,arg) void name(void* arg)
#define BX_THREAD_EXIT pthread_exit(NULL)
#define BX_THREAD_CREATE(name,arg,id) \
    pthread_create(&(id), NULL, (void *(*)(void *))&(name), arg)
#define BX_LOCK(mutex) pthread_mutex_lock(&(mutex));
#define BX_UNLOCK(mutex) pthread_mutex_unlock(&(mutex));
#define BX_MUTEX(mutex) pthread_mutex_t (mutex)
#define BX_INIT_MUTEX(mutex) pthread_mutex_init(&(mutex),NULL)
#define BX_FINI_MUTEX(mutex) pthread_mutex_destroy(&(mutex))
#define BX_MSLEEP(val) usleep(val*1000)
#endif

#endif  /* BX_BOCHS_H */
