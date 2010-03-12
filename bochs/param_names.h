/////////////////////////////////////////////////////////////////////////
// $Id: param_names.h,v 1.5 2010-03-12 11:28:59 sshwarts Exp $
/////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2009  The Bochs Project
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
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
//
/////////////////////////////////////////////////////////////////////////

#ifndef BX_PARAM_NAMES
#define BX_PARAM_NAMES

// define parameter path names.  These names give the location in the
// parameter tree where each can be found.  The names correspond to
// the old BXP_* enum values, which have been eliminated.
#define BXPN_SEL_CONFIG_INTERFACE        "general.config_interface"
#define BXPN_BOCHS_START                 "general.start_mode"
#define BXPN_BOCHS_BENCHMARK             "general.benchmark"
#define BXPN_RESTORE_FLAG                "general.restore"
#define BXPN_RESTORE_PATH                "general.restore_path"
#define BXPN_DEBUG_RUNNING               "general.debug_running"
#define BXPN_CPU_NPROCESSORS             "cpu.n_processors"
#define BXPN_CPU_NCORES                  "cpu.n_cores"
#define BXPN_CPU_NTHREADS                "cpu.n_threads"
#define BXPN_IPS                         "cpu.ips"
#define BXPN_SMP_QUANTUM                 "cpu.quantum"
#define BXPN_RESET_ON_TRIPLE_FAULT       "cpu.reset_on_triple_fault"
#define BXPN_IGNORE_BAD_MSRS             "cpu.ignore_bad_msrs"
#define BXPN_CONFIGURABLE_MSRS_PATH      "cpu.msrs"
#define BXPN_VENDOR_STRING               "cpuid.vendor_string"
#define BXPN_BRAND_STRING                "cpuid.brand_string"
#define BXPN_CPUID_LIMIT_WINNT           "cpuid.cpuid_limit_winnt"
#define BXPN_CPUID_MMX                   "cpuid.mmx"
#define BXPN_CPUID_SSE                   "cpuid.sse"
#define BXPN_CPUID_AES                   "cpuid.aes"
#define BXPN_CPUID_MOVBE                 "cpuid.movbe"
#define BXPN_CPUID_SEP                   "cpuid.sep"
#define BXPN_CPUID_XSAVE                 "cpuid.xsave"
#define BXPN_CPUID_XAPIC                 "cpuid.xapic"
#define BXPN_CPUID_MWAIT_IS_NOP          "cpuid.mwait_is_nop"
#define BXPN_MEM_SIZE                    "memory.standard.ram.size"
#define BXPN_HOST_MEM_SIZE               "memory.standard.ram.host_size"
#define BXPN_ROM_PATH                    "memory.standard.rom.path"
#define BXPN_ROM_ADDRESS                 "memory.standard.rom.addr"
#define BXPN_VGA_ROM_PATH                "memory.standard.vgarom.path"
#define BXPN_OPTROM1_PATH                "memory.optrom.1.path"
#define BXPN_OPTROM1_ADDRESS             "memory.optrom.1.addr"
#define BXPN_OPTROM2_PATH                "memory.optrom.2.path"
#define BXPN_OPTROM2_ADDRESS             "memory.optrom.2.addr"
#define BXPN_OPTROM3_PATH                "memory.optrom.3.path"
#define BXPN_OPTROM3_ADDRESS             "memory.optrom.3.addr"
#define BXPN_OPTROM4_PATH                "memory.optrom.4.path"
#define BXPN_OPTROM4_ADDRESS             "memory.optrom.4.addr"
#define BXPN_OPTRAM1_PATH                "memory.optram.1.path"
#define BXPN_OPTRAM1_ADDRESS             "memory.optram.1.addr"
#define BXPN_OPTRAM2_PATH                "memory.optram.2.path"
#define BXPN_OPTRAM2_ADDRESS             "memory.optram.2.addr"
#define BXPN_OPTRAM3_PATH                "memory.optram.3.path"
#define BXPN_OPTRAM3_ADDRESS             "memory.optram.3.addr"
#define BXPN_OPTRAM4_PATH                "memory.optram.4.path"
#define BXPN_OPTRAM4_ADDRESS             "memory.optram.4.addr"
#define BXPN_CLOCK_SYNC                  "clock_cmos.clock_sync"
#define BXPN_CLOCK_TIME0                 "clock_cmos.time0"
#define BXPN_CMOSIMAGE_ENABLED           "clock_cmos.cmosimage.enabled"
#define BXPN_CMOSIMAGE_PATH              "clock_cmos.cmosimage.path"
#define BXPN_CMOSIMAGE_RTC_INIT          "clock_cmos.cmosimage.rtc_init"
#define BXPN_I440FX_SUPPORT              "pci.i440fx_support"
#define BXPN_PCIDEV_VENDOR               "pci.pcidev.vendor"
#define BXPN_PCIDEV_DEVICE               "pci.pcidev.device"
#define BXPN_SEL_DISPLAY_LIBRARY         "display.display_library"
#define BXPN_DISPLAYLIB_OPTIONS          "display.displaylib_options"
#define BXPN_PRIVATE_COLORMAP            "display.private_colormap"
#define BXPN_FULLSCREEN                  "display.fullscreen"
#define BXPN_SCREENMODE                  "display.screenmode"
#define BXPN_VGA_EXTENSION               "display.vga_extension"
#define BXPN_VGA_UPDATE_INTERVAL         "display.vga_update_interval"
#define BXPN_KBD_TYPE                    "keyboard_mouse.keyboard.type"
#define BXPN_KBD_SERIAL_DELAY            "keyboard_mouse.keyboard.serial_delay"
#define BXPN_KBD_PASTE_DELAY             "keyboard_mouse.keyboard.paste_delay"
#define BXPN_KBD_USEMAPPING              "keyboard_mouse.keyboard.use_mapping"
#define BXPN_KBD_KEYMAP                  "keyboard_mouse.keyboard.keymap"
#define BXPN_USER_SHORTCUT               "keyboard_mouse.keyboard.user_shortcut"
#define BXPN_MOUSE_TYPE                  "keyboard_mouse.mouse.type"
#define BXPN_MOUSE_ENABLED               "keyboard_mouse.mouse.enabled"
#define BXPN_BOOTDRIVE1                  "boot_params.boot_drive1"
#define BXPN_BOOTDRIVE2                  "boot_params.boot_drive2"
#define BXPN_BOOTDRIVE3                  "boot_params.boot_drive3"
#define BXPN_FLOPPYSIGCHECK              "boot_params.floppy_sig_check"
#define BXPN_LOAD32BITOS_WHICH           "boot_params.load32bitos.which"
#define BXPN_LOAD32BITOS_PATH            "boot_params.load32bitos.path"
#define BXPN_LOAD32BITOS_IOLOG           "boot_params.load32bitos.iolog"
#define BXPN_LOAD32BITOS_INITRD          "boot_params.load32bitos.initrd"
#define BXPN_FLOPPYA                     "floppy.0"
#define BXPN_FLOPPYA_DEVTYPE             "floppy.0.devtype"
#define BXPN_FLOPPYA_PATH                "floppy.0.path"
#define BXPN_FLOPPYA_TYPE                "floppy.0.type"
#define BXPN_FLOPPYA_STATUS              "floppy.0.status"
#define BXPN_FLOPPYB                     "floppy.1"
#define BXPN_FLOPPYB_DEVTYPE             "floppy.1.devtype"
#define BXPN_FLOPPYB_PATH                "floppy.1.path"
#define BXPN_FLOPPYB_TYPE                "floppy.1.type"
#define BXPN_FLOPPYB_STATUS              "floppy.1.status"
#define BXPN_ATA0_RES                    "ata.0.resources"
#define BXPN_ATA1_RES                    "ata.1.resources"
#define BXPN_ATA2_RES                    "ata.2.resources"
#define BXPN_ATA3_RES                    "ata.3.resources"
#define BXPN_ATA0_ENABLED                "ata.0.resources.enabled"
#define BXPN_ATA1_ENABLED                "ata.1.resources.enabled"
#define BXPN_ATA0_MASTER                 "ata.0.master"
#define BXPN_ATA1_MASTER                 "ata.1.master"
#define BXPN_ATA2_MASTER                 "ata.2.master"
#define BXPN_ATA3_MASTER                 "ata.3.master"
#define BXPN_ATA0_SLAVE                  "ata.0.slave"
#define BXPN_ATA1_SLAVE                  "ata.1.slave"
#define BXPN_ATA2_SLAVE                  "ata.2.slave"
#define BXPN_ATA3_SLAVE                  "ata.3.slave"
#define BXPN_USB_UHCI                    "ports.usb.uhci"
#define BXPN_UHCI_ENABLED                "ports.usb.uhci.enabled"
#define BXPN_UHCI_PORT1                  "ports.usb.uhci.port1"
#define BXPN_UHCI_PORT2                  "ports.usb.uhci.port2"
#define BXPN_USB_OHCI                    "ports.usb.ohci"
#define BXPN_OHCI_ENABLED                "ports.usb.ohci.enabled"
#define BXPN_OHCI_PORT1                  "ports.usb.ohci.port1"
#define BXPN_OHCI_PORT2                  "ports.usb.ohci.port2"
#define BXPN_NE2K                        "network.ne2k"
#define BXPN_NE2K_ENABLED                "network.ne2k.enabled"
#define BXPN_PNIC                        "network.pnic"
#define BXPN_PNIC_ENABLED                "network.pnic.enabled"
#define BXPN_SB16                        "sound.sb16"
#define BXPN_SB16_ENABLED                "sound.sb16.enabled"
#define BXPN_SB16_MIDIFILE               "sound.sb16.midifile"
#define BXPN_SB16_WAVEFILE               "sound.sb16.wavefile"
#define BXPN_SB16_DMATIMER               "sound.sb16.dmatimer"
#define BXPN_SB16_LOGLEVEL               "sound.sb16.loglevel"
#define BXPN_PORT_E9_HACK                "misc.port_e9_hack"
#define BXPN_TEXT_SNAPSHOT_CHECK         "misc.text_snapshot_check"
#define BXPN_GDBSTUB                     "misc.gdbstub"
#define BXPN_PLUGIN_CTRL                 "misc.plugin_ctrl"
#define BXPN_LOG_FILENAME                "log.filename"
#define BXPN_LOG_PREFIX                  "log.prefix"
#define BXPN_DEBUGGER_LOG_FILENAME       "log.debugger_filename"
#define BXPN_MENU_DISK                   "menu.disk"
#define BXPN_MENU_DISK_WIN32             "menu.disk_win32"
#define BXPN_MENU_MEMORY                 "menu.memory"
#define BXPN_MENU_RUNTIME_CDROM          "menu.runtime.cdrom"
#define BXPN_MENU_RUNTIME_USB            "menu.runtime.usb"
#define BXPN_MENU_RUNTIME_MISC           "menu.runtime.misc"
#define BXPN_WX_KBD_STATE                "wxdebug.keyboard"
#define BXPN_WX_CPU_STATE                "wxdebug.cpu"
#define BXPN_WX_CPU0_STATE               "wxdebug.cpu.0"
#define BXPN_WX_CPU0_EFLAGS_IOPL         "wxdebug.cpu.0.IOPL"

#endif
