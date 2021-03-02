/*
 * Copyright (c) 2014 Google Inc. All rights reserved
 * Contributed by Stephane Eranian <eranian@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of libpfm, a performance monitoring support library for
 * applications on Linux.
 *
 * PMU: hswep_unc_ha (Intel Haswell-EP HA uncore PMU)
 */

static const intel_x86_umask_t hswep_unc_h_directory_lookup[]={
  { .uname = "NO_SNP",
    .udesc  = "Snoop not needed",
    .ucode  = 0x200,
  },
  { .uname = "SNOOP",
    .udesc  = "SNooop needed",
    .ucode  = 0x100,
  },
};

static const intel_x86_umask_t hswep_unc_h_bypass_imc[]={
  { .uname = "TAKEN",
    .udesc  = "Bypass taken",
    .ucode  = 0x100,
  },
  { .uname = "NOT_TAKEN",
    .udesc  = "Bypass not taken",
    .ucode  = 0x200,
  },
};

static const intel_x86_umask_t hswep_unc_h_directory_update[]={
  { .uname = "ANY",
    .udesc  = "Counts any directory update",
    .ucode  = 0x300,
    .uflags = INTEL_X86_NCOMBO | INTEL_X86_DFL,
  },
  { .uname = "CLEAR",
    .udesc  = "Directory clears",
    .ucode  = 0x200,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "SET",
    .udesc  = "Directory set",
    .ucode  = 0x100,
    .uflags = INTEL_X86_NCOMBO,
  },
};

static const intel_x86_umask_t hswep_unc_h_hitme_hit[]={
  { .uname = "ALL",
    .udesc  = "All requests",
    .ucode  = 0xff00,
    .uflags = INTEL_X86_NCOMBO | INTEL_X86_DFL,
  },
  { .uname = "READ_OR_INVITOE",
    .udesc  = "Number of hits with opcode RdCode, RdData, RdDataMigratory, RdInvOwn, RdCur or InvToE",
    .ucode  = 0x100,
  },
  { .uname = "WBMTOI",
    .udesc  = "Number of hits with opcode WbToMtoI",
    .ucode  = 0x200,
  },
  { .uname = "ACKCNFLTWBI",
    .udesc  = "Number of hits with opcode AckCnfltWbI",
    .ucode  = 0x400,
  },
  { .uname = "WBMTOE_OR_S",
    .udesc  = "Number of hits with opcode WbMtoE or WbMtoS",
    .ucode  = 0x800,
  },
  { .uname = "HOM",
    .udesc  = "Number of hits with HOM requests",
    .ucode  = 0xf00,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "RSPFWDI_REMOTE",
    .udesc  = "Number of hits with opcode RspIFwd, RspIFwdWb for remore requests",
    .ucode  = 0x1000,
  },
  { .uname = "RSPFWDI_LOCAL",
    .udesc  = "Number of hits with opcode RspIFwd, RspIFwdWb for local requests",
    .ucode  = 0x2000,
  },
  { .uname = "INVALS",
    .udesc  = "Number of hits for invalidations",
    .ucode  = 0x2600,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "RSPFWDS",
    .udesc  = "Number of hits with opcode RsSFwd, RspSFwdWb",
    .ucode  = 0x4000,
  },
  { .uname = "EVICTS",
    .udesc  = "Number of hits for allocations",
    .ucode  = 0x4200,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "ALLOCS",
    .udesc  = "Number of hits for allocations",
    .ucode  = 0x7000,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "RSP",
    .udesc  = "Number of hits with opcode RspI, RspIWb, RspSWb, RspCnflt, RspCnfltWbI",
    .ucode  = 0x8000,
  }
};

static const intel_x86_umask_t hswep_unc_h_hitme_hit_pv_bits_set[]={
  { .uname = "ALL",
    .udesc  = "All requests",
    .ucode  = 0xff00,
    .uflags = INTEL_X86_NCOMBO | INTEL_X86_DFL,
  },
  { .uname = "READ_OR_INVITOE",
    .udesc  = "Number of hits with opcode RdCode, RdData, RdDataMigratory, RdInvOwn, RdCur or InvToE",
    .ucode  = 0x100,
  },
  { .uname = "WBMTOI",
    .udesc  = "Number of hits with opcode WbToMtoI",
    .ucode  = 0x200,
  },
  { .uname = "ACKCNFLTWBI",
    .udesc  = "Number of hits with opcode AckCnfltWbI",
    .ucode  = 0x400,
  },
  { .uname = "WBMTOE_OR_S",
    .udesc  = "Number of hits with opcode WbMtoE or WbMtoS",
    .ucode  = 0x800,
  },
  { .uname = "HOM",
    .udesc  = "Number of hits with HOM requests",
    .ucode  = 0xf00,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "RSPFWDI_REMOTE",
    .udesc  = "Number of hits with opcode RspIFwd, RspIFwdWb for remore requests",
    .ucode  = 0x1000,
  },
  { .uname = "RSPFWDI_LOCAL",
    .udesc  = "Number of hits with opcode RspIFwd, RspIFwdWb for local requests",
    .ucode  = 0x2000,
  },
  { .uname = "RSPFWDS",
    .udesc  = "Number of hits with opcode RsSFwd, RspSFwdWb",
    .ucode  = 0x4000,
  },
  { .uname = "RSP",
    .udesc  = "Number of hits with opcode RspI, RspIWb, RspSWb, RspCnflt, RspCnfltWbI",
    .ucode  = 0x8000,
  }
};

static const intel_x86_umask_t hswep_unc_h_igr_no_credit_cycles[]={
  { .uname = "AD_QPI0",
    .udesc  = "AD to QPI link 0",
    .ucode  = 0x100,
  },
  { .uname = "AD_QPI1",
    .udesc  = "AD to QPI link 1",
    .ucode  = 0x200,
  },
  { .uname = "BL_QPI0",
    .udesc  = "BL to QPI link 0",
    .ucode  = 0x400,
  },
  { .uname = "BL_QPI1",
    .udesc  = "BL to QPI link 1",
    .ucode  = 0x800,
  },
  { .uname = "AD_QPI2",
    .udesc  = "AD to QPI link 2",
    .ucode  = 0x1000,
  },
  { .uname = "BL_QPI2",
    .udesc  = "BL to QPI link 2",
    .ucode  = 0x2000,
  },
};

static const intel_x86_umask_t hswep_unc_h_imc_writes[]={
  { .uname = "ALL",
    .udesc  = "Counts all writes",
    .ucode  = 0xf00,
    .uflags = INTEL_X86_NCOMBO | INTEL_X86_DFL,
  },
  { .uname = "FULL",
    .udesc  = "Counts full line non ISOCH",
    .ucode  = 0x100,
  },
  { .uname = "PARTIAL",
    .udesc  = "Counts partial non-ISOCH",
    .ucode  = 0x200,
  },
  { .uname = "FULL_ISOCH",
    .udesc  = "Counts ISOCH full line",
    .ucode  = 0x400,
  },
  { .uname = "PARTIAL_ISOCH",
    .udesc  = "Counts ISOCH partial",
    .ucode  = 0x800,
  },
};

static const intel_x86_umask_t hswep_unc_h_imc_reads[]={
  { .uname = "NORMAL",
    .udesc  = "Normal priority",
    .ucode  = 0x100,
    .uflags = INTEL_X86_DFL,
  },
};

static const intel_x86_umask_t hswep_unc_h_requests[]={
  { .uname = "READS",
    .udesc  = "Counts incoming read requests. Good proxy for LLC read misses, incl. RFOs",
    .ucode  = 0x300,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "READS_LOCAL",
    .udesc  = "Counts incoming read requests coming from local socket. Good proxy for LLC read misses, incl. RFOs from the local socket",
    .ucode  = 0x100,
  },
  { .uname = "READS_REMOTE",
    .udesc  = "Counts incoming read requests coming from remote socket. Good proxy for LLC read misses, incl. RFOs from the remote socket",
    .ucode  = 0x200,
  },
  { .uname = "WRITES",
    .udesc  = "Counts incoming writes",
    .ucode  = 0xc00,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "WRITES_LOCAL",
    .udesc  = "Counts incoming writes from local socket",
    .ucode  = 0x400,
  },
  { .uname = "WRITES_REMOTE",
    .udesc  = "Counts incoming writes from remote socket",
    .ucode  = 0x800,
  },
  { .uname = "INVITOE_LOCAL",
    .udesc  = "Counts InvItoE coming from local socket",
    .ucode  = 0x1000,
  },
  { .uname = "INVITOE_REMOTE",
    .udesc  = "Counts InvItoE coming from remote socket",
    .ucode  = 0x2000,
  }
};

static const intel_x86_umask_t hswep_unc_h_rpq_cycles_no_reg_credits[]={
  { .uname = "CHN0",
    .udesc  = "Channel 0",
    .ucode  = 0x100,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "CHN1",
    .udesc  = "Channel 1",
    .ucode  = 0x200,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "CHN2",
    .udesc  = "channel 2",
    .ucode  = 0x400,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "CHN3",
    .udesc  = "Chanel 3",
    .ucode  = 0x800,
    .uflags = INTEL_X86_NCOMBO,
  },
};

static const intel_x86_umask_t hswep_unc_h_tad_requests_g0[]={
  { .uname = "REGION0",
    .udesc  = "Counts for TAD Region 0",
    .ucode  = 0x100,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "REGION1",
    .udesc  = "Counts for TAD Region 1",
    .ucode  = 0x200,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "REGION2",
    .udesc  = "Counts for TAD Region 2",
    .ucode  = 0x400,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "REGION3",
    .udesc  = "Counts for TAD Region 3",
    .ucode  = 0x800,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "REGION4",
    .udesc  = "Counts for TAD Region 4",
    .ucode  = 0x1000,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "REGION5",
    .udesc  = "Counts for TAD Region 5",
    .ucode  = 0x2000,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "REGION6",
    .udesc  = "Counts for TAD Region 6",
    .ucode  = 0x4000,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "REGION7",
    .udesc  = "Counts for TAD Region 7",
    .ucode  = 0x8000,
    .uflags = INTEL_X86_NCOMBO,
  },
};

static const intel_x86_umask_t hswep_unc_h_tad_requests_g1[]={
  { .uname = "REGION8",
    .udesc  = "Counts for TAD Region 8",
    .ucode  = 0x100,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "REGION9",
    .udesc  = "Counts for TAD Region 9",
    .ucode  = 0x200,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "REGION10",
    .udesc  = "Counts for TAD Region 10",
    .ucode  = 0x400,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "REGION11",
    .udesc  = "Counts for TAD Region 11",
    .ucode  = 0x800,
    .uflags = INTEL_X86_NCOMBO,
  },
};

static const intel_x86_umask_t hswep_unc_h_snoop_resp[]={
  { .uname = "RSPI",
    .udesc  = "Filters for snoop responses of RspI. RspI is returned when the remote cache does not have the data or when the remote cache silently evicts data (e.g. RFO hit non-modified line)",
    .ucode  = 0x100,
  },
  { .uname = "RSPS",
    .udesc  = "Filters for snoop responses of RspS. RspS is returned when the remote cache has the data but is not forwarding it. It is a way to let the requesting socket know that it cannot allocate the data in E-state",
    .ucode  = 0x200,
  },
  { .uname = "RSPIFWD",
    .udesc  = "Filters for snoop responses of RspIFwd. RspIFwd is returned when the remote cache agent forwards data and the requesting agent is able to acquire the data in E or M state. This is commonly returned with RFO transacations. It can be either HitM or HitFE",
    .ucode  = 0x400,
  },
  { .uname = "RSPSFWD",
    .udesc  = "Filters for snoop responses of RspSFwd. RspSFwd is returned when the remote cache agent forwards data  but holds on to its current copy. This is common for data and code reads that hit in a remote socket in E or F state",
    .ucode  = 0x800,
  },
  { .uname = "RSP_WB",
    .udesc  = "Filters for snoop responses of RspIWB or RspSWB. This is returned when a non-RFO requests hits in M-state. Data and code reads can return either RspIWB or RspSWB depending on how the system has been configured. InvItoE transactions will also return RspIWB because they must acquire ownership",
    .ucode  = 0x1000,
  },
  { .uname = "RSP_FWD_WB",
    .udesc  = "Filters for snoop responses of RspxFwdxWB. This snoop response is only used in 4s systems. It is used when a snoop HITM in a remote caching agent and it directly forwards data to a requester and simultaneously returns data to the home to be written back to memory",
    .ucode  = 0x2000,
  },
  { .uname = "RSPCNFLCT",
    .udesc  = "Filters for snoop responses of RspConflict. This is returned when a snoop finds an existing outstanding transaction in a remote caching agent when it CMAs that caching agent. This triggers the conflict resolution hardware. This covers both RspConflct and RspCnflctWBI",
    .ucode  = 0x4000,
  },
};

static const intel_x86_umask_t hswep_unc_h_txr_ad_cycles_full[]={
  { .uname = "ALL",
    .udesc  = "Counts cycles full from both schedulers",
    .ucode  = 0x300,
    .uflags = INTEL_X86_NCOMBO | INTEL_X86_DFL,
  },
  { .uname = "SCHED0",
    .udesc  = "Counts cycles full from scheduler bank 0",
    .ucode  = 0x100,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "SCHED1",
    .udesc  = "Counts cycles full from scheduler bank 1",
    .ucode  = 0x200,
    .uflags = INTEL_X86_NCOMBO,
  },
};

static const intel_x86_umask_t hswep_unc_h_txr_bl_occupancy[]={
  { .uname = "SCHED0",
    .udesc  = "Counts cycles full from scheduler bank 0",
    .ucode  = 0x100,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "SCHED1",
    .udesc  = "Counts cycles full from scheduler bank 1",
    .ucode  = 0x200,
    .uflags = INTEL_X86_NCOMBO,
  },
};

static const intel_x86_umask_t hswep_unc_h_txr_ak_cycles_full[]={
  { .uname = "ALL",
    .udesc  = "Counts cycles from both schedulers",
    .ucode  = 0x300,
    .uflags = INTEL_X86_NCOMBO | INTEL_X86_DFL,
  },
  { .uname = "SCHED0",
    .udesc  = "Counts cycles from scheduler bank 0",
    .ucode  = 0x100,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "SCHED1",
    .udesc  = "Counts cycles from scheduler bank 1",
    .ucode  = 0x200,
    .uflags = INTEL_X86_NCOMBO,
  },
};

static const intel_x86_umask_t hswep_unc_h_txr_bl[]={
  { .uname = "DRS_CACHE",
    .udesc  = "Counts data being sent to the cache",
    .ucode  = 0x100,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "DRS_CORE",
    .udesc  = "Counts data being sent directly to the requesting core",
    .ucode  = 0x200,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "DRS_QPI",
    .udesc  = "Counts data being sent to a remote socket over QPI",
    .ucode  = 0x400,
    .uflags = INTEL_X86_NCOMBO,
  },
};

static const intel_x86_umask_t hswep_unc_h_osb[]={
  { .uname = "REMOTE",
    .udesc  = "Remote",
    .ucode  = 0x800,
  },
  { .uname = "READS_LOCAL",
    .udesc  = "Local reads",
    .ucode  = 0x200,
  },
  { .uname = "INVITOE_LOCAL",
    .udesc  = "Local InvItoE",
    .ucode  = 0x400,
  },
  { .uname = "CANCELLED",
    .udesc  = "Cancelled due to D2C or Other",
    .ucode  = 0x1000,
  },
  { .uname = "READS_LOCAL_USEFUL",
    .udesc  = "Local reads - useful",
    .ucode  = 0x2000,
  },
  { .uname = "REMOTE_USEFUL",
    .udesc  = "Remote - useful",
    .ucode  = 0x4000,
  }
};

static const intel_x86_umask_t hswep_unc_h_osb_edr[]={
  { .uname = "ALL",
    .udesc  = "All data returns",
    .ucode  = 0x100,
    .uflags = INTEL_X86_DFL | INTEL_X86_NCOMBO,
  },
  { .uname = "READS_LOCAL_I",
    .udesc  = "Reads to local I",
    .ucode  = 0x200,
  },
  { .uname = "READS_REMOTE_I",
    .udesc  = "Reads to remote I",
    .ucode  = 0x400,
  },
  { .uname = "READS_LOCAL_S",
    .udesc  = "Reads to local S",
    .ucode  = 0x800,
  },
  { .uname = "READS_REMOTE_S",
    .udesc  = "Reads to remote S",
    .ucode  = 0x1000,
  }
};

static const intel_x86_umask_t hswep_unc_h_ring_ad_used[]={
  { .uname = "CCW_EVEN",
    .udesc  = "Counter-clockwise and even ring polarity",
    .ucode  = 0x400,
  },
  { .uname = "CCW_ODD",
    .udesc  = "Counter-clockwise and odd ring polarity",
    .ucode  = 0x800,
  },
  { .uname = "CW_EVEN",
    .udesc  = "Clockwise and even ring polarity",
    .ucode  = 0x100,
  },
  { .uname = "CW_ODD",
    .udesc  = "Clockwise and odd ring polarity",
    .ucode  = 0x200,
  },
  { .uname = "CW",
    .udesc  = "Clockwise with any polarity",
    .ucode  = 0x3300,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "CCW",
    .udesc  = "Counter-clockwise with any polarity",
    .ucode  = 0xcc00,
    .uflags = INTEL_X86_NCOMBO,
  },
};

static const intel_x86_umask_t hswep_unc_h_snp_resp_recv_local[]={
  { .uname = "RSPI",
    .udesc  = "Filters for snoop responses of RspI. RspI is returned when the remote cache does not have the data or when the remote cache silently evicts data (e.g. RFO hit non-modified line)",
    .ucode  = 0x100,
  },
  { .uname = "RSPS",
    .udesc  = "Filters for snoop responses of RspS. RspS is returned when the remote cache has the data but is not forwarding it. It is a way to let the requesting socket know that it cannot allocate the data in E-state",
    .ucode  = 0x200,
  },
  { .uname = "RSPIFWD",
    .udesc  = "Filters for snoop responses of RspIFwd. RspIFwd is returned when the remote cache agent forwards data and the requesting agent is able to acquire the data in E or M state. This is commonly returned with RFO transacations. It can be either HitM or HitFE",
    .ucode  = 0x400,
  },
  { .uname = "RSPSFWD",
    .udesc  = "Filters for snoop responses of RspSFwd. RspSFwd is returned when the remote cache agent forwards data  but holds on to its current copy. This is common for data and code reads that hit in a remote socket in E or F state",
    .ucode  = 0x800,
  },
  { .uname = "RSP_WB",
    .udesc  = "Filters for snoop responses of RspIWB or RspSWB. This is returned when a non-RFO requests hits in M-state. Data and code reads can return either RspIWB or RspSWB depending on how the system has been configured. InvItoE transactions will also return RspIWB because they must acquire ownership",
    .ucode  = 0x1000,
  },
  { .uname = "RSP_FWD_WB",
    .udesc  = "Filters for snoop responses of RspxFwdxWB. This snoop response is only used in 4s systems. It is used when a snoop HITM in a remote caching agent and it directly forwards data to a requester and simultaneously returns data to the home to be written back to memory",
    .ucode  = 0x2000,
  },
  { .uname = "RSPCNFLCT",
    .udesc  = "Filters for snoop responses of RspConflict. This is returned when a snoop finds an existing outstanding transaction in a remote caching agent when it CMAs that caching agent. This triggers the conflict resolution hardware. This covers both RspConflct and RspCnflctWBI",
    .ucode  = 0x4000,
  },
  { .uname = "OTHER",
    .udesc  = "Filters all other snoop responses",
    .ucode  = 0x8000,
  },
};

static const intel_x86_umask_t hswep_unc_h_sbo0_credits_acquired[]={
  { .uname = "AD",
    .udesc  = "For AD ring",
    .ucode  = 0x100,
  },
  { .uname = "BL",
    .udesc  = "For BL ring",
    .ucode  = 0x200,
  },
};

static const intel_x86_umask_t hswep_unc_h_snoops_rsp_after_data[]={
  { .uname = "LOCAL",
    .udesc  = "Local",
    .ucode  = 0x100,
    .uflags = INTEL_X86_NCOMBO,
  },
  { .uname = "REMOTE",
    .udesc  = "Remote",
    .ucode  = 0x200,
    .uflags = INTEL_X86_NCOMBO,
  },
};

static const intel_x86_umask_t hswep_unc_h_snoops_cycles_ne[]={
  { .uname = "ALL",
    .udesc  = "Local",
    .ucode  = 0x300,
    .uflags = INTEL_X86_NCOMBO | INTEL_X86_DFL,
  },
  { .uname = "LOCAL",
    .udesc  = "Local",
    .ucode  = 0x100,
  },
  { .uname = "REMOTE",
    .udesc  = "Remote",
    .ucode  = 0x200,
  },
};

static const intel_x86_umask_t hswep_unc_h_txr_ak[]={
  { .uname = "NDR",
    .udesc  = "Number of outbound NDR (non-data response) transactions send on the AK ring. AK NDR is used for messages to the local socket",
    .ucode  = 0x100,
  },
  { .uname = "CRD_CBO",
    .udesc  = "Number of outbound CDR transactions send on the AK ring to CBO",
    .ucode  = 0x200,
  },
  { .uname = "CRD_QPI",
    .udesc  = "Number of outbound CDR transactions send on the AK ring to QPI",
    .ucode  = 0x400,
  },
};

static const intel_x86_umask_t hswep_unc_h_stall_no_sbo_credit[]={
  { .uname = "SBO0_AD",
    .udesc  = "No credit for SBO0 AD Ring",
    .ucode  = 0x100,
  },
  { .uname = "SBO1_AD",
    .udesc  = "No credit for SBO1 AD Ring",
    .ucode  = 0x200,
  },
  { .uname = "SBO0_BL",
    .udesc  = "No credit for SBO0 BL Ring",
    .ucode  = 0x400,
  },
  { .uname = "SBO1_BL",
    .udesc  = "No credit for SBO1 BL Ring",
    .ucode  = 0x800,
  },
};

static const intel_x86_umask_t hswep_unc_h_tracker_occupancy[]={
  { .uname = "READS_LOCAL",
    .udesc  = "Local read requests",
    .ucode  = 0x400,
  },
  { .uname = "READS_REMOTE",
    .udesc  = "Remote read requests",
    .ucode  = 0x800,
  },
  { .uname = "WRITES_LOCAL",
    .udesc  = "Local write requests",
    .ucode  = 0x1000,
  },
  { .uname = "WRITES_REMOTE",
    .udesc  = "Remote write requests",
    .ucode  = 0x2000,
  },
  { .uname = "INVITOE_LOCAL",
    .udesc  = "Local InvItoE requests",
    .ucode  = 0x4000,
  },
  { .uname = "INVITOE_REMOTE",
    .udesc  = "Remote InvItoE requests",
    .ucode  = 0x8000,
  }
};

static const intel_x86_umask_t hswep_unc_h_txr_starved[]={
  { .uname = "AK",
    .udesc  = "For AD ring",
    .ucode  = 0x100,
  },
  { .uname = "BL",
    .udesc  = "For BL ring",
    .ucode  = 0x200,
  },
};

static const intel_x86_entry_t intel_hswep_unc_h_pe[]={
  { .name   = "UNC_H_CLOCKTICKS",
    .desc   = "HA Uncore clockticks",
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .cntmsk = 0xf,
    .code = 0x00,
  },
  { .name = "UNC_H_CONFLICT_CYCLES",
    .desc = "Conflict Checks",
    .code = 0xb,
    .cntmsk = 0x2,
    .modmsk = HSWEP_UNC_HA_ATTRS,
  },
  { .name = "UNC_H_DIRECT2CORE_COUNT",
    .desc = "Direct2Core Messages Sent",
    .code = 0x11,
    .cntmsk = 0xf,
    .modmsk = HSWEP_UNC_HA_ATTRS,
  },
  { .name = "UNC_H_DIRECT2CORE_CYCLES_DISABLED",
    .desc = "Cycles when Direct2Core was Disabled",
    .code = 0x12,
    .cntmsk = 0xf,
    .modmsk = HSWEP_UNC_HA_ATTRS,
  },
  { .name = "UNC_H_DIRECT2CORE_TXN_OVERRIDE",
    .desc = "Number of Reads that had Direct2Core Overridden",
    .code = 0x13,
    .cntmsk = 0xf,
    .modmsk = HSWEP_UNC_HA_ATTRS,
  },
  { .name = "UNC_H_DIRECTORY_LOOKUP",
    .desc = "Directory Lookups",
    .code = 0xc,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_directory_lookup),
    .umasks  = hswep_unc_h_directory_lookup
  },
  { .name = "UNC_H_DIRECTORY_UPDATE",
    .desc = "Directory Updates",
    .code = 0xd,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_directory_update),
    .umasks  = hswep_unc_h_directory_update
  },
  { .name = "UNC_H_IGR_NO_CREDIT_CYCLES",
    .desc = "Cycles without QPI Ingress Credits",
    .code = 0x22,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_igr_no_credit_cycles),
    .umasks  = hswep_unc_h_igr_no_credit_cycles
  },
  { .name = "UNC_H_IMC_RETRY",
    .desc = "Retry Events",
    .code = 0x1e,
    .cntmsk = 0xf,
    .modmsk = HSWEP_UNC_HA_ATTRS,
  },
  { .name = "UNC_H_IMC_WRITES",
    .desc = "HA to IMC Full Line Writes Issued",
    .code = 0x1a,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_imc_writes),
    .umasks  = hswep_unc_h_imc_writes
  },
  { .name = "UNC_H_IMC_READS",
    .desc = "HA to IMC normal priority reads issued",
    .code = 0x17,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_imc_reads),
    .umasks  = hswep_unc_h_imc_reads
  },
  { .name = "UNC_H_REQUESTS",
    .desc = "Read and Write Requests",
    .code = 0x1,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_requests),
    .umasks  = hswep_unc_h_requests
  },
  { .name = "UNC_H_RPQ_CYCLES_NO_REG_CREDITS",
    .desc = "IMC RPQ Credits Empty",
    .code = 0x15,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_rpq_cycles_no_reg_credits),
    .umasks  = hswep_unc_h_rpq_cycles_no_reg_credits
  },
  { .name = "UNC_H_TAD_REQUESTS_G0",
    .desc = "HA Requests to a TAD Region",
    .code = 0x1b,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_tad_requests_g0),
    .umasks  = hswep_unc_h_tad_requests_g0
  },
  { .name = "UNC_H_TAD_REQUESTS_G1",
    .desc = "HA Requests to a TAD Region",
    .code = 0x1c,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_tad_requests_g1),
    .umasks  = hswep_unc_h_tad_requests_g1
  },
  { .name = "UNC_H_TXR_AD_CYCLES_FULL",
    .desc = "AD Egress Full",
    .code = 0x2a,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_txr_ad_cycles_full),
    .umasks  = hswep_unc_h_txr_ad_cycles_full
  },
  { .name = "UNC_H_TXR_AK_CYCLES_FULL",
    .desc = "AK Egress Full",
    .code = 0x32,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_txr_ak_cycles_full),
    .umasks  = hswep_unc_h_txr_ak_cycles_full
  },
  { .name = "UNC_H_TXR_AK",
    .desc = "Outbound Ring Transactions on AK",
    .code = 0xe,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_txr_ak),
    .umasks  = hswep_unc_h_txr_ak
  },
  { .name = "UNC_H_TXR_BL",
    .desc = "Outbound DRS Ring Transactions to Cache",
    .code = 0x10,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_txr_bl),
    .umasks  = hswep_unc_h_txr_bl
  },
  { .name = "UNC_H_TXR_BL_CYCLES_FULL",
    .desc = "BL Egress Full",
    .code = 0x36,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_txr_ak_cycles_full),
    .umasks  = hswep_unc_h_txr_ak_cycles_full, /* identical to snbep_unc_h_txr_ak_cycles_full */
  },
  { .name = "UNC_H_WPQ_CYCLES_NO_REG_CREDITS",
    .desc = "HA IMC CHN0 WPQ Credits Empty",
    .code = 0x18,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_rpq_cycles_no_reg_credits),
    .umasks  = hswep_unc_h_rpq_cycles_no_reg_credits, /* shared */
  },
  { .name = "UNC_H_BT_BYPASS",
    .desc = "Backup Tracker bypass",
    .code = 0x52,
    .cntmsk = 0xf,
    .modmsk = HSWEP_UNC_HA_ATTRS,
  },
  { .name = "UNC_H_BYPASS_IMC",
    .desc = "HA to IMC bypass",
    .code = 0x14,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_bypass_imc),
    .umasks  = hswep_unc_h_bypass_imc,
  },
  { .name = "UNC_H_BT_CYCLES_NE",
    .desc = "Backup Tracker cycles not empty",
    .code = 0x42,
    .cntmsk = 0xf,
    .modmsk = HSWEP_UNC_HA_ATTRS,
  },
  { .name = "UNC_H_BT_OCCUPANCY",
    .desc = "Backup Tracker inserts",
    .code = 0x43,
    .cntmsk = 0xf,
    .modmsk = HSWEP_UNC_HA_ATTRS,
  },
  { .name = "UNC_H_OSB",
    .desc = "OSB snoop broadcast",
    .code = 0x53,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_osb),
    .umasks  = hswep_unc_h_osb,
  },
  { .name = "UNC_H_OSB_EDR",
    .desc = "OSB early data return",
    .code = 0x54,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_osb_edr),
    .umasks  = hswep_unc_h_osb_edr,
  },
  { .name = "UNC_H_RING_AD_USED",
    .desc = "AD ring in use",
    .code = 0x3e,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_ring_ad_used),
    .umasks  = hswep_unc_h_ring_ad_used,
  },
  { .name = "UNC_H_RING_AK_USED",
    .desc = "AK ring in use",
    .code = 0x3f,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_ring_ad_used), /* shared */
    .umasks  = hswep_unc_h_ring_ad_used,
  },
  { .name = "UNC_H_RING_BL_USED",
    .desc = "BL ring in use",
    .code = 0x40,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_ring_ad_used), /* shared */
    .umasks  = hswep_unc_h_ring_ad_used,
  },
  { .name = "UNC_H_DIRECTORY_LAT_OPT",
    .desc = "Directory latency optimization data return path taken",
    .code = 0x41,
    .cntmsk = 0xf,
    .modmsk = HSWEP_UNC_HA_ATTRS,
  },

  { .name = "UNC_H_SNOOP_RESP_RECV_LOCAL",
    .desc = "Snoop responses received local",
    .code = 0x60,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_snp_resp_recv_local),
    .umasks  = hswep_unc_h_snp_resp_recv_local,
  },
  { .name = "UNC_H_SNP_RESP_RECV_LOCAL",
    .desc = "Snoop responses received local",
    .code = 0x60,
    .cntmsk = 0xf,
    .ngrp = 1,
    .equiv = "UNC_H_SNOOP_RESP_RECV_LOCAL",
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_snp_resp_recv_local),
    .umasks  = hswep_unc_h_snp_resp_recv_local,
  },
  { .name = "UNC_H_TXR_BL_OCCUPANCY",
    .desc = "BL Egress occupancy",
    .code = 0x34,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_txr_bl_occupancy),
    .umasks  = hswep_unc_h_txr_bl_occupancy,
  },
  { .name = "UNC_H_SNOOP_RESP",
    .desc = "Snoop responses received",
    .code = 0x21,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_snoop_resp),
    .umasks  = hswep_unc_h_snoop_resp
  },
  { .name = "UNC_H_HITME_HIT",
    .desc = "Hits in the HitMe cache",
    .code = 0x71,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_hitme_hit),
    .umasks  = hswep_unc_h_hitme_hit
  },
  { .name = "UNC_H_HITME_HIT_PV_BITS_SET",
    .desc = "Number of PV bits set on HitMe cache hits",
    .code = 0x72,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_hitme_hit_pv_bits_set),
    .umasks  = hswep_unc_h_hitme_hit_pv_bits_set
  },
  { .name = "UNC_H_HITME_LOOKUP",
    .desc = "Number of accesses to HitMe cache",
    .code = 0x70,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_hitme_hit), /* shared with hswep_unc_h_hitme_hit */
    .umasks  = hswep_unc_h_hitme_hit
  },
  { .name = "UNC_H_SBO0_CREDIT_ACQUIRED",
    .desc = "SBO0 credits acquired",
    .code = 0x68,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_sbo0_credits_acquired),
    .umasks  = hswep_unc_h_sbo0_credits_acquired,
  },
  { .name = "UNC_H_SBO0_CREDIT_OCCUPANCY",
    .desc = "SBO0 credits occupancy",
    .code = 0x6a,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_sbo0_credits_acquired),
    .umasks  = hswep_unc_h_sbo0_credits_acquired, /* shared with hswep_unc_h_sbo0_credits_acquired */
  },
  { .name = "UNC_H_SBO1_CREDIT_ACQUIRED",
    .desc = "SBO1 credits acquired",
    .code = 0x69,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_sbo0_credits_acquired),
    .umasks  = hswep_unc_h_sbo0_credits_acquired,/* shared with hswep_unc_h_sbo0_credits_acquired */
  },
  { .name = "UNC_H_SBO0_CREDIT_OCCUPANCY",
    .desc = "SBO1 credits occupancy",
    .code = 0x6b,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_sbo0_credits_acquired),
    .umasks  = hswep_unc_h_sbo0_credits_acquired,
  },
  { .name = "UNC_H_SNOOPS_RSP_AFTER_DATA",
    .desc = "Number of reads when the snoops was on the critical path to the data return",
    .code = 0xa,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_snoops_rsp_after_data),
    .umasks  = hswep_unc_h_snoops_rsp_after_data,
  },
  { .name = "UNC_H_SNOOPS_CYCLES_NE",
    .desc = "Number of cycles when one or more snoops are outstanding",
    .code = 0x8,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_snoops_cycles_ne),
    .umasks  = hswep_unc_h_snoops_cycles_ne,
  },
  { .name = "UNC_H_SNOOPS_OCCUPANCY",
    .desc = "Tracker snoops outstanding accumulator",
    .code = 0x9,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_snoops_rsp_after_data),
    .umasks  = hswep_unc_h_snoops_rsp_after_data, /* shared */
  },
  { .name = "UNC_H_STALL_NO_SBO_CREDIT",
    .desc = "Stalls on no SBO credits",
    .code = 0x6c,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_stall_no_sbo_credit),
    .umasks  = hswep_unc_h_stall_no_sbo_credit,
  },
  { .name = "UNC_H_TRACKER_CYCLES_NE",
    .desc = "Tracker cycles not empty",
    .code = 0x3,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_snoops_cycles_ne),
    .umasks  = hswep_unc_h_snoops_cycles_ne, /* shared */
  },
  { .name = "UNC_H_TRACKER_OCCUPANCY",
    .desc = "Tracker occupancy accumulator",
    .code = 0x4,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_tracker_occupancy),
    .umasks  = hswep_unc_h_tracker_occupancy,
  },
  { .name = "UNC_H_TRACKER_PENDING_OCCUPANCY",
    .desc = "Data pending occupancy accumulator",
    .code = 0x5,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_snoops_rsp_after_data),
    .umasks  = hswep_unc_h_snoops_rsp_after_data, /* shared */
  },
  { .name = "UNC_H_TXR_STARVED",
    .desc = "Injection starvation",
    .code = 0x6d,
    .cntmsk = 0xf,
    .ngrp = 1,
    .modmsk = HSWEP_UNC_HA_ATTRS,
    .numasks = LIBPFM_ARRAY_SIZE(hswep_unc_h_txr_starved),
    .umasks  = hswep_unc_h_txr_starved,
  },
};
