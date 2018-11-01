/*
 * SOES Simple Open EtherCAT Slave
 *
 * Copyright (C) 2010 ZBE Inc.
 * Copyright (C) 2007-2013 Arthur Ketels
 * Copyright (C) 2012-2013 rt-labs.
 *
 * SOES is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 2 as published by the Free
 * Software Foundation.
 *
 * SOES is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * As a special exception, if other files instantiate templates or use macros
 * or inline functions from this file, or you compile this file and link it
 * with other works to produce a work based on this file, this file does not
 * by itself cause the resulting work to be covered by the GNU General Public
 * License. However the source code for this file must still be made available
 * in accordance with section (3) of the GNU General Public License.
 *
 * This exception does not invalidate any other reasons why a work based on
 * this file might be covered by the GNU General Public License.
 *
 * The EtherCAT Technology, the trade name and logo "EtherCAT" are the intellectual
 * property of, and protected by Beckhoff Automation GmbH.
 */

/** \file
 * \brief
 * Headerfile for esc_foe.c
 */

#ifndef __esc_foe__
#define __esc_foe__

#include <cc.h>

/** Maximum number of characters allowed in a file name. */
#define FOE_FN_MAX      15

typedef struct foe_writefile_cfg foe_writefile_cfg_t;
struct foe_writefile_cfg
{
   /** Name of file to receive from master */
   const char * name;
   /** Size of file,sizeof data we can recv */
   uint32_t       max_data;
   /** Where to store the data initially */
   uint32_t       dest_start_address;
   /** Current address during write of file */
   uint32_t       address_offset;
   /* FoE password */
   uint32_t       filepass;
   /* Pointer to application foe write function */
   uint32_t       (*write_function) (foe_writefile_cfg_t * self, uint8_t * data);
};

typedef struct foe_cfg
{
   /** Allocate static in caller func to fit buffer_size */
   uint8_t * fbuffer;
   /** Write this to fill-up, ex. 0xFF for "non write" */
   uint8_t   empty_write;
   /** Buffer size before we flush to destination */
   uint32_t  buffer_size;
   /** Number of files used in firmware update */
   uint32_t  n_files;
   /** Pointer to files configured to be used by FoE */
   foe_writefile_cfg_t * files;
} foe_cfg_t;

typedef struct CC_PACKED
{
   /** Current FoE state, ex. Waiting for ACK, Waiting for DATA */
   uint8_t  foestate;
   /** Current file buffer position, evaluated against foe file buffer size
    * when to flush
    */
   uint16_t fbufposition;
   /** Frame number in read or write sequence */
   uint32_t foepacket;
   /** Current position in file to be handled by FoE request */
   uint32_t fposition;
   /** Previous position in file to be handled by FoE request */
   uint32_t fprevposition;
   /** End position of allocated disk space for FoE requested file  */
   uint32_t fend;
} _FOEvar;

/* Initializes FoE state. */
void FOE_config (foe_cfg_t * cfg, foe_writefile_cfg_t * cfg_files);
void FOE_init (void);
void ESC_foeprocess (void);

#endif
